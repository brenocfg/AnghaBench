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
struct usb_interface {int dummy; } ;
struct usb_idmouse {int /*<<< orphan*/  lock; scalar_t__ open; } ;
struct inode {int dummy; } ;
struct file {struct usb_idmouse* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int idmouse_create_image (struct usb_idmouse*) ; 
 int /*<<< orphan*/  idmouse_driver ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_disc_mutex ; 
 int usb_autopm_get_interface (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (struct usb_interface*) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_idmouse* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int idmouse_open(struct inode *inode, struct file *file)
{
	struct usb_idmouse *dev;
	struct usb_interface *interface;
	int result;

	/* get the interface from minor number and driver information */
	interface = usb_find_interface (&idmouse_driver, iminor (inode));
	if (!interface)
		return -ENODEV;

	mutex_lock(&open_disc_mutex);
	/* get the device information block from the interface */
	dev = usb_get_intfdata(interface);
	if (!dev) {
		mutex_unlock(&open_disc_mutex);
		return -ENODEV;
	}

	/* lock this device */
	mutex_lock(&dev->lock);
	mutex_unlock(&open_disc_mutex);

	/* check if already open */
	if (dev->open) {

		/* already open, so fail */
		result = -EBUSY;

	} else {

		/* create a new image and check for success */
		result = usb_autopm_get_interface(interface);
		if (result)
			goto error;
		result = idmouse_create_image (dev);
		if (result)
			goto error;
		usb_autopm_put_interface(interface);

		/* increment our usage count for the driver */
		++dev->open;

		/* save our object in the file's private structure */
		file->private_data = dev;

	} 

error:

	/* unlock this device */
	mutex_unlock(&dev->lock);
	return result;
}