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
typedef  int /*<<< orphan*/  uint64_t ;
struct controller_data_s {scalar_t__ rt; scalar_t__ lt; scalar_t__ back; scalar_t__ start; scalar_t__ down; scalar_t__ up; scalar_t__ right; scalar_t__ left; scalar_t__ x; scalar_t__ y; scalar_t__ a; scalar_t__ b; } ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_A ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_B ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_DOWN ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_L ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_LEFT ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_R ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_RIGHT ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_SELECT ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_START ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_UP ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_X ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_Y ; 
 int /*<<< orphan*/  get_controller_data (struct controller_data_s*,unsigned int) ; 
 int /*<<< orphan*/ * state ; 
 int /*<<< orphan*/  usb_do_poll () ; 

__attribute__((used)) static void xenon360_input_poll(void *data)
{
   (void)data;
   for (unsigned i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      struct controller_data_s pad;
      usb_do_poll();
      get_controller_data(&pad, i);

      uint64_t *cur_state = &state[i];

      *cur_state |= pad.b ? RETRO_DEVICE_ID_JOYPAD_A : 0;
      *cur_state |= pad.a ? RETRO_DEVICE_ID_JOYPAD_B : 0;
      *cur_state |= pad.y ? RETRO_DEVICE_ID_JOYPAD_X : 0;
      *cur_state |= pad.x ? RETRO_DEVICE_ID_JOYPAD_Y : 0;
      *cur_state |= pad.left ? RETRO_DEVICE_ID_JOYPAD_LEFT : 0;
      *cur_state |= pad.right ? RETRO_DEVICE_ID_JOYPAD_RIGHT : 0;
      *cur_state |= pad.up ? RETRO_DEVICE_ID_JOYPAD_UP : 0;
      *cur_state |= pad.down ? RETRO_DEVICE_ID_JOYPAD_DOWN : 0;
      *cur_state |= pad.start ? RETRO_DEVICE_ID_JOYPAD_START : 0;
      *cur_state |= pad.back ? RETRO_DEVICE_ID_JOYPAD_SELECT : 0;
      *cur_state |= pad.lt ? RETRO_DEVICE_ID_JOYPAD_L : 0;
      *cur_state |= pad.rt ? RETRO_DEVICE_ID_JOYPAD_R : 0;
   }
}