#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int is_keyboard; int is_mouse; int /*<<< orphan*/  max_packet_size_tx; int /*<<< orphan*/  max_packet_size_rx; int /*<<< orphan*/  interface_index; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  handle; int /*<<< orphan*/ * driver; } ;
typedef  TYPE_1__ wiiu_attach_event ;
typedef  int /*<<< orphan*/  hid_device_t ;
struct TYPE_7__ {int sub_class; int protocol; int /*<<< orphan*/  max_packet_size_tx; int /*<<< orphan*/  max_packet_size_rx; int /*<<< orphan*/  interface_index; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ HIDDevice ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* alloc_zeroed (int,int) ; 
 int /*<<< orphan*/ * hid_device_driver_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static wiiu_attach_event *new_attach_event(HIDDevice *device)
{
   hid_device_t *driver = hid_device_driver_lookup(device->vid, device->pid);
   if (!driver)
   {
      RARCH_ERR("[hid]: Failed to locate driver for device vid=%04x pid=%04x\n",
        device->vid, device->pid);
      return NULL;
   }
   wiiu_attach_event *event = alloc_zeroed(4, sizeof(wiiu_attach_event));
   if (!event)
      return NULL;

   event->driver             = driver;
   event->handle             = device->handle;
   event->vendor_id          = device->vid;
   event->product_id         = device->pid;
   event->interface_index    = device->interface_index;
   event->is_keyboard        = (device->sub_class == 1
         && device->protocol == 1);
   event->is_mouse           = (device->sub_class == 1
         && device->protocol == 2);
   event->max_packet_size_rx = device->max_packet_size_rx;
   event->max_packet_size_tx = device->max_packet_size_tx;

   return event;
}