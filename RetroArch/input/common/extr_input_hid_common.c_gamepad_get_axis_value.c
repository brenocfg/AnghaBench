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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int axis; int /*<<< orphan*/  is_negative; } ;
typedef  TYPE_1__ axis_data ;

/* Variables and functions */
#define  AXIS_LEFT_ANALOG_X 131 
#define  AXIS_LEFT_ANALOG_Y 130 
#define  AXIS_RIGHT_ANALOG_X 129 
#define  AXIS_RIGHT_ANALOG_Y 128 
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
 int /*<<< orphan*/  gamepad_clamp_axis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int16_t gamepad_get_axis_value(int16_t state[3][2], axis_data *data)
{
   int16_t value = 0;

   if(!data)
      return 0;

   switch(data->axis)
   {
      case AXIS_LEFT_ANALOG_X:
         value = state[RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X];
         break;
      case AXIS_LEFT_ANALOG_Y:
         value = state[RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y];
         break;
      case AXIS_RIGHT_ANALOG_X:
         value = state[RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X];
         break;
      case AXIS_RIGHT_ANALOG_Y:
         value = state[RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y];
         break;
   }

   return gamepad_clamp_axis(value, data->is_negative);
}