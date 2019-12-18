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
struct usb_device {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct dev_state* private_data; } ;
struct dev_state {int /*<<< orphan*/  disc_pid; scalar_t__ ifclaimed; int /*<<< orphan*/  list; struct usb_device* dev; } ;
struct async {int dummy; } ;

/* Variables and functions */
 struct async* async_getcompleted (struct dev_state*) ; 
 int /*<<< orphan*/  destroy_all_async (struct dev_state*) ; 
 int /*<<< orphan*/  free_async (struct async*) ; 
 int /*<<< orphan*/  kfree (struct dev_state*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releaseintf (struct dev_state*,unsigned int) ; 
 scalar_t__ test_bit (unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  usb_autosuspend_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_hub_release_all_ports (struct usb_device*,struct dev_state*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usbfs_mutex ; 

__attribute__((used)) static int usbdev_release(struct inode *inode, struct file *file)
{
	struct dev_state *ps = file->private_data;
	struct usb_device *dev = ps->dev;
	unsigned int ifnum;
	struct async *as;

	usb_lock_device(dev);
	usb_hub_release_all_ports(dev, ps);

	/* Protect against simultaneous open */
	mutex_lock(&usbfs_mutex);
	list_del_init(&ps->list);
	mutex_unlock(&usbfs_mutex);

	for (ifnum = 0; ps->ifclaimed && ifnum < 8*sizeof(ps->ifclaimed);
			ifnum++) {
		if (test_bit(ifnum, &ps->ifclaimed))
			releaseintf(ps, ifnum);
	}
	destroy_all_async(ps);
	usb_autosuspend_device(dev);
	usb_unlock_device(dev);
	usb_put_dev(dev);
	put_pid(ps->disc_pid);

	as = async_getcompleted(ps);
	while (as) {
		free_async(as);
		as = async_getcompleted(ps);
	}
	kfree(ps);
	return 0;
}