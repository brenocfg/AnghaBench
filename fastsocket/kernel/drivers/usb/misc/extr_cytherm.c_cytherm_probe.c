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
struct usb_cytherm {int brightness; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_brightness ; 
 int /*<<< orphan*/  dev_attr_button ; 
 int /*<<< orphan*/  dev_attr_port0 ; 
 int /*<<< orphan*/  dev_attr_port1 ; 
 int /*<<< orphan*/  dev_attr_temp ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usb_cytherm*) ; 
 struct usb_cytherm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_cytherm*) ; 

__attribute__((used)) static int cytherm_probe(struct usb_interface *interface, 
			 const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_cytherm *dev = NULL;
	int retval = -ENOMEM;

	dev = kzalloc (sizeof(struct usb_cytherm), GFP_KERNEL);
	if (dev == NULL) {
		dev_err (&interface->dev, "Out of memory\n");
		goto error_mem;
	}

	dev->udev = usb_get_dev(udev);

	usb_set_intfdata (interface, dev);

	dev->brightness = 0xFF;

	retval = device_create_file(&interface->dev, &dev_attr_brightness);
	if (retval)
		goto error;
	retval = device_create_file(&interface->dev, &dev_attr_temp);
	if (retval)
		goto error;
	retval = device_create_file(&interface->dev, &dev_attr_button);
	if (retval)
		goto error;
	retval = device_create_file(&interface->dev, &dev_attr_port0);
	if (retval)
		goto error;
	retval = device_create_file(&interface->dev, &dev_attr_port1);
	if (retval)
		goto error;

	dev_info (&interface->dev,
		  "Cypress thermometer device now attached\n");
	return 0;
error:
	device_remove_file(&interface->dev, &dev_attr_brightness);
	device_remove_file(&interface->dev, &dev_attr_temp);
	device_remove_file(&interface->dev, &dev_attr_button);
	device_remove_file(&interface->dev, &dev_attr_port0);
	device_remove_file(&interface->dev, &dev_attr_port1);
	usb_set_intfdata (interface, NULL);
	usb_put_dev(dev->udev);
	kfree(dev);
error_mem:
	return retval;
}