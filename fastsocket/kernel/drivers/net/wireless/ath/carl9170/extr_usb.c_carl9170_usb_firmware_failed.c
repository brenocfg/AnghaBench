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
struct TYPE_2__ {struct device* parent; } ;
struct usb_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  fw_load_wait; struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void carl9170_usb_firmware_failed(struct ar9170 *ar)
{
	struct device *parent = ar->udev->dev.parent;
	struct usb_device *udev;

	/*
	 * Store a copy of the usb_device pointer locally.
	 * This is because device_release_driver initiates
	 * carl9170_usb_disconnect, which in turn frees our
	 * driver context (ar).
	 */
	udev = ar->udev;

	complete(&ar->fw_load_wait);

	/* unbind anything failed */
	if (parent)
		device_lock(parent);

	device_release_driver(&udev->dev);
	if (parent)
		device_unlock(parent);

	usb_put_dev(udev);
}