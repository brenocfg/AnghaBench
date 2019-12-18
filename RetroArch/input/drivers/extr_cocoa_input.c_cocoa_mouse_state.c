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
typedef  int int16_t ;
struct TYPE_3__ {int mouse_rel_x; int mouse_x_last; int mouse_rel_y; int mouse_y_last; int mouse_buttons; int mouse_wu; int mouse_wd; int mouse_wl; int mouse_wr; } ;
typedef  TYPE_1__ cocoa_input_data_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 135 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 134 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 

__attribute__((used)) static int16_t cocoa_mouse_state(cocoa_input_data_t *apple,
      unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
           return apple->mouse_rel_x - apple->mouse_x_last;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return apple->mouse_rel_y - apple->mouse_y_last;
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return apple->mouse_buttons & 1;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return apple->mouse_buttons & 2;
       case RETRO_DEVICE_ID_MOUSE_WHEELUP:
           return apple->mouse_wu;
       case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
           return apple->mouse_wd;
       case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
           return apple->mouse_wl;
       case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
           return apple->mouse_wr;
   }

   return 0;
}