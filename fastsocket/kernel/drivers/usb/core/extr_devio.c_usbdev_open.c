#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_device {scalar_t__ state; int /*<<< orphan*/  dev; int /*<<< orphan*/  filelist; TYPE_1__* usbfs_dentry; } ;
struct inode {struct usb_device* i_private; int /*<<< orphan*/  i_rdev; } ;
struct file {struct dev_state* private_data; } ;
struct dev_state {int /*<<< orphan*/  list; int /*<<< orphan*/  secid; scalar_t__ ifclaimed; int /*<<< orphan*/ * disccontext; int /*<<< orphan*/  disc_euid; int /*<<< orphan*/  disc_uid; int /*<<< orphan*/  disc_pid; scalar_t__ discsignr; int /*<<< orphan*/  wait; int /*<<< orphan*/  async_completed; int /*<<< orphan*/  async_pending; int /*<<< orphan*/  lock; struct file* file; struct usb_device* dev; } ;
struct cred {int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
struct TYPE_7__ {int /*<<< orphan*/  comm; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_DEVICE_MAJOR ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 TYPE_2__* current ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ imajor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dev_state*) ; 
 struct dev_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_task_getsecid (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  snoop (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (TYPE_2__*) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_2__*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int usb_autoresume_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 struct usb_device* usbdev_lookup_by_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbfs_mutex ; 

__attribute__((used)) static int usbdev_open(struct inode *inode, struct file *file)
{
	struct usb_device *dev = NULL;
	struct dev_state *ps;
	const struct cred *cred = current_cred();
	int ret;

	lock_kernel();
	/* Protect against simultaneous removal or release */
	mutex_lock(&usbfs_mutex);

	ret = -ENOMEM;
	ps = kmalloc(sizeof(struct dev_state), GFP_KERNEL);
	if (!ps)
		goto out;

	ret = -ENODEV;

	/* usbdev device-node */
	if (imajor(inode) == USB_DEVICE_MAJOR)
		dev = usbdev_lookup_by_devt(inode->i_rdev);
#ifdef CONFIG_USB_DEVICEFS
	/* procfs file */
	if (!dev) {
		dev = inode->i_private;
		if (dev && dev->usbfs_dentry &&
					dev->usbfs_dentry->d_inode == inode)
			usb_get_dev(dev);
		else
			dev = NULL;
	}
#endif
	if (!dev || dev->state == USB_STATE_NOTATTACHED)
		goto out;
	ret = usb_autoresume_device(dev);
	if (ret)
		goto out;

	ret = 0;
	ps->dev = dev;
	ps->file = file;
	spin_lock_init(&ps->lock);
	INIT_LIST_HEAD(&ps->list);
	INIT_LIST_HEAD(&ps->async_pending);
	INIT_LIST_HEAD(&ps->async_completed);
	init_waitqueue_head(&ps->wait);
	ps->discsignr = 0;
	ps->disc_pid = get_pid(task_pid(current));
	ps->disc_uid = cred->uid;
	ps->disc_euid = cred->euid;
	ps->disccontext = NULL;
	ps->ifclaimed = 0;
	security_task_getsecid(current, &ps->secid);
	smp_wmb();
	list_add_tail(&ps->list, &dev->filelist);
	file->private_data = ps;
	snoop(&dev->dev, "opened by process %d: %s\n", task_pid_nr(current),
			current->comm);
 out:
	if (ret) {
		kfree(ps);
		usb_put_dev(dev);
	}
	mutex_unlock(&usbfs_mutex);
	unlock_kernel();
	return ret;
}