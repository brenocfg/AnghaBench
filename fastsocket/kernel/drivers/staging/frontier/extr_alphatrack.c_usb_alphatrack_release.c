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
struct usb_alphatrack {int open_count; int /*<<< orphan*/  sem; scalar_t__ interrupt_out_busy; int /*<<< orphan*/  write_wait; int /*<<< orphan*/ * intf; } ;
struct inode {int dummy; } ;
struct file {struct usb_alphatrack* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERESTARTSYS ; 
 int HZ ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alphatrack_abort_transfers (struct usb_alphatrack*) ; 
 int /*<<< orphan*/  usb_alphatrack_delete (struct usb_alphatrack*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int usb_alphatrack_release(struct inode *inode, struct file *file)
{
	struct usb_alphatrack *dev;
	int retval = 0;

	dev = file->private_data;

	if (dev == NULL) {
		retval = -ENODEV;
		goto exit;
	}

	if (down_interruptible(&dev->sem)) {
		retval = -ERESTARTSYS;
		goto exit;
	}

	if (dev->open_count != 1) {
		retval = -ENODEV;
		goto unlock_exit;
	}

	if (dev->intf == NULL) {
		/* the device was unplugged before the file was released */
		up(&dev->sem);
		/* unlock here as usb_alphatrack_delete frees dev */
		usb_alphatrack_delete(dev);
		retval = -ENODEV;
		goto exit;
	}

	/* wait until write transfer is finished */
	if (dev->interrupt_out_busy)
		wait_event_interruptible_timeout(dev->write_wait,
						 !dev->interrupt_out_busy,
						 2 * HZ);
	usb_alphatrack_abort_transfers(dev);
	dev->open_count = 0;

unlock_exit:
	up(&dev->sem);

exit:
	return retval;
}