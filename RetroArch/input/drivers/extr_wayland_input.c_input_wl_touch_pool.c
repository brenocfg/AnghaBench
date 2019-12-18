#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* touches; } ;
typedef  TYPE_2__ input_ctx_wayland_data_t ;
struct TYPE_4__ {int active; unsigned int x; unsigned int y; } ;

/* Variables and functions */
 int MAX_TOUCHES ; 
 scalar_t__ wayland_context_gettouchpos (TYPE_2__*,int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void input_wl_touch_pool(void *data)
{
   int id;
   unsigned touch_x             = 0;
   unsigned touch_y             = 0;
   input_ctx_wayland_data_t *wl = (input_ctx_wayland_data_t*)data;

   if (!wl)
      return;

   for (id = 0; id < MAX_TOUCHES; id++)
   {
      if (wayland_context_gettouchpos(wl, id, &touch_x, &touch_y))
         wl->touches[id].active = true;
      else
         wl->touches[id].active = false;
      wl->touches[id].x         = touch_x;
      wl->touches[id].y         = touch_y;
   }
}