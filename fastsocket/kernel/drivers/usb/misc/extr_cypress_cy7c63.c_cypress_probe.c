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
struct cypress {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_port0 ; 
 int /*<<< orphan*/  dev_attr_port1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct cypress*) ; 
 struct cypress* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct cypress*) ; 

__attribute__((used)) static int cypress_probe(struct usb_interface *interface,
			 const struct usb_device_id *id)
{
	struct cypress *dev = NULL;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory!\n");
		goto error_mem;
	}

	dev->udev = usb_get_dev(interface_to_usbdev(interface));

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* create device attribute files */
	retval = device_create_file(&interface->dev, &dev_attr_port0);
	if (retval)
		goto error;
	retval = device_create_file(&interface->dev, &dev_attr_port1);
	if (retval)
		goto error;

	/* let the user know that the device is now attached */
	dev_info(&interface->dev,
		 "Cypress CY7C63xxx device now attached\n");
	return 0;

error:
	device_remove_file(&interface->dev, &dev_attr_port0);
	device_remove_file(&interface->dev, &dev_attr_port1);
	usb_set_intfdata(interface, NULL);
	usb_put_dev(dev->udev);
	kfree(dev);

error_mem:
	return retval;
}