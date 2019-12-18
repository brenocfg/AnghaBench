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
struct usb_device {scalar_t__ authorized; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int usb_choose_configuration (struct usb_device*) ; 
 scalar_t__ usb_device_is_owned (struct usb_device*) ; 
 int /*<<< orphan*/  usb_notify_add_device (struct usb_device*) ; 
 int usb_set_configuration (struct usb_device*,int) ; 

__attribute__((used)) static int generic_probe(struct usb_device *udev)
{
	int err, c;

	/* Choose and set the configuration.  This registers the interfaces
	 * with the driver core and lets interface drivers bind to them.
	 */
	if (usb_device_is_owned(udev))
		;		/* Don't configure if the device is owned */
	else if (udev->authorized == 0)
		dev_err(&udev->dev, "Device is not authorized for usage\n");
	else {
		c = usb_choose_configuration(udev);
		if (c >= 0) {
			err = usb_set_configuration(udev, c);
			if (err) {
				dev_err(&udev->dev, "can't set config #%d, error %d\n",
					c, err);
				/* This need not be fatal.  The user can try to
				 * set other configurations. */
			}
		}
	}
	/* USB device state == configured ... usable */
	usb_notify_add_device(udev);

	return 0;
}