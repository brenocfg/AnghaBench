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
struct hidpad_nesusb_data {int* data; int buttons; } ;

/* Variables and functions */
#define  NO_BTN 138 
#define  RETRO_DEVICE_ID_JOYPAD_A 137 
#define  RETRO_DEVICE_ID_JOYPAD_B 136 
#define  RETRO_DEVICE_ID_JOYPAD_L 135 
#define  RETRO_DEVICE_ID_JOYPAD_L2 134 
#define  RETRO_DEVICE_ID_JOYPAD_R 133 
#define  RETRO_DEVICE_ID_JOYPAD_R2 132 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 131 
#define  RETRO_DEVICE_ID_JOYPAD_START 130 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpad_nesusb_packet_handler(void *data, uint8_t *packet, uint16_t size)
{
   uint32_t i, pressed_keys;
   static const uint32_t button_mapping[17] =
   {
      RETRO_DEVICE_ID_JOYPAD_L2,
      RETRO_DEVICE_ID_JOYPAD_R2,
      RETRO_DEVICE_ID_JOYPAD_L,
      RETRO_DEVICE_ID_JOYPAD_R,
      RETRO_DEVICE_ID_JOYPAD_SELECT,
      RETRO_DEVICE_ID_JOYPAD_START,
      NO_BTN,
      NO_BTN,
      NO_BTN,
      NO_BTN,
      NO_BTN,
      NO_BTN,
      RETRO_DEVICE_ID_JOYPAD_B,
      RETRO_DEVICE_ID_JOYPAD_A,
      RETRO_DEVICE_ID_JOYPAD_Y,
      RETRO_DEVICE_ID_JOYPAD_X,
   };
   struct hidpad_nesusb_data *device = (struct hidpad_nesusb_data*)data;

   if (!device)
      return;

   memcpy(device->data, packet, size);

   device->buttons = 0;

   pressed_keys  = device->data[7] | (device->data[6] << 8);

   for (i = 0; i < 16; i ++)
      if (button_mapping[i] != NO_BTN)
         device->buttons |= (pressed_keys & (1 << i)) ? (1 << button_mapping[i]) : 0;
}