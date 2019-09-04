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
 int /*<<< orphan*/  SDL_Flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int testImage (int /*<<< orphan*/ *,char*) ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_SWSURFACE);

  int result = 0;

  result |= testImage(screen, "screenshot.jpg"); // absolute path
  assert(result != 0);

  SDL_Flip(screen);

  printf("you should see an image.\n");

  SDL_Quit();

  return 0;
}