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
struct vhost_work {int /*<<< orphan*/  queue_seq; int /*<<< orphan*/  node; } ;
struct vhost_dev {int /*<<< orphan*/  work_lock; int /*<<< orphan*/  worker; int /*<<< orphan*/  work_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vhost_work_queue(struct vhost_dev *dev,
				    struct vhost_work *work)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->work_lock, flags);
	if (list_empty(&work->node)) {
		list_add_tail(&work->node, &dev->work_list);
		work->queue_seq++;
		wake_up_process(dev->worker);
	}
	spin_unlock_irqrestore(&dev->work_lock, flags);
}