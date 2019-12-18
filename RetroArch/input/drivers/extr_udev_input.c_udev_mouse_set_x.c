#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ x; scalar_t__ full_width; } ;
typedef  TYPE_1__ video_viewport_t ;
struct TYPE_6__ {scalar_t__ x_abs; int /*<<< orphan*/  x_rel; } ;
typedef  TYPE_2__ udev_input_mouse_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ video_driver_get_viewport_info (TYPE_1__*) ; 

__attribute__((used)) static void udev_mouse_set_x(udev_input_mouse_t *mouse, int32_t x, bool abs)
{
   video_viewport_t vp;

   if (abs)
   {
      mouse->x_rel += x - mouse->x_abs;
      mouse->x_abs = x;
   }
   else
   {
      mouse->x_rel += x;
      if (video_driver_get_viewport_info(&vp))
      {
         mouse->x_abs += x;

         if (mouse->x_abs < vp.x)
            mouse->x_abs = vp.x;
         else if (mouse->x_abs >= vp.x + vp.full_width)
            mouse->x_abs = vp.x + vp.full_width - 1;
      }
   }
}