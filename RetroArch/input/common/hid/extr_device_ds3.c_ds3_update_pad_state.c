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
typedef  int uint32_t ;
struct TYPE_3__ {int buttons; int* data; } ;
typedef  TYPE_1__ ds3_instance_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_JOYPAD_A 143 
#define  RETRO_DEVICE_ID_JOYPAD_B 142 
#define  RETRO_DEVICE_ID_JOYPAD_DOWN 141 
#define  RETRO_DEVICE_ID_JOYPAD_L 140 
#define  RETRO_DEVICE_ID_JOYPAD_L2 139 
#define  RETRO_DEVICE_ID_JOYPAD_L3 138 
#define  RETRO_DEVICE_ID_JOYPAD_LEFT 137 
#define  RETRO_DEVICE_ID_JOYPAD_R 136 
#define  RETRO_DEVICE_ID_JOYPAD_R2 135 
#define  RETRO_DEVICE_ID_JOYPAD_R3 134 
#define  RETRO_DEVICE_ID_JOYPAD_RIGHT 133 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 132 
#define  RETRO_DEVICE_ID_JOYPAD_START 131 
#define  RETRO_DEVICE_ID_JOYPAD_UP 130 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 

__attribute__((used)) static void ds3_update_pad_state(ds3_instance_t *instance)
{
   uint32_t i, pressed_keys;

   static const uint32_t button_mapping[17] =
   {
      RETRO_DEVICE_ID_JOYPAD_SELECT,
      RETRO_DEVICE_ID_JOYPAD_L3,
      RETRO_DEVICE_ID_JOYPAD_R3,
      RETRO_DEVICE_ID_JOYPAD_START,
      RETRO_DEVICE_ID_JOYPAD_UP,
      RETRO_DEVICE_ID_JOYPAD_RIGHT,
      RETRO_DEVICE_ID_JOYPAD_DOWN,
      RETRO_DEVICE_ID_JOYPAD_LEFT,
      RETRO_DEVICE_ID_JOYPAD_L2,
      RETRO_DEVICE_ID_JOYPAD_R2,
      RETRO_DEVICE_ID_JOYPAD_L,
      RETRO_DEVICE_ID_JOYPAD_R,
      RETRO_DEVICE_ID_JOYPAD_X,
      RETRO_DEVICE_ID_JOYPAD_A,
      RETRO_DEVICE_ID_JOYPAD_B,
      RETRO_DEVICE_ID_JOYPAD_Y,
      16 /* PS button */
   };

   instance->buttons = 0;

   pressed_keys = instance->data[2]|(instance->data[3] << 8)|((instance->data[4] & 0x01) << 16);

   for(i = 0; i < 17; i++)
     instance->buttons |= (pressed_keys & (1 << i)) ?
        (1 << button_mapping[i]) : 0;
}