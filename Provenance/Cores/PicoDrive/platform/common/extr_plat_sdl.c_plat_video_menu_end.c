#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * pixels; } ;
struct TYPE_12__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DisplayYUVOverlay (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_Flip (TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_LockYUVOverlay (TYPE_3__*) ; 
 scalar_t__ SDL_MUSTLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_UnlockYUVOverlay (TYPE_3__*) ; 
 int g_menuscreen_h ; 
 int /*<<< orphan*/ * g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int /*<<< orphan*/  gl_flip (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ plat_sdl_gl_active ; 
 TYPE_3__* plat_sdl_overlay ; 
 TYPE_2__* plat_sdl_screen ; 
 int /*<<< orphan*/  rgb565_to_uyvy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shadow_fb ; 

void plat_video_menu_end(void)
{
	if (plat_sdl_overlay != NULL) {
		SDL_Rect dstrect =
			{ 0, 0, plat_sdl_screen->w, plat_sdl_screen->h };

		SDL_LockYUVOverlay(plat_sdl_overlay);
		rgb565_to_uyvy(plat_sdl_overlay->pixels[0], shadow_fb,
				g_menuscreen_w * g_menuscreen_h);
		SDL_UnlockYUVOverlay(plat_sdl_overlay);

		SDL_DisplayYUVOverlay(plat_sdl_overlay, &dstrect);
	}
	else if (plat_sdl_gl_active) {
		gl_flip(g_menuscreen_ptr, g_menuscreen_w, g_menuscreen_h);
	}
	else {
		if (SDL_MUSTLOCK(plat_sdl_screen))
			SDL_UnlockSurface(plat_sdl_screen);
		SDL_Flip(plat_sdl_screen);
	}
	g_menuscreen_ptr = NULL;

}