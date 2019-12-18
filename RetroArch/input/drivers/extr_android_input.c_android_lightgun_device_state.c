#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_4__ {int mouse_x_delta; int mouse_y_delta; int mouse_m; int mouse_r; int /*<<< orphan*/  mouse_l; } ;
typedef  TYPE_1__ android_input_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_LIGHTGUN_CURSOR 134 
#define  RETRO_DEVICE_ID_LIGHTGUN_PAUSE 133 
#define  RETRO_DEVICE_ID_LIGHTGUN_START 132 
#define  RETRO_DEVICE_ID_LIGHTGUN_TRIGGER 131 
#define  RETRO_DEVICE_ID_LIGHTGUN_TURBO 130 
#define  RETRO_DEVICE_ID_LIGHTGUN_X 129 
#define  RETRO_DEVICE_ID_LIGHTGUN_Y 128 
 int /*<<< orphan*/  android_check_quick_tap (TYPE_1__*) ; 

__attribute__((used)) static int16_t android_lightgun_device_state(android_input_t *android, unsigned id)
{
   int val = 0;
   switch (id)
   {
      case RETRO_DEVICE_ID_LIGHTGUN_X:
         val = android->mouse_x_delta;
         android->mouse_x_delta = 0; /* flush delta after it has been read */
         break;
      case RETRO_DEVICE_ID_LIGHTGUN_Y:
         val = android->mouse_y_delta; /* flush delta after it has been read */
         android->mouse_y_delta = 0;
         break;
      case RETRO_DEVICE_ID_LIGHTGUN_TRIGGER:
         val = android->mouse_l || android_check_quick_tap(android);
         break;
      case RETRO_DEVICE_ID_LIGHTGUN_CURSOR:
         val = android->mouse_m;
         break;
      case RETRO_DEVICE_ID_LIGHTGUN_TURBO:
         val = android->mouse_r;
         break;
      case RETRO_DEVICE_ID_LIGHTGUN_START:
         val = android->mouse_m && android->mouse_r;
         break;
      case RETRO_DEVICE_ID_LIGHTGUN_PAUSE:
         val = android->mouse_m && android->mouse_l;
         break;
   }

   return val;
}