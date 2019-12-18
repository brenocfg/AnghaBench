#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct usb_interface {TYPE_1__ dev; } ;
struct usb_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ supports_autosuspend; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int sprintf (char*,char*,int) ; 
 TYPE_2__* to_usb_driver (int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static ssize_t show_supports_autosuspend(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct usb_interface *intf;
	struct usb_device *udev;
	int ret;

	intf = to_usb_interface(dev);
	udev = interface_to_usbdev(intf);

	usb_lock_device(udev);
	/* Devices will be autosuspended even when an interface isn't claimed */
	if (!intf->dev.driver ||
			to_usb_driver(intf->dev.driver)->supports_autosuspend)
		ret = sprintf(buf, "%u\n", 1);
	else
		ret = sprintf(buf, "%u\n", 0);
	usb_unlock_device(udev);

	return ret;
}