#include <stdio.h>		/* Included for "scanf(), printf()" */
#include <string.h>		/* Included for "strcpy()" */



int call_display(void) {

	printf("\n\n\n\n\n\n      ________     .__        __.    .___________.\n   .++--------\\\\    \\=-      -=/    //===========\\\\\n  //           \\\\    \\=-    -=/    //             \\\\\n ||/============\\\\    \\=-  -=/    //               \\\\\n||/^                   \\=--=/    //                 \\\\\n |\\\\            _.     /====\\    \\\\                 //\n  \\\\\\._________//     /=-  -=\\    \\\\               //\n   \\\\=========//     /=-    -=\\    \\\\             //\n    ^^^^^^^^^^^   ._/=-      -=\\_.  \\\\===========//\n                                     ''^^^^^^^^^''\n");
	printf("\n   A Tic-Tac-To implementation, for your terminal!\n                  Created by Moose.\n");
	
	printf("\n\n\n  ..______________________________________________..\n //------------------------------------------------\\\\\n||          ( s )      Start!                       ||\n||          ( h )    How to Play?                   ||\n||          ( c )      Credits                      ||\n||          ( q )       Quit                        ||\n\\\\--------------------------------------------------//\n ''^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^''\n\n\n");
	
	char input;
	int exit = 0;
	
	while(!exit) {
		
		scanf("%c", &input);
		exit = 0;
		
		switch(input) {
		
			case 'S':
			case 's':
				exit = 1;
				return 0;
			case 'H':
			case 'h':
				printf("\n\n\n/'|| (S)tart!\n/'|| (H)ow to play?\n/'|| (C)redits\n/'|| (Q)uit\n\n");
				printf("Use the keyboard to input the desired space, and then the symbol to use.\nFor the case of Tic-Tac-To, the symbol is either 'X' or 'O'.\nAn empty space is marked as '^'. Any empty space can be filled with either\nsymbol. A space that is already occupied can not be evicted by another symbol.\n\nThe field can be as large as the player desires. In the \"Start Menu\", the\ngame will request how large the user would like the field to be. No input\nwill default to '3'.\n\n\nThe field has two number rows, one at the top, and one at the bottom.\nThese number rows show the space number.\n(Top Row + Bottom Row = Space Number).\n\n\nYou can exit the game anytime by typing '0' or 'q' during active playtime.");
				break;
			case 'C':
			case 'c':
				printf("\n\n\n/'|| (S)tart!\n/'|| (H)ow to play?\n/'|| (C)redits\n/'|| (Q)uit\n\n");
				printf("Game created by Moose, using the C Programming Language.\nAny binary distributed will either be compiled with GCC or Clang. This will be noted in the changelog.");
				break;
			case 'Q':
			case 'q':
			default:
				exit = 1;
				return 1;
			
		}
	}
	
}


int call_game_menu(void) {
	
	printf("\n\n\n\n\n\n ..____________________________________________________..\n//------------------------------------------------------\\\\\n||      How large would you like the field to be?       ||\n||                                                      ||\n|| Enter any number below, besides negative or decimal: ||\n\\\\------------------------------------------------------//\n''^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^''\n\n\n");
	
	int input;
	scanf("%d", &input);
	
	if(input > 0) {
		return input;
	}
	else if (!input)
		return 3;
	else
		return -1;
		
}


void update_board(char board[], int board_size) {
	
	printf("\n\n\n\n     ");
	
	for(int lane = 0; lane < board_size; ++lane)
		printf("%3d ", lane+1);
	
	printf("\n\n");
	
	for(int f = 0; f < board_size*board_size;) {
			
			printf(" %3d ", f);
			
		for(int i = 0; i < board_size; ++i && ++f) {
			
			switch(board[f]) {
				
				case 'e':
					printf("| ^ ", f+1);
					break;
					
				case 'o':
					printf("| O ");
					break;
					
				case 'x':
					printf("| X ");
					break;
					
				default:
					printf("| * ");		/* error */
					break;
					
			}
		}
		printf("|\n\n");
	}
	
	printf("\n\n\n\n\n");
	
}


int change_board(char board[], int board_size, int slot_to_change, char symbol) {
	
	if(symbol != 'x' && symbol != 'o')
		return 0;
	else if(symbol == 'q' || symbol == 'Q')
		return 1;
	
	int full_board = board_size*board_size;
	
	char new_board[(full_board)+1];
	strcpy(new_board, board);
	new_board[(full_board)] = '\0';
	
	if(slot_to_change-1 <= (full_board) || slot_to_change-1 >= 0) {
		switch(board[slot_to_change-1]) {
			
			case 'e':
				new_board[slot_to_change-1] = symbol;
				strcpy(board, new_board);
				break;
			
			case 'x':
			case 'o':
				printf("That slot has already been occupied!\n");
				break;
			
			default:
				return -1;
				break;
				
		}
	return 0;
	}
}


int check_board(char board[], int board_size) {
	
	/* Returns 1 for an X win, returns 2 for an O win, returns 0 for no win. */
	
	char previous_character;
	int no_match = 0;
	
	/* Check horizontally */
	for(int i = 0; i <= (board_size*board_size)-1; i += board_size) {
		
		previous_character = board[i];
		
		for(int f = i; f <= i+board_size-1 && previous_character != 'e'; ++f) {

			if(previous_character == board[f] && f == i+(board_size-1))
				switch(board[f]) {
					case 'x':
						return 2;
					case 'o':
						return 3;
				}
			else if(previous_character != board[f])
				break;
			
		}
	}
	
	/* Check vertically */
	for(int i = 0; i <= board_size-1; ++i) {
		
		previous_character = board[i];
		
		for(int f = i; f <= ((board_size*board_size)-board_size)+i && previous_character != 'e'; f += board_size) {
			
			if(previous_character == board[f] && f == ((board_size*board_size)-board_size)+i)
				switch(board[f]) {
					case 'x':
						return 2;
					case 'o':
						return 3;
				}
			else if(previous_character != board[f])
				break;
			
		}
	}
	
	/* Check diagonally ( \ ) */
	for(int f = 0, previous_character = board[f]; f <= (board_size*board_size)-1 && previous_character != 'e'; f += (board_size+1)) {
			
		if(previous_character == board[f] && f == (board_size*board_size)-1)
			switch(board[f]) {
				case 'x':
					return 2;
				case 'o':
					return 3;
			}
		else if(previous_character != board[f])
			break;
			
	}
	
	/* Check diagonally ( / ) */
	for(int f = board_size-1, previous_character = board[f]; f < (board_size*board_size)-1 && previous_character != 'e'; f += board_size-1) {
		
		if(previous_character == board[f] && f == (board_size*board_size)-board_size)
			switch(board[f]) {
				case 'x':
					return 2;
				case 'o':
					return 3;
			}
		else if(previous_character != board[f])
			break;
			
	}
	
	int null_count;
	
	for(null_count = 0; null_count < (board_size*board_size) && board[null_count] != 'e'; ++null_count);
	
	if(null_count >= (board_size*board_size))
		return 1;
	
	
	return 0;
	
}


int main(void) {
	
	int tiles = 0;		/* How many tiles to render. 3 is default. */
	
	while(tiles <= 0) {
		
		if(call_display() < 1)
			tiles = call_game_menu();
			
		else {
			printf("\n\n\nThank you for playing!\n   - Moose <3\n\n\n");
			return 0;
		}
		
	}
	
	char board[(tiles*tiles)+1];
	/*
	 * e = empty slot
	 * o = slot with 'O' occupying it
	 * x = slot with 'X' occupying it
	 */

	/* Clear the board */
	
	for(int i = 0; i < tiles*tiles; ++i)
		board[i] = 'e';
	board[tiles*tiles+1] = '\0';	/* Set NULL terminator */
	
	printf("\n\n");
	
	int space, board_status = 0, exit = 0;
	char input;
	
	while(!exit) {
		
			update_board(board, tiles);
			scanf("%d %c", &space, &input);	/* Pause and wait for user input */
			change_board(board, tiles, space, input);
			
			board_status = check_board(board, tiles);
			if(board_status < 0) {
				printf("An error has occured, and the game has exited to prevent memory leak.\n");
				return -1;
			}
			
		/* Check if anyone has won! */
		if(board_status > 0) {
			
			update_board(board, tiles);
			
			switch(board_status) {
				
				case 1:
					printf("All spaces occupied; No one can win!... Try again next time! :>\n");
					break;
				case 2:
					printf("X has won the match!\n");
					break;
				case 3:
					printf("O has won the match!\n");
					break;
				default:
					printf("No winner!\n");
					break;
					
			}
			exit = 1;
		}
	}
	
	return 0;
	
}
