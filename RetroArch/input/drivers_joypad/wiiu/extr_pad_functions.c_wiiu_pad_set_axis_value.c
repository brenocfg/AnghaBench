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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 size_t RETRO_DEVICE_ID_ANALOG_X ; 
 size_t RETRO_DEVICE_ID_ANALOG_Y ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_LEFT ; 
 size_t RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
 size_t WIIU_DEVICE_INDEX_TOUCHPAD ; 

void wiiu_pad_set_axis_value(
      int16_t state[3][2],
      int16_t left_x,  int16_t left_y,
      int16_t right_x, int16_t right_y,
      int16_t touch_x, int16_t touch_y)
{
  state[RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X] = left_x;
  state[RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y] = left_y;
  state[RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X] = right_x;
  state[RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y] = right_y;
  state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_X] = touch_x;
  state[WIIU_DEVICE_INDEX_TOUCHPAD][RETRO_DEVICE_ID_ANALOG_Y] = touch_y;
}