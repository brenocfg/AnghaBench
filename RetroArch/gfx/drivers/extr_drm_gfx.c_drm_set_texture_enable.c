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
struct drm_video {int menu_active; int /*<<< orphan*/  menu_surface; int /*<<< orphan*/  main_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_plane_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_surface_free (struct drm_video*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_set_texture_enable(void *data, bool state, bool full_screen)
{
   struct drm_video *_drmvars = data;

   /* If menu was active but it's not anymore... */
   if (!state && _drmvars->menu_active)
   {
      /* We tell ony the plane we have to read from the main surface again */
      drm_plane_setup(_drmvars->main_surface);
      /* We free the menu surface buffers */
      drm_surface_free(_drmvars, &_drmvars->menu_surface);
   }

   _drmvars->menu_active = state;
}