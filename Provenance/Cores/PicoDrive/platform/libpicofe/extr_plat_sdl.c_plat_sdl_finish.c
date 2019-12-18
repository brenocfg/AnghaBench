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
 int /*<<< orphan*/  SDL_FreeYUVOverlay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_h ; 
 int /*<<< orphan*/  fs_w ; 
 int /*<<< orphan*/  gl_finish () ; 
 scalar_t__ plat_sdl_gl_active ; 
 int /*<<< orphan*/ * plat_sdl_overlay ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vid_drv_name ; 

void plat_sdl_finish(void)
{
  if (plat_sdl_overlay != NULL) {
    SDL_FreeYUVOverlay(plat_sdl_overlay);
    plat_sdl_overlay = NULL;
  }
  if (plat_sdl_gl_active) {
    gl_finish();
    plat_sdl_gl_active = 0;
  }
  // restore back to initial resolution
  // resolves black screen issue on R-Pi
  if (strcmp(vid_drv_name, "x11") != 0)
    SDL_SetVideoMode(fs_w, fs_h, 16, SDL_SWSURFACE);
  SDL_Quit();
}