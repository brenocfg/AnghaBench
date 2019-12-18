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
struct TYPE_7__ {int mouse_l; int mouse_r; int mouse_m; } ;
typedef  TYPE_2__ x11_input_t ;
struct TYPE_6__ {scalar_t__* input_mouse_index; } ;
struct TYPE_8__ {TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 134 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 133 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 132 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 131 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 130 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 129 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 128 
 TYPE_3__* config_get_ptr () ; 
 int x_mouse_state_wheel (unsigned int) ; 

__attribute__((used)) static bool x_mouse_button_pressed(
      x11_input_t *x11, unsigned port, unsigned key)
{
   bool result;
   settings_t *settings = config_get_ptr();

   if (port >= MAX_USERS)
      return false;

   /* the driver only supports one mouse */
   if ( settings->uints.input_mouse_index[ port ] != 0 )
      return false;

   switch ( key )
   {

   case RETRO_DEVICE_ID_MOUSE_LEFT:
      return x11->mouse_l;
   case RETRO_DEVICE_ID_MOUSE_RIGHT:
      return x11->mouse_r;
   case RETRO_DEVICE_ID_MOUSE_MIDDLE:
      return x11->mouse_m;
/*   case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
      return x11->mouse_b4;*/
/*   case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
      return x11->mouse_b5;*/

   case RETRO_DEVICE_ID_MOUSE_WHEELUP:
   case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
   case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
   case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
      return x_mouse_state_wheel( key );
   }

   return false;
}