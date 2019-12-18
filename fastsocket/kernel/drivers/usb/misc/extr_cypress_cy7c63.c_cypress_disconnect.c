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
struct cypress {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_port0 ; 
 int /*<<< orphan*/  dev_attr_port1 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cypress*) ; 
 struct cypress* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cypress_disconnect(struct usb_interface *interface)
{
	struct cypress *dev;

	dev = usb_get_intfdata(interface);

	/* remove device attribute files */
	device_remove_file(&interface->dev, &dev_attr_port0);
	device_remove_file(&interface->dev, &dev_attr_port1);
	/* the intfdata can be set to NULL only after the
	 * device files have been removed */
	usb_set_intfdata(interface, NULL);

	usb_put_dev(dev->udev);

	dev_info(&interface->dev,
		 "Cypress CY7C63xxx device now disconnected\n");

	kfree(dev);
}