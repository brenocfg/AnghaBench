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
struct TYPE_3__ {int device_detected; struct wiiusb_adapter* adapters_head; int /*<<< orphan*/  poll_thread_quit; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
struct wiiusb_adapter {int busy; int /*<<< orphan*/  data; int /*<<< orphan*/  endpoint_in_max_size; int /*<<< orphan*/  endpoint_in; int /*<<< orphan*/  handle; scalar_t__ send_control_type; struct wiiusb_adapter* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ReadIntrMsgAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wiiusb_adapter*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  wiiusb_hid_process_control_message (struct wiiusb_adapter*) ; 
 int /*<<< orphan*/  wiiusb_hid_read_cb ; 
 int /*<<< orphan*/  wiiusb_hid_scan_for_devices (TYPE_1__*) ; 

__attribute__((used)) static void wiiusb_hid_poll_thread(void *data)
{
   wiiusb_hid_t              *hid = (wiiusb_hid_t*)data;
   struct wiiusb_adapter *adapter = NULL;

   if (!hid)
      return;

   while (!hid->poll_thread_quit)
   {

      /* first check for new devices */
      if (hid->device_detected)
      {
         /* turn off the detection flag */
         hid->device_detected = false;
         /* search for new pads and add them as needed */
         wiiusb_hid_scan_for_devices(hid);
      }

      /* process each active adapter */
      for (adapter = hid->adapters_head; adapter; adapter=adapter->next)
      {
         if (adapter->busy)
            continue;

         /* lock itself while writing or reading */
         adapter->busy = true;

         if (adapter->send_control_type)
            wiiusb_hid_process_control_message(adapter);

         USB_ReadIntrMsgAsync(adapter->handle, adapter->endpoint_in,
               adapter->endpoint_in_max_size,
               adapter->data, wiiusb_hid_read_cb, adapter);
      }

      /* Wait 10 milliseconds to process again */
      usleep(10000);
   }
}