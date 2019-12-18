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
struct dinput_input {int mouse_l; int mouse_r; int mouse_m; int mouse_b4; int mouse_b5; int mouse_wu; int mouse_wd; int mouse_hwu; int mouse_hwd; } ;
struct TYPE_4__ {scalar_t__* input_mouse_index; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 136 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 135 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 134 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 133 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 132 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 131 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 130 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 129 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 128 
 TYPE_2__* config_get_ptr () ; 

__attribute__((used)) static bool dinput_mouse_button_pressed(
      struct dinput_input *di, unsigned port, unsigned key)
{
	bool result;
	settings_t *settings = config_get_ptr();

	if (port >= MAX_USERS)
		return false;

	/* the driver only supports one mouse */
	if ( settings->uints.input_mouse_index[ port ] != 0)
		return false;

	switch (key)
   {
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return di->mouse_l;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return di->mouse_r;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return di->mouse_m;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
         return di->mouse_b4;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
         return di->mouse_b5;

      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         result = di->mouse_wu;
         di->mouse_wu = false;
         return result;

      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         result = di->mouse_wd;
         di->mouse_wd = false;
         return result;

      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
         result = di->mouse_hwu;
         di->mouse_hwu = false;
         return result;

      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
         result = di->mouse_hwd;
         di->mouse_hwd = false;
         return result;

   }

	return false;
}