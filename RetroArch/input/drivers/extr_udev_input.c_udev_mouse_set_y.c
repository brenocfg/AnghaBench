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
struct TYPE_5__ {scalar_t__ y; scalar_t__ full_height; } ;
typedef  TYPE_1__ video_viewport_t ;
struct TYPE_6__ {scalar_t__ y_abs; int /*<<< orphan*/  y_rel; } ;
typedef  TYPE_2__ udev_input_mouse_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ video_driver_get_viewport_info (TYPE_1__*) ; 

__attribute__((used)) static void udev_mouse_set_y(udev_input_mouse_t *mouse, int32_t y, bool abs)
{
   video_viewport_t vp;

   if (abs)
   {
      mouse->y_rel += y - mouse->y_abs;
      mouse->y_abs = y;
   }
   else
   {
      mouse->y_rel += y;
      if (video_driver_get_viewport_info(&vp))
      {
         mouse->y_abs += y;

         if (mouse->y_abs < vp.y)
            mouse->y_abs = vp.y;
         else if (mouse->y_abs >= vp.y + vp.full_height)
            mouse->y_abs = vp.y + vp.full_height - 1;
      }
   }
}