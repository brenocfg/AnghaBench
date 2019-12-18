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
struct printer_dev {int /*<<< orphan*/  tx_reqs_active; int /*<<< orphan*/  tx_flush_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_reqs; } ;
struct file {struct printer_dev* private_data; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
printer_fsync(struct file *fd, struct dentry *dentry, int datasync)
{
	struct printer_dev	*dev = fd->private_data;
	unsigned long		flags;
	int			tx_list_empty;

	spin_lock_irqsave(&dev->lock, flags);
	tx_list_empty = (likely(list_empty(&dev->tx_reqs)));
	spin_unlock_irqrestore(&dev->lock, flags);

	if (!tx_list_empty) {
		/* Sleep until all data has been sent */
		wait_event_interruptible(dev->tx_flush_wait,
				(likely(list_empty(&dev->tx_reqs_active))));
	}

	return 0;
}