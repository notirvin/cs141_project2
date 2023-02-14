/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Windows 11 x86_64 and G++
    Template Authors: George Maratos and David Hayes
    Project Code Author: Irvin Ortiz
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>
#include<bits/stdc++.h>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl
         << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl
         << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M'))
    {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M'))
    {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move();
void initialize_board();
bool game_over();
bool valid_check();

/* Since player inputs need to be read by both make_move and game_over
   I initialized the playerInput outside of main for less hassle */
string playerInput;

/* Created alphaCheck for use in my make_move branch statment. This will
   allow me to check if each of the 3 playerInput characters fall within
   the acceptable uppercase letters. */
string alphaCheck = {"ABCDEFGHIJKLM"};

/* created global variable validInputs to define every possible move that could work.
   Like Prof. Hayes mentioned in his video, there are alot less moves that are correct
   than moves that are wrong. After checking every vertical, horizontal and diagonal,
   and then reversing those input, i came to find there were 32 possible inputs that are
   valid. */
string validInputs[32] = {"ACG", "GCA", "BFJ", "JFB", "CGK", "KGC", "DHL", "LHD", "GKM", "MKG", "BCD", "DCB", "EFG", "GFE", "FGH", "HGF", "GHI", "IHG", "JKL", "LKJ", "ADI", "IDA", "BGL", "LGB", "EJM", "MJE", "EBA", "ABE", "JGD", "DGJ", "MLI", "ILM"};

/* Pretty much based around the lab setup since it seemed the most sound way to approach */
int main()
{
    initialize_board();
    display_instructions();
    do
    {
        display_board();
        make_move();
    } while (!game_over() && !cin.eof());

    // TODO: How you define main is up to you.
    return 0;
}

void make_move()
{
    /* TODO: Write a function that reads in a command from the user
    and  updates the  board, if  the  move  is valid.  ONLY use the
    functions get_element and set_element to update the board, do
    not access the array 'board' directly. */

    /* Step 1: Initialize playerComplete. This will be used to end the
       loop if playerComplete becomes true. Also output the statement
       shown in the example textfiles */
    bool playerComplete = false;

    cout << "Enter positions from, jump, and to (e.g. EFG): ";

    /* Step 2: Take input from player into playerInput*/
    cin >> playerInput;

    /* Had to convert the input to uppercase so lowercase
       inputs like the autograder work */
    transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);

    /* Step 3: Begin mega branch statement for each error condition
       that would fanagle the output, with the X and R inputs being first.
       */
    while (playerComplete == false)
    {
        /* Checks if playeryInput is R */
        if (playerInput == "X" || playerInput == "x")
        {
            // playerComplete kills the loop and allows game_over to handle rest
            playerComplete = true;
        }
        /* Checks if playeryInput is R */
        else if (playerInput == "R" || playerInput == "r")
        {
            /* board is re-initialized after prompt + playerComplete kills loop for next
               display_board to occur (since game_over isn't true yet)
               */
            cout << "Restarting game." << endl;
            initialize_board();
            playerComplete = true;
        }
        /* Checks if input isn't 3 characters long. Kills loop + displays error if valid
         */
        else if (playerInput.size() != 3)
        {
            cout << "Invalid sequence. Please retry." << endl;
            playerComplete = true;
        }
        /* Checks if playerInputs 3 characters are within the A to M range. Kills loop
           + displays error message if invalid.
           */
        else if (alphaCheck.find(playerInput[0]) == string::npos || alphaCheck.find(playerInput[1]) == string::npos || alphaCheck.find(playerInput[2]) == string::npos)
        {
            /* Error message is spit out, then loop is killed */
            cout << "*** Given move has positions not on the board! Please retry." << endl;
            playerComplete = true;
        }
        /* Checks if the hopped element of playerInput was empty on board. If it is empty
           then it would kill loop and display error.
            */
        else if (get_element(playerInput[1]) != '#')
        {
            cout << "*** Must jump a piece. Please retry." << endl;
            playerComplete = true;
        }
        /* Checks if the hopping element of playerInput was empty on board. If it is empty
           then it would kill loop and display error.
            */
        else if (get_element(playerInput[0]) != '#')
        {
            cout << "*** Source needs a piece. Please retry." << endl;
            playerComplete = true;
        }
        /* Checks if the landing element of playerInput was taken on the board. If it is
           occupied then it would kill loop and display error.
            */
        else if (get_element(playerInput[2]) == '#')
        {
            cout << "*** Destination must be empty. Please retry." << endl;
            playerComplete = true;
        }
        /* Used my custom function to check if playerInput was a valid straight line */
        else if (valid_check() == true)
        {
            set_element(playerInput[0], '.');
            set_element(playerInput[1], '.');
            set_element(playerInput[2], '#');
            playerComplete = true;
        }
        /* Used this condition as a catch all for any invalid input not caught by previous
           validation branches */
        else
        {
            cout << "*** Move is invalid. Please retry." << endl;
            playerComplete = true;
        }
    }
}

/* Created function valid_check to compare the playerInput against the
   32 valid inputs i found earlier. If the input isn't valid, then the
   function will return a false, otherwise it will become true */
bool valid_check()
{
    bool results = false;
    for (int i = 0; i < size(validInputs); i++)
    {
        if (validInputs[i] == playerInput)
        {
            results = true;
        }
    }
    return results;
}

bool game_over()
{
    /* TODO: Write a function that returns true only if there is one
    one peg left, or if the user gives up by entering 'X' (or 'x')*/

    /* Mainly copied what Prof. Hayes did in the video he released.
       Just set a variable to false that would change to true if 12
       pegs were on the board or if the last playerInput was an 'x'
       or an 'X' */
    bool results = false;
    int boardCount = 13;

    for (char i = 'A'; i <= 'M'; i++)
    {
        if (get_element(i) == '.')
        {
            boardCount -= 1;
        }
    }

    if (boardCount == 1)
    {
        results = true;
        cout << "Congrats you win!";
    }
    else if (playerInput == "X" || playerInput == "x")
    {
        results = true;
        cout << "Exiting.";
    }

    return results;
}

void initialize_board()
{
    /* TODO: Initialize the board to have all pegs, besides the very
    center hole.  ONLY use the functions get_element and set_element
    to update  the board,  do not access  the array 'board' directly.
    */

    /* Basic gist of loop is to go down the array positions and drop a
       '#', except for the center, where it will drop a '.' We know
       that the center position for the board was G so thats where the
       loop plops a '.' down.
       */
    for (char i = 'A'; i <= 'M'; i++)
    {
        if (i == 'G')
        {
            set_element(i, '.');
        }
        else
        {
            set_element(i, '#');
        }
    }
}
