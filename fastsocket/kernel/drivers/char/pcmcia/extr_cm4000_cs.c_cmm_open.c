#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int open; struct cm4000_dev* priv; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct cm4000_dev* private_data; } ;
struct cm4000_dev {int /*<<< orphan*/  mdelay; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int CM4000_MAX_DEV ; 
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*,...) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENODEV ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  T_50MSEC ; 
 int /*<<< orphan*/  ZERO_DEV (struct cm4000_dev*) ; 
 TYPE_1__* current ; 
 struct pcmcia_device** dev_table ; 
 int /*<<< orphan*/  imajor (struct inode*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  start_monitor (struct cm4000_dev*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int cmm_open(struct inode *inode, struct file *filp)
{
	struct cm4000_dev *dev;
	struct pcmcia_device *link;
	int minor = iminor(inode);
	int ret;

	if (minor >= CM4000_MAX_DEV)
		return -ENODEV;

	lock_kernel();
	link = dev_table[minor];
	if (link == NULL || !pcmcia_dev_present(link)) {
		ret = -ENODEV;
		goto out;
	}

	if (link->open) {
		ret = -EBUSY;
		goto out;
	}

	dev = link->priv;
	filp->private_data = dev;

	DEBUGP(2, dev, "-> cmm_open(device=%d.%d process=%s,%d)\n",
	      imajor(inode), minor, current->comm, current->pid);

	/* init device variables, they may be "polluted" after close
	 * or, the device may never have been closed (i.e. open failed)
	 */

	ZERO_DEV(dev);

	/* opening will always block since the
	 * monitor will be started by open, which
	 * means we have to wait for ATR becoming
	 * vaild = block until valid (or card
	 * inserted)
	 */
	if (filp->f_flags & O_NONBLOCK) {
		ret = -EAGAIN;
		goto out;
	}

	dev->mdelay = T_50MSEC;

	/* start monitoring the cardstatus */
	start_monitor(dev);

	link->open = 1;		/* only one open per device */

	DEBUGP(2, dev, "<- cmm_open\n");
	ret = nonseekable_open(inode, filp);
out:
	unlock_kernel();
	return ret;
}