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
struct vhost_work {unsigned int queue_seq; int flushing; int /*<<< orphan*/  done; } ;
struct vhost_dev {int /*<<< orphan*/  work_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_work_seq_done (struct vhost_dev*,struct vhost_work*,unsigned int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vhost_work_flush(struct vhost_dev *dev, struct vhost_work *work)
{
	unsigned seq;
	int flushing;

	spin_lock_irq(&dev->work_lock);
	seq = work->queue_seq;
	work->flushing++;
	spin_unlock_irq(&dev->work_lock);
	wait_event(work->done, vhost_work_seq_done(dev, work, seq));
	spin_lock_irq(&dev->work_lock);
	flushing = --work->flushing;
	spin_unlock_irq(&dev->work_lock);
	BUG_ON(flushing < 0);
}