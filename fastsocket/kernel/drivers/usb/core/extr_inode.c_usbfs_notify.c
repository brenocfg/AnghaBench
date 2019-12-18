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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
#define  USB_BUS_ADD 131 
#define  USB_BUS_REMOVE 130 
#define  USB_DEVICE_ADD 129 
#define  USB_DEVICE_REMOVE 128 
 int /*<<< orphan*/  usbfs_add_bus (void*) ; 
 int /*<<< orphan*/  usbfs_add_device (void*) ; 
 int /*<<< orphan*/  usbfs_conn_disc_event () ; 
 int /*<<< orphan*/  usbfs_remove_bus (void*) ; 
 int /*<<< orphan*/  usbfs_remove_device (void*) ; 
 int /*<<< orphan*/  usbfs_update_special () ; 

__attribute__((used)) static int usbfs_notify(struct notifier_block *self, unsigned long action, void *dev)
{
	switch (action) {
	case USB_DEVICE_ADD:
		usbfs_add_device(dev);
		break;
	case USB_DEVICE_REMOVE:
		usbfs_remove_device(dev);
		break;
	case USB_BUS_ADD:
		usbfs_add_bus(dev);
		break;
	case USB_BUS_REMOVE:
		usbfs_remove_bus(dev);
	}

	usbfs_update_special();
	usbfs_conn_disc_event();
	return NOTIFY_OK;
}