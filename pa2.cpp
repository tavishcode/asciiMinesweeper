/*
 * pa2.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: Tavish
 */
/*
* COMP2011 (Spring 2016) Assignment 2: Designing the game of Minesweeper
*
* Student name: GOBINDRAM, TAVISH
* Student ID: 20317576
* Student email: tgobindram@connect.ust.hk
*
* Be reminded that you are only allowed to modify a certain part of this file. Read the assignment description and
 requirement carefully.
*/

#include <iostream>
#include <fstream>

using namespace std;

#define HEIGHT 15
#define WIDTH 15

const char MINE='X';
const char SAFE='@';
const char UNKNOWN='*';
const char WALL='W';

/* Given Functions */

//The function to print current mine_map in command line
void print_map(char map[HEIGHT][WIDTH])
{
   cout << " |012345678901234" << endl;
   cout << " ----------------" << endl;

   for (int i = 0; i < HEIGHT; i++)
   {
      cout << i % 10 << "|";
      for (int j = 0; j < WIDTH; j++)
      {
         if (map[i][j] == MINE || map[i][j] == SAFE)
            cout << UNKNOWN; // not showing the mine to player, instead show the symbol of UNKNOWN
         else
            cout << map[i][j];
      }
         cout << endl;
   }

   cout << " ----------------" << endl;
   cout << " |012345678901234" << endl;
}

//main helper function; useless for tasks
bool all_open(const char mine_map[HEIGHT][WIDTH])
{
   for (int i = 0; i < HEIGHT; i++)
      for (int j = 0; j < WIDTH; j++)
         if (mine_map[i][j] == SAFE)
            return false;

   return true;
}
//main helper function; useless for tasks; Load input file
bool load_mine_map(char mine_map[HEIGHT][WIDTH], int coin_map[HEIGHT][WIDTH],
                   int& initial_i, int& initial_j, const char file_name[])
{
   ifstream ifile(file_name);

   if (!ifile.is_open())  // failed to open the file
      return false;

   for (int i = 0; i < HEIGHT ;i++)  // read the mine map
      for (int j = 0; j < WIDTH; j++)
         ifile >> mine_map[i][j];

   for(int i = 0;i < HEIGHT; i++)  // read the coin map
      for(int j = 0; j < WIDTH; j++)
         ifile >> coin_map[i][j];

   ifile >> initial_i >> initial_j;  // get the initial position
   ifile.close();

   return true;
}

/* Your Tasks */
/*
 Task 1: You are required to implement this function by recursively using this function to complete task 1
 Parameters:
   mine_map: 2D char array to represent the current mine map
   row, col: The place swept now.In main function, this place is specified by input file or users.
*/
void sweep_fill_along_line(char mine_map[HEIGHT][WIDTH], int row, int col)
{
   //TODO: Add your code here
	int mine_count=0;
	if(mine_map[row][col]!=SAFE||(row>=HEIGHT)||(row<0)||
	   (col>=WIDTH)||(col<0))//base case: if block is checked/out of bounds/mine terminate
		return;
	for(int i=row-1;i<=row+1;i++) //iterates between above and lower row
	{
		if(i>=HEIGHT)
			break;
		else if(i<0)
			continue;
		for(int j=col-1;j<=col+1;j++) //iterates between previous and following columns
		{
			if(j>=WIDTH)
				break;
			else if(j<0)
				continue;
			else if (mine_map[i][j]==MINE)
				mine_count++; //calculates total mines surrounding a particular 'box'
		}
	}
	mine_map[row][col]=mine_count+'0';
	if(mine_count>0) //base case: if mine found near by terminate function
		return;
	sweep_fill_along_line(mine_map,row,col-1); //checks left side for mines
	sweep_fill_along_line(mine_map,row,col+1); //checks right side for mines
}
/*
 Task 2: You are required to implement this function by recursively using this function to complete task 2
 Parameters:
   mine_map: 2D char array to represent the current mine map
   row, col: The place swept now.In main function, this place is specified by input file or users.
*/
void sweep_fill(char mine_map[HEIGHT][WIDTH], int row, int col)
{
   //TODO: Add your code here
	int mine_count=0;
	if(mine_map[row][col]!=SAFE||(row>=HEIGHT)||(row<0)||(col>=WIDTH)||(col<0))
		return;
	for(int i=row-1;i<=row+1;i++) //iterates between above and lower row
		{
			if(i>=HEIGHT)
				break;
			else if(i<0)
				continue;
			for(int j=col-1;j<=col+1;j++) //iterates between previous and following columns
			{
				if(j>=WIDTH)
					break;
				else if(j<0)
					continue;
				else if (mine_map[i][j]==MINE)
					mine_count++; //calculates total mines surrounding a particular 'box'
			}
		}
	mine_map[row][col]=mine_count+'0';
	if(mine_count>0)
		return;
	sweep_fill(mine_map,row-1,col-1); //upper-left check
	sweep_fill(mine_map,row-1,col); //upper check
	sweep_fill(mine_map,row-1,col+1); //upper-right check
	sweep_fill(mine_map,row,col-1); //left check
	sweep_fill(mine_map,row,col+1); //right check
	sweep_fill(mine_map,row+1,col-1); //bottom-left check
	sweep_fill(mine_map,row+1,col);//bottom check
	sweep_fill(mine_map,row+1,col+1); //bottom-right check
}

/*
 Task 3: You are required to implement this function by recursively using this function to complete task 3.
 You are not allowed to call the function sweep_fill and results in task 2.
 Paramters:
   mine_map: 2D char array to represent the current mine map
   coin_map: 2D int array to record the number of coins in each block
   row, col: The place swept now.In main function, this place is specified by input file or users.
*/
int sweep_fill_collect_coin(char mine_map[HEIGHT][WIDTH], const int coin_map[HEIGHT][WIDTH], int row, int col)
{
   //TODO: Add your code here
	int mine_count=0,coins=0;
		if(mine_map[row][col]!=SAFE||(row>=HEIGHT)||(row<0)||(col>=WIDTH)||(col<0))
			return 0;
		if(coin_map[row][col]==-1) //checks if current position is a wall and terminates
		{
			mine_map[row][col]='W';
			return 0;
		}
		for(int i=row-1;i<=row+1;i++) //iterates between above and lower row
			{
				if(i>=HEIGHT)
					break;
				else if(i<0)
					continue;
				for(int j=col-1;j<=col+1;j++) //iterates between previous and following columns
				{
					if(j>=WIDTH)
						break;
					else if(j<0)
						continue;
					else if (mine_map[i][j]==MINE)
						mine_count++; //calculates total mines surrounding a particular 'box'
				}
			}
		mine_map[row][col]=mine_count+'0';
		coins+=coin_map[row][col]; //value of coins at current position
		if(mine_count>0)
		{
			return coins;
		}
		//continuously adds value of coins from each iteration without utilizing global variable
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row-1,col-1);
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row-1,col);
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row-1,col+1);
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row,col-1);
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row,col+1);
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row+1,col-1);
		coins+=sweep_fill_collect_coin(mine_map,coin_map,row+1,col);
		return coins+=sweep_fill_collect_coin(mine_map,coin_map,row+1,col+1); //returns total number from all function calls
}


/* Main function */
int main()
{
   int option = 1;
   char fname[100] = "";
   cout << "Welcome to the game!" << endl;
   cout << "Please input the file name: ";
   cin >> fname;

   char mine_map[HEIGHT][WIDTH];
   int coin_map[HEIGHT][WIDTH];

   int row, col;
   int coin_num;

   // load the mine map from the file in fname
   if (!load_mine_map(mine_map, coin_map, row, col, fname)) {
         cout << "Cannot load file!" << endl;
         return 0;
   }

   // Player select the playing mode: 1 for task 1, 2 for task 2, 3 for task 3 */
   cout << "Please select playing mode (1, 2 or 3): " << endl;
   cin >> option;

   // Start sweeping with the initial position from input file
   switch (option)
   {
      case 1:
         sweep_fill_along_line(mine_map, row, col);
         print_map(mine_map);
         break;
      case 2:
         sweep_fill(mine_map, row, col);
         print_map(mine_map);
         break;
      case 3:
         coin_num = sweep_fill_collect_coin(mine_map, coin_map, row, col);
         print_map(mine_map);
         cout << "You have collected " << coin_num << " coins." << endl;
   }

   // Asking whether the player want to continue
   char game_status = 'y';
   cout << "Continue? (Y/N)";
   cin >> game_status;

   // If player want to continue and not all safe places are swept
   while ((game_status == 'Y' || game_status == 'y') && (!all_open(mine_map)))
   {
      bool valid_input = true;

      // get a valid position
      do
      {
         cout << "Enter (row, col) coordinate: ";
         cin >> row >> col;

         if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
         {
            cout << "Input row and col are out of boundary! Please input again." << endl;
            valid_input = false;
         } else if (mine_map[row][col] == MINE) {   // a mine is selected, game over
            cout << "It's a mine. Game Over!" << endl;
            return 0;
         } else if ((mine_map[row][col] >= '0' && mine_map[row][col] <= '9') || (mine_map[row][col] == WALL)) {
            cout << "This block has been swept! Pleae select another block." << endl;
            valid_input = false;
         } else
            valid_input = true;

      } while (!valid_input);

      // Start sweeping with the position selected by player
      switch (option)
      {
         case 1:
            sweep_fill_along_line(mine_map, row, col);
            print_map(mine_map);
            break;
         case 2:
            sweep_fill(mine_map, row, col);
            print_map(mine_map);
            break;
         case 3:
            coin_num=sweep_fill_collect_coin(mine_map, coin_map, row, col);
            print_map(mine_map);
            cout << "You have collected " << coin_num << " coins."<<endl;
      }

      cout << "Continue? (Y/N) ";
      cin >> game_status;
   }

   // Game ends
   if ((game_status == 'Y') || (game_status == 'y'))
      cout << "You Win!" << endl;

   return 0;
}




