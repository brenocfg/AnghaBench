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
struct hidpad_wiiugca_data {int* data; int buttons; } ;

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
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpad_wiiugca_packet_handler(void *data, uint8_t *packet, uint16_t size)
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
   struct hidpad_wiiugca_data *device = (struct hidpad_wiiugca_data*)data;

   if (!device)
      return;

   memcpy(device->data, packet, size);

   device->buttons = 0;

   pressed_keys = device->data[3] | (device->data[4] << 8);

   for (i = 0; i < 12; i ++)
      device->buttons |= (pressed_keys & (1 << i)) ?
         (1 << button_mapping[i]) : 0;
}