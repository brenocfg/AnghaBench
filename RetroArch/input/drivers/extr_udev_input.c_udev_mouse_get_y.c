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
struct TYPE_5__ {double full_height; scalar_t__ height; } ;
typedef  TYPE_1__ video_viewport_t ;
struct TYPE_6__ {scalar_t__ y_min; scalar_t__ y_max; double y_rel; } ;
typedef  TYPE_2__ udev_input_mouse_t ;
typedef  double int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_get_viewport_info (TYPE_1__*) ; 

__attribute__((used)) static int16_t udev_mouse_get_y(const udev_input_mouse_t *mouse)
{
   video_viewport_t vp;
   double src_height;
   double y;

   if (!video_driver_get_viewport_info(&vp))
      return 0;

   if (mouse->y_min < mouse->y_max) /* mouse coords are absolute */
      src_height = mouse->y_max - mouse->y_min + 1;
   else
      src_height = vp.full_height;

   y = (double)vp.height / src_height * mouse->y_rel;

   return y + (y < 0 ? -0.5 : 0.5);
}