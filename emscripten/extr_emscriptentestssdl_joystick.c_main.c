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
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int SDL_INIT_JOYSTICK ; 
 int SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_async_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  main_2 ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);
  emscripten_async_call(main_2, NULL, 3000); // avoid startup delays and intermittent errors
  return 0;
}