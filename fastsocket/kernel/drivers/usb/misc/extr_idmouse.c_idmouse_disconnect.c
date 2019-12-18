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
struct usb_idmouse {int /*<<< orphan*/  lock; int /*<<< orphan*/  open; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  idmouse_class ; 
 int /*<<< orphan*/  idmouse_delete (struct usb_idmouse*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_disc_mutex ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usb_idmouse* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idmouse_disconnect(struct usb_interface *interface)
{
	struct usb_idmouse *dev;

	/* get device structure */
	dev = usb_get_intfdata(interface);

	/* give back our minor */
	usb_deregister_dev(interface, &idmouse_class);

	mutex_lock(&open_disc_mutex);
	usb_set_intfdata(interface, NULL);
	/* lock the device */
	mutex_lock(&dev->lock);
	mutex_unlock(&open_disc_mutex);

	/* prevent device read, write and ioctl */
	dev->present = 0;

	/* if the device is opened, idmouse_release will clean this up */
	if (!dev->open) {
		mutex_unlock(&dev->lock);
		idmouse_delete(dev);
	} else {
		/* unlock */
		mutex_unlock(&dev->lock);
	}

	dev_info(&interface->dev, "disconnected\n");
}