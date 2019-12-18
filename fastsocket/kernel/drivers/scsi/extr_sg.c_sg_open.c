#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct inode {int dummy; } ;
struct file {int f_flags; int /*<<< orphan*/ * private_data; } ;
struct TYPE_11__ {struct request_queue* request_queue; } ;
struct TYPE_10__ {int exclude; TYPE_5__* device; int /*<<< orphan*/  o_excl_wait; int /*<<< orphan*/  sg_tablesize; scalar_t__ sgdebug; int /*<<< orphan*/  sfds; scalar_t__ detached; } ;
typedef  int /*<<< orphan*/  Sg_fd ;
typedef  TYPE_1__ Sg_device ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPERM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int O_ACCMODE ; 
 int O_EXCL ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SCSI_LOG_TIMEOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait_event_interruptible (int /*<<< orphan*/ ,int,int) ; 
 int iminor (struct inode*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int /*<<< orphan*/  queue_max_segments (struct request_queue*) ; 
 scalar_t__ scsi_block_when_processing_errors (TYPE_5__*) ; 
 int scsi_device_get (TYPE_5__*) ; 
 int /*<<< orphan*/  scsi_device_put (TYPE_5__*) ; 
 int /*<<< orphan*/ * sg_add_sfp (TYPE_1__*,int) ; 
 TYPE_1__* sg_get_dev (int) ; 
 int /*<<< orphan*/  sg_put_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sg_open(struct inode *inode, struct file *filp)
{
	int dev = iminor(inode);
	int flags = filp->f_flags;
	struct request_queue *q;
	Sg_device *sdp;
	Sg_fd *sfp;
	int res;
	int retval;

	lock_kernel();
	nonseekable_open(inode, filp);
	SCSI_LOG_TIMEOUT(3, printk("sg_open: dev=%d, flags=0x%x\n", dev, flags));
	sdp = sg_get_dev(dev);
	if (IS_ERR(sdp)) {
		retval = PTR_ERR(sdp);
		sdp = NULL;
		goto sg_put;
	}

	/* This driver's module count bumped by fops_get in <linux/fs.h> */
	/* Prevent the device driver from vanishing while we sleep */
	retval = scsi_device_get(sdp->device);
	if (retval)
		goto sg_put;

	if (!((flags & O_NONBLOCK) ||
	      scsi_block_when_processing_errors(sdp->device))) {
		retval = -ENXIO;
		/* we are in error recovery for this device */
		goto error_out;
	}

	if (flags & O_EXCL) {
		if (O_RDONLY == (flags & O_ACCMODE)) {
			retval = -EPERM; /* Can't lock it with read only access */
			goto error_out;
		}
		if (!list_empty(&sdp->sfds) && (flags & O_NONBLOCK)) {
			retval = -EBUSY;
			goto error_out;
		}
		res = 0;
		__wait_event_interruptible(sdp->o_excl_wait,
					   ((!list_empty(&sdp->sfds) || sdp->exclude) ? 0 : (sdp->exclude = 1)), res);
		if (res) {
			retval = res;	/* -ERESTARTSYS because signal hit process */
			goto error_out;
		}
	} else if (sdp->exclude) {	/* some other fd has an exclusive lock on dev */
		if (flags & O_NONBLOCK) {
			retval = -EBUSY;
			goto error_out;
		}
		res = 0;
		__wait_event_interruptible(sdp->o_excl_wait, (!sdp->exclude),
					   res);
		if (res) {
			retval = res;	/* -ERESTARTSYS because signal hit process */
			goto error_out;
		}
	}
	if (sdp->detached) {
		retval = -ENODEV;
		goto error_out;
	}
	if (list_empty(&sdp->sfds)) {	/* no existing opens on this device */
		sdp->sgdebug = 0;
		q = sdp->device->request_queue;
		sdp->sg_tablesize = queue_max_segments(q);
	}
	if ((sfp = sg_add_sfp(sdp, dev)))
		filp->private_data = sfp;
	else {
		if (flags & O_EXCL) {
			sdp->exclude = 0;	/* undo if error */
			wake_up_interruptible(&sdp->o_excl_wait);
		}
		retval = -ENOMEM;
		goto error_out;
	}
	retval = 0;
error_out:
	if (retval)
		scsi_device_put(sdp->device);
sg_put:
	if (sdp)
		sg_put_dev(sdp);
	unlock_kernel();
	return retval;
}