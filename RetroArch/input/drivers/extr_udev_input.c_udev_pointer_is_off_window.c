#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pointer_x; scalar_t__ pointer_y; } ;
typedef  TYPE_1__ udev_input_t ;
struct video_viewport {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;

/* Variables and functions */
 int video_driver_get_viewport_info (struct video_viewport*) ; 

__attribute__((used)) static bool udev_pointer_is_off_window(const udev_input_t *udev)
{
#ifdef HAVE_X11
   struct video_viewport view;
   bool r = video_driver_get_viewport_info(&view);

   if (r)
      r = udev->pointer_x < view.x ||
          udev->pointer_x >= view.x + view.width ||
          udev->pointer_y < view.y ||
          udev->pointer_y >= view.y + view.height;
   return r;
#else
   return false;
#endif
}