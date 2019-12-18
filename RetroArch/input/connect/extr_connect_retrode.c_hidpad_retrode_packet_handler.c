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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct hidpad_retrode_data {int* data; int buttons; } ;

/* Variables and functions */
 int const NO_BTN ; 
#define  RETRO_DEVICE_ID_JOYPAD_A 135 
#define  RETRO_DEVICE_ID_JOYPAD_B 134 
#define  RETRO_DEVICE_ID_JOYPAD_L 133 
#define  RETRO_DEVICE_ID_JOYPAD_R 132 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 131 
#define  RETRO_DEVICE_ID_JOYPAD_START 130 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 struct hidpad_retrode_data** port_device ; 

__attribute__((used)) static void hidpad_retrode_packet_handler(void *data, uint8_t *packet, uint16_t size)
{
   uint32_t i, pressed_keys;
   static const uint32_t button_mapping[8] =
   {
           RETRO_DEVICE_ID_JOYPAD_B,
           RETRO_DEVICE_ID_JOYPAD_Y,
           RETRO_DEVICE_ID_JOYPAD_SELECT,
           RETRO_DEVICE_ID_JOYPAD_START,
           RETRO_DEVICE_ID_JOYPAD_A,
           RETRO_DEVICE_ID_JOYPAD_X,
           RETRO_DEVICE_ID_JOYPAD_L,
           RETRO_DEVICE_ID_JOYPAD_R
   };
   struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;
   struct hidpad_retrode_data *device1234;

   if (!device)
      return;

   /*
    * packet[1] contains Retrode port number
    * 1 = left SNES
    * 2 = right SNES
    * 3 = left Genesis/MD
    * 4 = right Genesis/MD
    */

   /* for port 1 only */
   /*
   if (packet[1] != 1)
          return;

   memcpy(device->data, packet, size);

   device->buttons = 0;

   pressed_keys = device->data[4];

   for (i = 0; i < 8; i ++)
      if (button_mapping[i] != NO_BTN)
         device->buttons |= (pressed_keys & (1 << i)) ? (1 << button_mapping[i]) : 0;
   */

   /*
    * find instance which handles specific port
    * (wiiusb_hid_read_cb calls first instance only, so need to delegate)
    */
   device1234 = port_device[packet[1] - 1];

   if (!device1234)
      return;

   memcpy(device1234->data, packet, size);

   device1234->buttons = 0;

   pressed_keys = device1234->data[4];

   for (i = 0; i < 8; i ++)
      if (button_mapping[i] != NO_BTN)
          device1234->buttons |= (pressed_keys & (1 << i)) ? (1 << button_mapping[i]) : 0;
}