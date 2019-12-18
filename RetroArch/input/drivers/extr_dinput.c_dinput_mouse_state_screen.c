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
struct dinput_input {int mouse_x; int mouse_y; } ;
struct TYPE_4__ {scalar_t__* input_mouse_index; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
typedef  int int16_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 TYPE_2__* config_get_ptr () ; 
 int dinput_mouse_state (struct dinput_input*,unsigned int,unsigned int) ; 

__attribute__((used)) static int16_t dinput_mouse_state_screen(struct dinput_input *di, unsigned port, unsigned id)
{
	settings_t *settings = config_get_ptr();

	if (port >= MAX_USERS)
		return false;

	/* the driver only supports one mouse */
	if (settings->uints.input_mouse_index[ port ] != 0)
		return 0;

   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return di->mouse_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return di->mouse_y;
      default:
         break;
   }

   return dinput_mouse_state(di, port, id);
}