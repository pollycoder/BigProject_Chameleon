#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "tableboard.h"

/************************************************************
 * Process of a game:
 *  1. Initialize a cardstack
 *  2. Deal the card to players
 *  3. Play the card (rules have been finished in C project)
 *  4. End the game once the stack and vectors are all empty
 * Props of one game:
 *  1. Cards (stack)
 *  2. Players
 * Operations inside a game:
 *  1. Deal the card
 *  2. Play:
 *      (1) Give a card
 *          1) Check the calidity
 *          2) Choose a card due to the strategy
 *      (2) Take a card if the stack is not empty
************************************************************/


class Game : public Tableboard
{
public:
    //init part
    Game();
    friend class mode;
    friend class MainWindow;
    void deal();

    //play part
    Card givecard(int player_index, int position);
    void getcard(int player_index);

    //rule part
    friend bool valid_rule(const Card& card, Game *g);
    friend bool chame_rule(const Card& card, Game *g);
    Color getcolor(){return current_color;}
    int getnumber(){return current_num;}
    void CheckValid(bool (*valid_rule)(const Card& card, Game *g), Player& player);
    void CheckChame(bool (*chame_rule)(const Card& card, Game *g), Player& player);

    //Don't distinct play and discard
    int select_card(bool (*valid_rule)(const Card& card, Game *g), bool (*chame_rule)(const Card& card, Game *g), int player_index);

    void check_play(int player_index, Card& cardgiven);
    Color select_color(){return static_cast<Color>(arc4random() % colornum);}

    //Change the current color and number
    void change_color(Color c){current_color = c;}
    void change_number(int num){current_num = num;}
    //Game
    void play_a_turn(int turn);
    void update_playercard(int player_index);




private:
    Cardstack cardstack;
    Players players;
    //Using display function in tableboard class
    Color current_color;
    int current_num;

};

bool valid_rule(const Card& card, Game *g);
bool chame_rule(const Card& card, Game *g);
void delay();
#endif // GAME_H