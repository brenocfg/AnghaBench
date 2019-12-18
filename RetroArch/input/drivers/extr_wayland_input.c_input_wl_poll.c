#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ delta_y; scalar_t__ delta_x; int /*<<< orphan*/  focus; scalar_t__ y; scalar_t__ last_y; scalar_t__ x; scalar_t__ last_x; } ;
struct TYPE_8__ {TYPE_2__* joypad; TYPE_1__ mouse; } ;
typedef  TYPE_3__ input_ctx_wayland_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* poll ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  flush_wayland_fd (TYPE_3__*) ; 
 int /*<<< orphan*/  input_wl_touch_pool (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void input_wl_poll(void *data)
{
   input_ctx_wayland_data_t *wl = (input_ctx_wayland_data_t*)data;
   if (!wl)
      return;

   flush_wayland_fd(wl);

   wl->mouse.delta_x = wl->mouse.x - wl->mouse.last_x;
   wl->mouse.delta_y = wl->mouse.y - wl->mouse.last_y;
   wl->mouse.last_x  = wl->mouse.x;
   wl->mouse.last_y  = wl->mouse.y;

   if (!wl->mouse.focus)
   {
      wl->mouse.delta_x = 0;
      wl->mouse.delta_y = 0;
   }

   if (wl->joypad)
      wl->joypad->poll();

   input_wl_touch_pool(wl);
}