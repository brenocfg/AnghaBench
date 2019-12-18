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
 int NOTIFY_BAD ; 
 int NOTIFY_OK ; 
#define  USB_DEVICE_ADD 129 
#define  USB_DEVICE_REMOVE 128 
 int /*<<< orphan*/  usb_classdev_add (void*) ; 
 int /*<<< orphan*/  usb_classdev_remove (void*) ; 
 int /*<<< orphan*/  usbdev_remove (void*) ; 

__attribute__((used)) static int usbdev_notify(struct notifier_block *self,
			       unsigned long action, void *dev)
{
	switch (action) {
	case USB_DEVICE_ADD:
		if (usb_classdev_add(dev))
			return NOTIFY_BAD;
		break;
	case USB_DEVICE_REMOVE:
		usb_classdev_remove(dev);
		usbdev_remove(dev);
		break;
	}
	return NOTIFY_OK;
}