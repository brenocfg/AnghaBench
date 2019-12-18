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
struct usb_skel {int ongoing_read; size_t bulk_in_copied; int processed_urb; int errors; size_t bulk_in_filled; size_t bulk_in_buffer; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  bulk_in_completion; int /*<<< orphan*/  err_lock; int /*<<< orphan*/  interface; int /*<<< orphan*/  bulk_in_urb; } ;
struct file {int f_flags; scalar_t__ private_data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int EIO ; 
 int ENODEV ; 
 int EPIPE ; 
 int O_NONBLOCK ; 
 scalar_t__ copy_to_user (char*,size_t,size_t) ; 
 size_t min (size_t,size_t) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int skel_do_read_io (struct usb_skel*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t skel_read(struct file *file, char *buffer, size_t count,
			 loff_t *ppos)
{
	struct usb_skel *dev;
	int rv;
	bool ongoing_io;

	dev = (struct usb_skel *)file->private_data;

	/* if we cannot read at all, return EOF */
	if (!dev->bulk_in_urb || !count)
		return 0;

	/* no concurrent readers */
	rv = mutex_lock_interruptible(&dev->io_mutex);
	if (rv < 0)
		return rv;

	if (!dev->interface) {		/* disconnect() was called */
		rv = -ENODEV;
		goto exit;
	}

	/* if IO is under way, we must not touch things */
retry:
	spin_lock_irq(&dev->err_lock);
	ongoing_io = dev->ongoing_read;
	spin_unlock_irq(&dev->err_lock);

	if (ongoing_io) {
		/* nonblocking IO shall not wait */
		if (file->f_flags & O_NONBLOCK) {
			rv = -EAGAIN;
			goto exit;
		}
		/*
		 * IO may take forever
		 * hence wait in an interruptible state
		 */
		rv = wait_for_completion_interruptible(&dev->bulk_in_completion);
		if (rv < 0)
			goto exit;
		/*
		 * by waiting we also semiprocessed the urb
		 * we must finish now
		 */
		dev->bulk_in_copied = 0;
		dev->processed_urb = 1;
	}

	if (!dev->processed_urb) {
		/*
		 * the URB hasn't been processed
		 * do it now
		 */
		wait_for_completion(&dev->bulk_in_completion);
		dev->bulk_in_copied = 0;
		dev->processed_urb = 1;
	}

	/* errors must be reported */
	rv = dev->errors;
	if (rv < 0) {
		/* any error is reported once */
		dev->errors = 0;
		/* to preserve notifications about reset */
		rv = (rv == -EPIPE) ? rv : -EIO;
		/* no data to deliver */
		dev->bulk_in_filled = 0;
		/* report it */
		goto exit;
	}

	/*
	 * if the buffer is filled we may satisfy the read
	 * else we need to start IO
	 */

	if (dev->bulk_in_filled) {
		/* we had read data */
		size_t available = dev->bulk_in_filled - dev->bulk_in_copied;
		size_t chunk = min(available, count);

		if (!available) {
			/*
			 * all data has been used
			 * actual IO needs to be done
			 */
			rv = skel_do_read_io(dev, count);
			if (rv < 0)
				goto exit;
			else
				goto retry;
		}
		/*
		 * data is available
		 * chunk tells us how much shall be copied
		 */

		if (copy_to_user(buffer,
				 dev->bulk_in_buffer + dev->bulk_in_copied,
				 chunk))
			rv = -EFAULT;
		else
			rv = chunk;

		dev->bulk_in_copied += chunk;

		/*
		 * if we are asked for more than we have,
		 * we start IO but don't wait
		 */
		if (available < count)
			skel_do_read_io(dev, count - chunk);
	} else {
		/* no data in the buffer */
		rv = skel_do_read_io(dev, count);
		if (rv < 0)
			goto exit;
		else if (!file->f_flags & O_NONBLOCK)
			goto retry;
		rv = -EAGAIN;
	}
exit:
	mutex_unlock(&dev->io_mutex);
	return rv;
}