/**
 * C++ class for a game of the Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Game.h"
#include "Stack.h"
#include "uiuc/Cube.h"
#include "uiuc/HSLAPixel.h"

#include <iostream>
using std::cout;
using std::endl;

// Solves the Tower of Hanoi puzzle.
// (Feel free to call "helper functions" to help you solve the puzzle.)
void Game::solve() {
  // Prints out the state of the game:
  cout << *this << endl;

  // Define the target size
  unsigned idxStaIni = 0;
  unsigned idxStaFin = 2;
  unsigned idxStaSpa = 1;
  moveSta(idxStaIni, idxStaFin, idxStaSpa, 0);
  
}

// Default constructor to create the initial state:
Game::Game() {
  // Create the three empty stacks:
  for (int i = 0; i < 3; i++) {
    Stack stackOfCubes;
    stacks_.push_back( stackOfCubes );
  }

  // Create the four cubes, placing each on the [0]th stack:
  Cube blue(4, uiuc::HSLAPixel::BLUE);
  stacks_[0].push_back(blue);

  Cube orange(3, uiuc::HSLAPixel::ORANGE);
  stacks_[0].push_back(orange);

  Cube purple(2, uiuc::HSLAPixel::PURPLE);
  stacks_[0].push_back(purple);

  Cube yellow(1, uiuc::HSLAPixel::YELLOW);
  stacks_[0].push_back(yellow);
}

void Game::move(unsigned idxStaIni, unsigned idxStaFin){
  if ( stacks_.size() <= idxStaIni || stacks_.size() <= idxStaFin || idxStaIni < 0 || idxStaFin < 0 || idxStaIni==idxStaFin){
    throw std::runtime_error("Moving indices requested out of range");
  }
  if ( stacks_[idxStaIni].size() <= 0){
    throw std::runtime_error("Starting stack to be moved is empty");
  }
  if ( stacks_[idxStaFin].size() > 0 && stacks_[idxStaIni].peekTop().getLength() >= stacks_[idxStaFin].peekTop().getLength()){
    throw std::runtime_error("Illegal move requested");
  } else {
    Cube cubeRm = stacks_[idxStaIni].removeTop();
    stacks_[idxStaFin].push_back(cubeRm);
  }
}

void Game::moveSta(unsigned idxStaIni, unsigned idxStaFin, unsigned idxStaSpa, unsigned level){
  if ((stacks_[idxStaIni].size()-level) > 1){
    unsigned levRetSta = stacks_[idxStaSpa].size();
    moveSta(idxStaIni,idxStaSpa,idxStaFin,level+1);
    move(idxStaIni,idxStaFin);
    cout << *this << endl;
    moveSta(idxStaSpa,idxStaFin,idxStaIni,levRetSta);
  } else if ((stacks_[idxStaIni].size()-level) == 1){
    move(idxStaIni,idxStaFin);
    cout << *this << endl;
  } else {
    throw std::runtime_error("Starting stack has no cube");
  }
}


std::ostream& operator<<(std::ostream & os, const Game & game) {
  for (unsigned i = 0; i < game.stacks_.size(); i++) {
    os << "Stack[" << i << "]: " << game.stacks_[i];
  }
  return os;
}
