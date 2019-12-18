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
struct TYPE_3__ {int* data; int buttons; } ;
typedef  TYPE_1__ gca_pad_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_JOYPAD_A 139 
#define  RETRO_DEVICE_ID_JOYPAD_B 138 
#define  RETRO_DEVICE_ID_JOYPAD_DOWN 137 
#define  RETRO_DEVICE_ID_JOYPAD_L 136 
#define  RETRO_DEVICE_ID_JOYPAD_LEFT 135 
#define  RETRO_DEVICE_ID_JOYPAD_R 134 
#define  RETRO_DEVICE_ID_JOYPAD_RIGHT 133 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 132 
#define  RETRO_DEVICE_ID_JOYPAD_START 131 
#define  RETRO_DEVICE_ID_JOYPAD_UP 130 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 

__attribute__((used)) static void update_buttons(gca_pad_t *pad)
{
   uint32_t i, pressed_keys;

   static const uint32_t button_mapping[12] =
   {
      RETRO_DEVICE_ID_JOYPAD_A,
      RETRO_DEVICE_ID_JOYPAD_B,
      RETRO_DEVICE_ID_JOYPAD_X,
      RETRO_DEVICE_ID_JOYPAD_Y,
      RETRO_DEVICE_ID_JOYPAD_LEFT,
      RETRO_DEVICE_ID_JOYPAD_RIGHT,
      RETRO_DEVICE_ID_JOYPAD_DOWN,
      RETRO_DEVICE_ID_JOYPAD_UP,
      RETRO_DEVICE_ID_JOYPAD_START,
      RETRO_DEVICE_ID_JOYPAD_SELECT,
      RETRO_DEVICE_ID_JOYPAD_R,
      RETRO_DEVICE_ID_JOYPAD_L,
   };

   if(!pad)
      return;

   pressed_keys = pad->data[1] | (pad->data[2] << 8);
   pad->buttons = 0;

   for (i = 0; i < 12; i++)
      pad->buttons |= (pressed_keys & (1 << i)) ?
         (1 << button_mapping[i]) : 0;
}