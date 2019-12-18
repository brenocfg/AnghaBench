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
struct TYPE_5__ {double x; double full_width; double width; } ;
typedef  TYPE_1__ video_viewport_t ;
struct TYPE_6__ {int x_min; int x_max; double x_abs; } ;
typedef  TYPE_2__ udev_input_mouse_t ;
typedef  double int32_t ;
typedef  double int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_get_viewport_info (TYPE_1__*) ; 

__attribute__((used)) static int16_t udev_mouse_get_pointer_x(const udev_input_mouse_t *mouse, bool screen)
{
   video_viewport_t vp;
   double src_min;
   double src_width;
   int32_t x;

   if (!video_driver_get_viewport_info(&vp))
      return 0;

   if (mouse->x_min < mouse->x_max) /* mouse coords are absolute */
   {
      src_min = mouse->x_min;
      src_width = mouse->x_max - mouse->x_min + 1;
   }
   else /* mouse coords are viewport relative */
   {
      src_min = vp.x;
      if (screen)
         src_width = vp.full_width;
      else
         src_width = vp.width;
   }

   x = -32767.0 + 65535.0 / src_width * (mouse->x_abs - src_min);
   x += (x < 0 ? -0.5 : 0.5);

   if (x < -0x7fff)
      x = -0x7fff;
   else if(x > 0x7fff)
      x = 0x7fff;

   return x;
}