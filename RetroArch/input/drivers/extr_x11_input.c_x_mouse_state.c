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
struct TYPE_3__ {scalar_t__ mouse_m; scalar_t__ mouse_r; scalar_t__ mouse_l; scalar_t__ mouse_last_y; scalar_t__ mouse_y; scalar_t__ mouse_last_x; scalar_t__ mouse_x; } ;
typedef  TYPE_1__ x11_input_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 136 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 135 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 134 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 scalar_t__ x_mouse_state_wheel (unsigned int) ; 

__attribute__((used)) static int16_t x_mouse_state(x11_input_t *x11, unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return x11->mouse_x - x11->mouse_last_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return x11->mouse_y - x11->mouse_last_y;
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return x11->mouse_l;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return x11->mouse_r;
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
         return x_mouse_state_wheel(id);
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return x11->mouse_m;
   }

   return 0;
}