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
struct gspca_dev {scalar_t__ memory; scalar_t__ fr_o; int /*<<< orphan*/  present; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  fr_i; int /*<<< orphan*/  wq; } ;
struct file {struct gspca_dev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  D_FRAM ; 
 scalar_t__ GSPCA_MEMORY_NO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_alloc (struct gspca_dev*,struct file*) ; 

__attribute__((used)) static unsigned int dev_poll(struct file *file, poll_table *wait)
{
	struct gspca_dev *gspca_dev = file->private_data;
	int ret;

	PDEBUG(D_FRAM, "poll");

	poll_wait(file, &gspca_dev->wq, wait);

	/* if reqbufs is not done, the user would use read() */
	if (gspca_dev->memory == GSPCA_MEMORY_NO) {
		ret = read_alloc(gspca_dev, file);
		if (ret != 0)
			return POLLERR;
	}

	if (mutex_lock_interruptible(&gspca_dev->queue_lock) != 0)
		return POLLERR;

	/* check if an image has been received */
	if (gspca_dev->fr_o != atomic_read(&gspca_dev->fr_i))
		ret = POLLIN | POLLRDNORM;	/* yes */
	else
		ret = 0;
	mutex_unlock(&gspca_dev->queue_lock);
	if (!gspca_dev->present)
		return POLLHUP;
	return ret;
}