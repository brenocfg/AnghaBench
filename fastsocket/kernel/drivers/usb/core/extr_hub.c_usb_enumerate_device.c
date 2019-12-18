#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  iProduct; } ;
struct usb_device {int wusb; scalar_t__ authorized; TYPE_1__ descriptor; void* serial; void* manufacturer; void* product; int /*<<< orphan*/  dev; int /*<<< orphan*/ * config; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 void* usb_cache_string (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_enumerate_device_otg (struct usb_device*) ; 
 int usb_get_configuration (struct usb_device*) ; 

__attribute__((used)) static int usb_enumerate_device(struct usb_device *udev)
{
	int err;

	if (udev->config == NULL) {
		err = usb_get_configuration(udev);
		if (err < 0) {
			dev_err(&udev->dev, "can't read configurations, error %d\n",
				err);
			goto fail;
		}
	}
	if (udev->wusb == 1 && udev->authorized == 0) {
		udev->product = kstrdup("n/a (unauthorized)", GFP_KERNEL);
		udev->manufacturer = kstrdup("n/a (unauthorized)", GFP_KERNEL);
		udev->serial = kstrdup("n/a (unauthorized)", GFP_KERNEL);
	}
	else {
		/* read the standard strings and cache them if present */
		udev->product = usb_cache_string(udev, udev->descriptor.iProduct);
		udev->manufacturer = usb_cache_string(udev,
						      udev->descriptor.iManufacturer);
		udev->serial = usb_cache_string(udev, udev->descriptor.iSerialNumber);
	}
	err = usb_enumerate_device_otg(udev);
fail:
	return err;
}