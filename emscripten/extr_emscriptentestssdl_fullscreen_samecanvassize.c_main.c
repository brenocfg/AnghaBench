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

/* Variables and functions */
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_get_canvas_element_size (char*,int*,int*) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mainloop ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  screen ; 

int main() {
  int w, h;
  emscripten_get_canvas_element_size("#canvas", &w, &h);
  printf("w:%d,h:%d\n", w,h);

  SDL_Init(SDL_INIT_VIDEO);

  screen = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE); //set with the same size with canvas. this used to break full screen

  printf("You should see a yellow canvas.\n");
  printf("Click on the canvas to enter full screen, and then click on the canvas again to finish the test.\n");
  printf("When in full screen, you should see the whole screen filled yellow, and after exiting, the yellow canvas should be restored in the window.\n");
  emscripten_set_main_loop(mainloop, 0, 0);
  return 0;
}