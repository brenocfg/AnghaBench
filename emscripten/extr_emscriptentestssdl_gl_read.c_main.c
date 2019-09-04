#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SDL_Surface ;

/* Variables and functions */
 int /*<<< orphan*/  Draw () ; 
 int /*<<< orphan*/  Init () ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Verify () ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  width ; 

int main(int argc, char *argv[])
{
  SDL_Surface *screen;
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  if (!screen) {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }

  Init();
  Draw();
  Verify();

  return 0;
}