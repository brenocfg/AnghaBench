#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  devt; } ;
struct usb_device {int devnum; int /*<<< orphan*/  ep0; TYPE_2__ dev; TYPE_1__* bus; scalar_t__ parent; } ;
struct TYPE_8__ {int busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_DEVICE_MAJOR ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  announce_device (struct usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  usb_autoresume_device (scalar_t__) ; 
 int /*<<< orphan*/  usb_create_ep_devs (TYPE_2__*,int /*<<< orphan*/ *,struct usb_device*) ; 
 int /*<<< orphan*/  usb_detect_quirks (struct usb_device*) ; 
 int usb_enumerate_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stop_pm (struct usb_device*) ; 

int usb_new_device(struct usb_device *udev)
{
	int err;

	if (udev->parent) {
		/* Increment the parent's count of unsuspended children */
		usb_autoresume_device(udev->parent);

		/* Initialize non-root-hub device wakeup to disabled;
		 * device (un)configuration controls wakeup capable
		 * sysfs power/wakeup controls wakeup enabled/disabled
		 */
		device_init_wakeup(&udev->dev, 0);
		device_set_wakeup_enable(&udev->dev, 1);
	}

	usb_detect_quirks(udev);
	err = usb_enumerate_device(udev);	/* Read descriptors */
	if (err < 0)
		goto fail;
	dev_dbg(&udev->dev, "udev %d, busnum %d, minor = %d\n",
			udev->devnum, udev->bus->busnum,
			(((udev->bus->busnum-1) * 128) + (udev->devnum-1)));
	/* export the usbdev device-node for libusb */
	udev->dev.devt = MKDEV(USB_DEVICE_MAJOR,
			(((udev->bus->busnum-1) * 128) + (udev->devnum-1)));

	/* Tell the world! */
	announce_device(udev);

	/* Register the device.  The device driver is responsible
	 * for configuring the device and invoking the add-device
	 * notifier chain (used by usbfs and possibly others).
	 */
	err = device_add(&udev->dev);
	if (err) {
		dev_err(&udev->dev, "can't device_add, error %d\n", err);
		goto fail;
	}

	(void) usb_create_ep_devs(&udev->dev, &udev->ep0, udev);
	return err;

fail:
	usb_set_device_state(udev, USB_STATE_NOTATTACHED);
	usb_stop_pm(udev);
	return err;
}