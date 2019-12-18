#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dinput_input {int mouse_rel_x; int mouse_rel_y; int mouse_l; int mouse_r; int mouse_wu; int mouse_wd; int mouse_hwu; int mouse_hwd; int mouse_m; int mouse_b4; int mouse_b5; } ;
struct TYPE_4__ {scalar_t__* input_mouse_index; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
typedef  int int16_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
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
 TYPE_2__* config_get_ptr () ; 

__attribute__((used)) static int16_t dinput_mouse_state(struct dinput_input *di, unsigned port, unsigned id)
{
   int16_t state = 0;

	settings_t *settings = config_get_ptr();

	if (port >= MAX_USERS)
		return false;

	/* the driver only supports one mouse */
	if (settings->uints.input_mouse_index[ port ] != 0)
		return 0;

   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return di->mouse_rel_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return di->mouse_rel_y;
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return di->mouse_l;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return di->mouse_r;
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         if (di->mouse_wu)
            state = 1;
         di->mouse_wu = false;
         return state;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         if (di->mouse_wd)
            state = 1;
         di->mouse_wd = false;
         return state;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
         if (di->mouse_hwu)
            state = 1;
         di->mouse_hwu = false;
         return state;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
         if (di->mouse_hwd)
            state = 1;
         di->mouse_hwd = false;
         return state;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return di->mouse_m;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
         return di->mouse_b4;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
         return di->mouse_b5;
   }

   return 0;
}