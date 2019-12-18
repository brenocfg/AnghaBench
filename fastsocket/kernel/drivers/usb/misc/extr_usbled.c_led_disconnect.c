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
struct usb_led {int /*<<< orphan*/  udev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_blue ; 
 int /*<<< orphan*/  dev_attr_green ; 
 int /*<<< orphan*/  dev_attr_red ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usb_led*) ; 
 struct usb_led* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void led_disconnect(struct usb_interface *interface)
{
	struct usb_led *dev;

	dev = usb_get_intfdata (interface);

	device_remove_file(&interface->dev, &dev_attr_blue);
	device_remove_file(&interface->dev, &dev_attr_red);
	device_remove_file(&interface->dev, &dev_attr_green);

	/* first remove the files, then set the pointer to NULL */
	usb_set_intfdata (interface, NULL);

	usb_put_dev(dev->udev);

	kfree(dev);

	dev_info(&interface->dev, "USB LED now disconnected\n");
}