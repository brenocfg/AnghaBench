#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; TYPE_1__* private_data; scalar_t__ f_pos; } ;
typedef  TYPE_1__* pdabusb_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int opened; int /*<<< orphan*/  mutex; TYPE_2__* usbdev; } ;

/* Variables and functions */
 int DABUSB_MINOR ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int NRDABUSB ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  _DABUSB_IF ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* dabusb ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_set_interface (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dabusb_open (struct inode *inode, struct file *file)
{
	int devnum = iminor(inode);
	pdabusb_t s;

	if (devnum < DABUSB_MINOR || devnum >= (DABUSB_MINOR + NRDABUSB))
		return -EIO;

	s = &dabusb[devnum - DABUSB_MINOR];

	dbg("dabusb_open");
	mutex_lock(&s->mutex);

	while (!s->usbdev || s->opened) {
		mutex_unlock(&s->mutex);

		if (file->f_flags & O_NONBLOCK) {
			return -EBUSY;
		}
		msleep_interruptible(500);

		if (signal_pending (current)) {
			return -EAGAIN;
		}
		mutex_lock(&s->mutex);
	}
	if (usb_set_interface (s->usbdev, _DABUSB_IF, 1) < 0) {
		mutex_unlock(&s->mutex);
		dev_err(&s->usbdev->dev, "set_interface failed\n");
		return -EINVAL;
	}
	s->opened = 1;
	mutex_unlock(&s->mutex);

	file->f_pos = 0;
	file->private_data = s;

	return nonseekable_open(inode, file);
}