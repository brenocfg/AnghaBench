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
typedef  int /*<<< orphan*/  uint16_t ;
struct connect_wii_wiimote_t {int dummy; } ;

/* Variables and functions */
#define  WM_RPT_BTN 131 
#define  WM_RPT_BTN_EXP 130 
#define  WM_RPT_CTRL_STATUS 129 
#define  WM_RPT_READ 128 
 int /*<<< orphan*/  wiimote_handle_expansion (struct connect_wii_wiimote_t*,int*) ; 
 int /*<<< orphan*/  wiimote_handshake (struct connect_wii_wiimote_t*,int const,int*,int) ; 
 int /*<<< orphan*/  wiimote_pressed_buttons (struct connect_wii_wiimote_t*,int*) ; 

__attribute__((used)) static void hidpad_wii_packet_handler(void *data,
      uint8_t *packet, uint16_t size)
{
   struct connect_wii_wiimote_t* device = (struct connect_wii_wiimote_t*)data;
   uint8_t             *msg = packet + 2;

   if (!device)
      return;

   switch (packet[1])
   {
      case WM_RPT_BTN:
         wiimote_pressed_buttons(device, msg);
         break;
      case WM_RPT_READ:
         wiimote_pressed_buttons(device, msg);
         wiimote_handshake(device, WM_RPT_READ, msg + 5,
               ((msg[2] & 0xF0) >> 4) + 1);
         break;
      case WM_RPT_CTRL_STATUS:
         wiimote_pressed_buttons(device, msg);
         wiimote_handshake(device,WM_RPT_CTRL_STATUS,msg,-1);
         break;
      case WM_RPT_BTN_EXP:
         wiimote_pressed_buttons(device, msg);
         wiimote_handle_expansion(device, msg+2);
         break;
   }
}