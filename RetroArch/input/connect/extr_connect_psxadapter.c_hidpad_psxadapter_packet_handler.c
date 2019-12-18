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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct hidpad_psxadapter_data {int* data; int buttons; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  NO_BTN 140 
 scalar_t__ PSX_H_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSX_H_GET (int) ; 
 scalar_t__ PSX_H_LEFT (int /*<<< orphan*/ ) ; 
 scalar_t__ PSX_H_RIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ PSX_H_UP (int /*<<< orphan*/ ) ; 
#define  RETRO_DEVICE_ID_JOYPAD_A 139 
#define  RETRO_DEVICE_ID_JOYPAD_B 138 
 int RETRO_DEVICE_ID_JOYPAD_DOWN ; 
#define  RETRO_DEVICE_ID_JOYPAD_L 137 
#define  RETRO_DEVICE_ID_JOYPAD_L2 136 
#define  RETRO_DEVICE_ID_JOYPAD_L3 135 
 int RETRO_DEVICE_ID_JOYPAD_LEFT ; 
#define  RETRO_DEVICE_ID_JOYPAD_R 134 
#define  RETRO_DEVICE_ID_JOYPAD_R2 133 
#define  RETRO_DEVICE_ID_JOYPAD_R3 132 
 int RETRO_DEVICE_ID_JOYPAD_RIGHT ; 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 131 
#define  RETRO_DEVICE_ID_JOYPAD_START 130 
 int RETRO_DEVICE_ID_JOYPAD_UP ; 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpad_psxadapter_packet_handler(void *data, uint8_t *packet, uint16_t size)
{
   uint32_t i, pressed_keys;
   int16_t hat_value;
   static const uint32_t button_mapping[16] =
   {
      RETRO_DEVICE_ID_JOYPAD_L2,
      RETRO_DEVICE_ID_JOYPAD_R2,
      RETRO_DEVICE_ID_JOYPAD_L,
      RETRO_DEVICE_ID_JOYPAD_R,
      RETRO_DEVICE_ID_JOYPAD_SELECT,
      RETRO_DEVICE_ID_JOYPAD_START,
      RETRO_DEVICE_ID_JOYPAD_L3,
      RETRO_DEVICE_ID_JOYPAD_R3,
      NO_BTN,
      NO_BTN,
      NO_BTN,
      NO_BTN,
      RETRO_DEVICE_ID_JOYPAD_X,
      RETRO_DEVICE_ID_JOYPAD_A,
      RETRO_DEVICE_ID_JOYPAD_B,
      RETRO_DEVICE_ID_JOYPAD_Y,
   };
   struct hidpad_psxadapter_data *device = (struct hidpad_psxadapter_data*)data;

   if (!device)
      return;

   memcpy(device->data, packet, size);

   device->buttons = 0;

   pressed_keys  = device->data[7] | (device->data[6] << 8);

   for (i = 0; i < 16; i ++)
      if (button_mapping[i] != NO_BTN)
         device->buttons |= (pressed_keys & (1 << i)) ? (1 << button_mapping[i]) : 0;

   if (device->data[2]==0x7F) /* digital mode detection */
   {
      /* We're in digital mode, process the dpad values */
      device->buttons |= (device->data[4]==0x00) ? (1 << RETRO_DEVICE_ID_JOYPAD_LEFT) : 0;
      device->buttons |= (device->data[4]==0xFF) ? (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT) : 0;
      device->buttons |= (device->data[5]==0x00) ? (1 << RETRO_DEVICE_ID_JOYPAD_UP) : 0;
      device->buttons |= (device->data[5]==0xFF) ? (1 << RETRO_DEVICE_ID_JOYPAD_DOWN) : 0;
   }
   else
   {
      /* We're in analog mode, process the hat values as if they were pad buttons */
      hat_value = PSX_H_GET(device->data[6]);
      device->buttons |= PSX_H_LEFT(hat_value) ? (1 << RETRO_DEVICE_ID_JOYPAD_LEFT) : 0;
      device->buttons |= PSX_H_RIGHT(hat_value) ? (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT) : 0;
      device->buttons |= PSX_H_UP(hat_value) ? (1 << RETRO_DEVICE_ID_JOYPAD_UP) : 0;
      device->buttons |= PSX_H_DOWN(hat_value) ? (1 << RETRO_DEVICE_ID_JOYPAD_DOWN) : 0;
   }
}