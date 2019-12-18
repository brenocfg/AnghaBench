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
struct TYPE_3__ {int buttons; double scroll_y; double scroll_x; int /*<<< orphan*/  delta_y; int /*<<< orphan*/  y; int /*<<< orphan*/  delta_x; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rwebinput_mouse_state_t ;
typedef  int int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 138 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 137 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 136 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 135 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 134 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 int RWEBINPUT_MOUSE_BTN4 ; 
 int RWEBINPUT_MOUSE_BTN5 ; 
 int RWEBINPUT_MOUSE_BTNL ; 
 int RWEBINPUT_MOUSE_BTNM ; 
 int RWEBINPUT_MOUSE_BTNR ; 

__attribute__((used)) static int16_t rwebinput_mouse_state(rwebinput_mouse_state_t *mouse,
   unsigned id, bool screen)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return (int16_t)(screen ? mouse->x : mouse->delta_x);
      case RETRO_DEVICE_ID_MOUSE_Y:
         return (int16_t)(screen ? mouse->y : mouse->delta_y);
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return !!(mouse->buttons & (1 << RWEBINPUT_MOUSE_BTNL));
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return !!(mouse->buttons & (1 << RWEBINPUT_MOUSE_BTNR));
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return !!(mouse->buttons & (1 << RWEBINPUT_MOUSE_BTNM));
      case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
         return !!(mouse->buttons & (1 << RWEBINPUT_MOUSE_BTN4));
      case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
         return !!(mouse->buttons & (1 << RWEBINPUT_MOUSE_BTN5));
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         return mouse->scroll_y < 0.0;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         return mouse->scroll_y > 0.0;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
         return mouse->scroll_x < 0.0;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
         return mouse->scroll_x > 0.0;
   }

   return 0;
}