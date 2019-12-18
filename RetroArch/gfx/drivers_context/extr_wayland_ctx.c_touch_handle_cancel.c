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
struct wl_touch {int dummy; } ;
typedef  int /*<<< orphan*/  gfx_ctx_wayland_data_t ;
struct TYPE_2__ {int active; int id; unsigned int x; unsigned int y; } ;

/* Variables and functions */
 int MAX_TOUCHES ; 
 TYPE_1__* active_touch_positions ; 
 scalar_t__ num_active_touches ; 

__attribute__((used)) static void touch_handle_cancel(void *data,
      struct wl_touch *wl_touch)
{
   /* If i understand the spec correctly we have to reset all touches here
    * since they were not ment for us anyway */
   int i;
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   for (i = 0; i < MAX_TOUCHES; i++)
   {
      active_touch_positions[i].active = false;
      active_touch_positions[i].id     = -1;
      active_touch_positions[i].x      = (unsigned) 0;
      active_touch_positions[i].y      = (unsigned) 0;
   }
   num_active_touches = 0;
}