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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_touch {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  gfx_ctx_wayland_data_t ;
struct TYPE_2__ {scalar_t__ id; unsigned int x; unsigned int y; scalar_t__ active; } ;

/* Variables and functions */
 int MAX_TOUCHES ; 
 TYPE_1__* active_touch_positions ; 
 scalar_t__ wl_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void touch_handle_motion(void *data,
      struct wl_touch *wl_touch,
      uint32_t time,
      int32_t id,
      wl_fixed_t x,
      wl_fixed_t y)
{
   int i;
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   for (i = 0; i < MAX_TOUCHES; i++)
   {
      if (  active_touch_positions[i].active &&
            active_touch_positions[i].id == id)
      {
         active_touch_positions[i].x = (unsigned) wl_fixed_to_int(x);
         active_touch_positions[i].y = (unsigned) wl_fixed_to_int(y);
      }
   }
}