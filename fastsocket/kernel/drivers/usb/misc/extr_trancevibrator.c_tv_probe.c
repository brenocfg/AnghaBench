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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct trancevibrator {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_speed ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct trancevibrator*) ; 
 struct trancevibrator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct trancevibrator*) ; 

__attribute__((used)) static int tv_probe(struct usb_interface *interface,
		    const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct trancevibrator *dev;
	int retval;

	dev = kzalloc(sizeof(struct trancevibrator), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		retval = -ENOMEM;
		goto error;
	}

	dev->udev = usb_get_dev(udev);
	usb_set_intfdata(interface, dev);
	retval = device_create_file(&interface->dev, &dev_attr_speed);
	if (retval)
		goto error_create_file;

	return 0;

error_create_file:
	usb_put_dev(udev);
	usb_set_intfdata(interface, NULL);
error:
	kfree(dev);
	return retval;
}