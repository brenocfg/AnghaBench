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
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/ * SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyWindow (int /*<<< orphan*/ *) ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_UNDEFINED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_get_canvas_element_size (char*,int*,int*) ; 
 int /*<<< orphan*/  emscripten_set_canvas_element_size (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
    SDL_Window *window;

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

   // Test 1: Check that initializing video mode
   // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "sdlw_canvas_size",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        700,
        200,
        0
    );

    // Test 2: Check that getting current canvas size works.
    int w, h;
    emscripten_get_canvas_element_size("#canvas", &w, &h);
    printf("w:%d,h:%d\n", w,h);
    assert(w == 700);
    assert(h == 200);

    // Test 3: Check that resizing the canvas works as well.
    emscripten_set_canvas_element_size("#canvas", 640, 480);
    emscripten_get_canvas_element_size("#canvas", &w, &h);
    printf("w:%d,h:%d\n", w,h);
    assert(w == 640);
    assert(h == 480);

    SDL_DestroyWindow(window);
    SDL_Quit();
    REPORT_RESULT(1);

    return 0;
}