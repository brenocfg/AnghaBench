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
 int /*<<< orphan*/  SDL_CreateRenderer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GL_SetSwapInterval (int) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RENDERER_ACCELERATED ; 
 int /*<<< orphan*/  SDL_WINDOW_OPENGL ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  frame ; 
 int /*<<< orphan*/  renderer ; 
 int /*<<< orphan*/  window ; 

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("test", 0, 0, 640, 480, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_GL_SetSwapInterval(1);
    emscripten_set_main_loop(frame, -1, 1);
}