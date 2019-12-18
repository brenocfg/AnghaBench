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
struct usb_device {scalar_t__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int usb_remove_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static ssize_t usb_remove_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct usb_device *udev = to_usb_device(dev);
	int rc = 0;

	usb_lock_device(udev);
	if (udev->state != USB_STATE_NOTATTACHED) {

		/* To avoid races, first unconfigure and then remove */
		usb_set_configuration(udev, -1);
		rc = usb_remove_device(udev);
	}
	if (rc == 0)
		rc = count;
	usb_unlock_device(udev);
	return rc;
}