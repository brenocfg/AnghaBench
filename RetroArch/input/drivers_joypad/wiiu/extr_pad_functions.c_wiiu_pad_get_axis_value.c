#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
#define  WIIU_AXIS_LEFT_ANALOG_X 133 
#define  WIIU_AXIS_LEFT_ANALOG_Y 132 
#define  WIIU_AXIS_RIGHT_ANALOG_X 131 
#define  WIIU_AXIS_RIGHT_ANALOG_Y 130 
#define  WIIU_AXIS_TOUCH_X 129 
#define  WIIU_AXIS_TOUCH_Y 128 
 size_t WIIU_DEVICE_INDEX_TOUCHPAD ; 
 int /*<<< orphan*/  clamp_axis (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int16_t wiiu_pad_get_axis_value(int32_t axis,
      int16_t state[3][2], bool is_negative)
{
   int16_t value = 0;

   switch(axis)
   {
      case WIIU_AXIS_LEFT_ANALOG_X:
         value = state[RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X];
         break;
      case WIIU_AXIS_LEFT_ANALOG_Y:
         value = state[RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y];
         break;
      case WIIU_AXIS_RIGHT_ANALOG_X:
         value = state[RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X];
         break;
      case WIIU_AXIS_RIGHT_ANALOG_Y:
         value = state[RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y];
         break;
      case WIIU_AXIS_TOUCH_X:
         return state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_X];
      case WIIU_AXIS_TOUCH_Y:
         return state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_Y];
   }

   return clamp_axis(value, is_negative);
}