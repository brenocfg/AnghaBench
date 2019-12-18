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
struct dispmanx_video {int menu_active; int /*<<< orphan*/  menu_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispmanx_surface_free (struct dispmanx_video*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispmanx_set_texture_enable(void *data, bool state, bool full_screen)
{
   struct dispmanx_video *_dispvars = data;

   /* If it was active but it's not anymore... */
   if (!state && _dispvars->menu_active)
      dispmanx_surface_free(_dispvars, &_dispvars->menu_surface);

   _dispvars->menu_active = state;
}