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
 int /*<<< orphan*/  SDL_CreateWindowAndRenderer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTF_Init () ; 
 int /*<<< orphan*/  TTF_OpenFont (char*,int) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  font ; 
 int /*<<< orphan*/  frame ; 
 int /*<<< orphan*/  renderer ; 
 int /*<<< orphan*/  window ; 

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    font = TTF_OpenFont("LiberationSansBold.ttf", 40);
    emscripten_set_main_loop(frame, -1, 1);
}