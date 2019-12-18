#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_video {float current_aspect; int /*<<< orphan*/  menu_surface; scalar_t__ menu_active; int /*<<< orphan*/  main_surface; } ;
struct TYPE_2__ {float value; } ;

/* Variables and functions */
 TYPE_1__* aspectratio_lut ; 
 int /*<<< orphan*/  drm_plane_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_surface_set_aspect (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void drm_set_aspect_ratio (void *data, unsigned aspect_ratio_idx)
{
   struct drm_video *_drmvars = data;
   /* Here we obtain the new aspect ratio. */
   float new_aspect = aspectratio_lut[aspect_ratio_idx].value;

   if (_drmvars->current_aspect != new_aspect)
   {
      _drmvars->current_aspect = new_aspect;
      drm_surface_set_aspect(_drmvars->main_surface, new_aspect);
      if (_drmvars->menu_active)
      {
         drm_surface_set_aspect(_drmvars->menu_surface, new_aspect);
         drm_plane_setup(_drmvars->menu_surface);
      }
   }
}