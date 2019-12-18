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
struct TYPE_3__ {int button; } ;
typedef  TYPE_1__ XButtonEvent ;

/* Variables and functions */
 int x11_mouse_hwd ; 
 int x11_mouse_hwu ; 
 int x11_mouse_wd ; 
 int x11_mouse_wu ; 

void x_input_poll_wheel(XButtonEvent *event, bool latch)
{
   switch (event->button)
   {
      case 4:
         x11_mouse_wu = 1;
         break;
      case 5:
         x11_mouse_wd = 1;
         break;
      case 6:
         /* Scroll wheel left == HORIZ_WHEELDOWN */
         x11_mouse_hwd = 1;
         break;
      case 7:
         /* Scroll wheel right == HORIZ_WHEELUP */
         x11_mouse_hwu = 1;
         break;
   }
}