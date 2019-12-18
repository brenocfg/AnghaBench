#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mouse_l; int mouse_r; int mouse_m; int mouse_b4; int mouse_b5; int mouse_wu; int mouse_wd; int /*<<< orphan*/  mouse_abs_y; int /*<<< orphan*/  mouse_abs_x; int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; } ;
typedef  TYPE_1__ sdl_input_t ;
typedef  int Uint8 ;

/* Variables and functions */
 int SDL_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_BUTTON_LEFT ; 
 int /*<<< orphan*/  SDL_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  SDL_BUTTON_RIGHT ; 
 int /*<<< orphan*/  SDL_BUTTON_WHEELDOWN ; 
 int /*<<< orphan*/  SDL_BUTTON_WHEELUP ; 
 int /*<<< orphan*/  SDL_BUTTON_X1 ; 
 int /*<<< orphan*/  SDL_BUTTON_X2 ; 
 int /*<<< orphan*/  SDL_GetMouseState (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SDL_GetRelativeMouseState (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdl_poll_mouse(sdl_input_t *sdl)
{
   Uint8 btn = SDL_GetRelativeMouseState(&sdl->mouse_x, &sdl->mouse_y);

   SDL_GetMouseState(&sdl->mouse_abs_x, &sdl->mouse_abs_y);

   sdl->mouse_l  = (SDL_BUTTON(SDL_BUTTON_LEFT)      & btn) ? 1 : 0;
   sdl->mouse_r  = (SDL_BUTTON(SDL_BUTTON_RIGHT)     & btn) ? 1 : 0;
   sdl->mouse_m  = (SDL_BUTTON(SDL_BUTTON_MIDDLE)    & btn) ? 1 : 0;
   sdl->mouse_b4 = (SDL_BUTTON(SDL_BUTTON_X1)        & btn) ? 1 : 0;
   sdl->mouse_b5 = (SDL_BUTTON(SDL_BUTTON_X2)        & btn) ? 1 : 0;
#ifndef HAVE_SDL2
   sdl->mouse_wu = (SDL_BUTTON(SDL_BUTTON_WHEELUP)   & btn) ? 1 : 0;
   sdl->mouse_wd = (SDL_BUTTON(SDL_BUTTON_WHEELDOWN) & btn) ? 1 : 0;
#endif
}