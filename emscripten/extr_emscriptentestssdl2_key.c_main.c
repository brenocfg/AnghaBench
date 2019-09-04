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

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_StartTextInput () ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_CENTERED ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  one () ; 

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window;
  window = SDL_CreateWindow("sdl2_key",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            640, 480, 0);

#ifdef TEST_EMSCRIPTEN_SDL_SETEVENTHANDLER
  emscripten_SDL_SetEventHandler(EventHandler, 0);
#else
  one();
#endif

  SDL_StartTextInput();

  emscripten_run_script("keydown(38);keyup(38)"); // up
  emscripten_run_script("keydown(40);keyup(40);"); // down
  emscripten_run_script("keydown(37);keyup(37);"); // left
  emscripten_run_script("keydown(39);keyup(39);"); // right
  emscripten_run_script("keydown(65);keyup(65);"); // a
  emscripten_run_script("keydown(66);keyup(66);"); // b
  emscripten_run_script("keydown(100);keyup(100);"); // trigger the end

  return 0;
}