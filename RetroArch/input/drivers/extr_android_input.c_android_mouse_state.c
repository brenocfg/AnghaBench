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
struct TYPE_4__ {int mouse_r; int mouse_m; int mouse_x_delta; int mouse_y_delta; int mouse_wu; int mouse_wd; int /*<<< orphan*/  mouse_l; } ;
typedef  TYPE_1__ android_input_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_LEFT 134 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 int /*<<< orphan*/  android_check_quick_tap (TYPE_1__*) ; 

__attribute__((used)) static int16_t android_mouse_state(android_input_t *android, unsigned id)
{
   int val = 0;
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         val = android->mouse_l || android_check_quick_tap(android);
         break;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         val = android->mouse_r;
         break;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         val = android->mouse_m;
         break;
      case RETRO_DEVICE_ID_MOUSE_X:
         val = android->mouse_x_delta;
         android->mouse_x_delta = 0; /* flush delta after it has been read */
         break;
      case RETRO_DEVICE_ID_MOUSE_Y:
         val = android->mouse_y_delta; /* flush delta after it has been read */
         android->mouse_y_delta = 0;
         break;
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         val = android->mouse_wu;
         android->mouse_wu = 0;
         break;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         val = android->mouse_wd;
         android->mouse_wd = 0;
         break;
   }

   return val;
}