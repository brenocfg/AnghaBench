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
struct dispmanx_video {int /*<<< orphan*/  vsync_condition; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  display; scalar_t__ menu_surface; scalar_t__ back_surface; scalar_t__ main_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_host_deinit () ; 
 int /*<<< orphan*/  dispmanx_surface_free (struct dispmanx_video*,scalar_t__*) ; 
 int /*<<< orphan*/  free (struct dispmanx_video*) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_display_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispmanx_gfx_free(void *data)
{
   struct dispmanx_video *_dispvars = data;

   if (!_dispvars)
      return;

   dispmanx_surface_free(_dispvars, &_dispvars->main_surface);
   dispmanx_surface_free(_dispvars, &_dispvars->back_surface);

   if (_dispvars->menu_surface)
      dispmanx_surface_free(_dispvars, &_dispvars->menu_surface);

   /* Close display and deinitialize. */
   vc_dispmanx_display_close(_dispvars->display);
   bcm_host_deinit();

   /* Destroy mutexes and conditions. */
   slock_free(_dispvars->pending_mutex);
   scond_free(_dispvars->vsync_condition);

   free(_dispvars);
}