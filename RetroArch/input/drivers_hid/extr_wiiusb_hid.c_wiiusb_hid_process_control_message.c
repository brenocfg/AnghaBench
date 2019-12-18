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
struct wiiusb_adapter {int send_control_type; int /*<<< orphan*/  send_control_buffer; int /*<<< orphan*/  send_control_size; int /*<<< orphan*/  handle; int /*<<< orphan*/  endpoint_out; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int USB_REPTYPE_FEATURE ; 
 int USB_REPTYPE_OUTPUT ; 
 int /*<<< orphan*/  USB_REQTYPE_INTERFACE_SET ; 
 int /*<<< orphan*/  USB_REQ_SETREPORT ; 
 int /*<<< orphan*/  USB_WriteCtrlMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_WriteIntrMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  WIIUSB_SC_CTRLMSG 130 
#define  WIIUSB_SC_CTRLMSG2 129 
#define  WIIUSB_SC_INTMSG 128 
 int WIIUSB_SC_NONE ; 

__attribute__((used)) static void wiiusb_hid_process_control_message(struct wiiusb_adapter* adapter)
{
   int32_t r;
   switch (adapter->send_control_type)
   {
      case WIIUSB_SC_INTMSG:
         do
         {
            r = USB_WriteIntrMsg(adapter->handle,
               adapter->endpoint_out, adapter->send_control_size,
               adapter->send_control_buffer);
         } while (r < 0);
         break;
      case WIIUSB_SC_CTRLMSG:
         do
         {
            r = USB_WriteCtrlMsg(adapter->handle, USB_REQTYPE_INTERFACE_SET,
               USB_REQ_SETREPORT, (USB_REPTYPE_FEATURE<<8) | 0xf4, 0x0,
               adapter->send_control_size, adapter->send_control_buffer);
         } while (r < 0);
         break;
      case WIIUSB_SC_CTRLMSG2:
         do
         {
            r = USB_WriteCtrlMsg(adapter->handle, USB_REQTYPE_INTERFACE_SET,
                  USB_REQ_SETREPORT, (USB_REPTYPE_OUTPUT<<8) | 0x01, 0x0,
                  adapter->send_control_size, adapter->send_control_buffer);
         } while (r < 0);
         break;
      /*default:  any other case we do nothing */
   }
   /* Reset the control type */
   adapter->send_control_type = WIIUSB_SC_NONE;
}