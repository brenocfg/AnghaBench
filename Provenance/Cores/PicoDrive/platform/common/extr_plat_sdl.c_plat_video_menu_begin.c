#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_LockSurface (TYPE_1__*) ; 
 scalar_t__ SDL_MUSTLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  g_menuscreen_ptr ; 
 scalar_t__ plat_sdl_gl_active ; 
 int /*<<< orphan*/ * plat_sdl_overlay ; 
 TYPE_1__* plat_sdl_screen ; 
 int /*<<< orphan*/  shadow_fb ; 

void plat_video_menu_begin(void)
{
	if (plat_sdl_overlay != NULL || plat_sdl_gl_active) {
		g_menuscreen_ptr = shadow_fb;
	}
	else {
		if (SDL_MUSTLOCK(plat_sdl_screen))
			SDL_LockSurface(plat_sdl_screen);
		g_menuscreen_ptr = plat_sdl_screen->pixels;
	}
}