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
struct vhost_work {unsigned int done_seq; } ;
struct vhost_dev {int /*<<< orphan*/  work_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vhost_work_seq_done(struct vhost_dev *dev, struct vhost_work *work,
				unsigned seq)
{
	int left;
	spin_lock_irq(&dev->work_lock);
	left = seq - work->done_seq;
	spin_unlock_irq(&dev->work_lock);
	return left <= 0;
}