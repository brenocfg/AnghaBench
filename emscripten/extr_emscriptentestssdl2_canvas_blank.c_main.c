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
typedef  int /*<<< orphan*/  SDL_Window ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  int /*<<< orphan*/  SDL_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateRGBSurface (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateWindowAndRenderer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockSurface (int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_MUSTLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (int /*<<< orphan*/ *) ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(256, 256, 0, &window, &renderer);

  SDL_Surface *screen = SDL_CreateRGBSurface(0, 256, 256, 8, 0, 0, 0, 0);

  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_RenderPresent(renderer);

  // Don't quit - we need to reftest the canvas! SDL_Quit();

  return 0;
}