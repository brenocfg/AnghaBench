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
struct file {struct b3dfg_dev* private_data; } ;
struct b3dfg_dev {int /*<<< orphan*/  transmission_enabled; int /*<<< orphan*/  buffer_lock; TYPE_1__* buffers; int /*<<< orphan*/  buffer_waitqueue; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ B3DFG_BUFFER_POPULATED ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int b3dfg_nbuf ; 
 unsigned long get_cstate_change (struct b3dfg_dev*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int b3dfg_poll(struct file *filp, poll_table *poll_table)
{
	struct b3dfg_dev *fgdev = filp->private_data;
	unsigned long flags, when;
	int i;
	int r = 0;

	when = get_cstate_change(fgdev);
	poll_wait(filp, &fgdev->buffer_waitqueue, poll_table);

	spin_lock_irqsave(&fgdev->buffer_lock, flags);
	for (i = 0; i < b3dfg_nbuf; i++) {
		if (fgdev->buffers[i].state == B3DFG_BUFFER_POPULATED) {
			r = POLLIN | POLLRDNORM;
			break;
		}
	}
	spin_unlock_irqrestore(&fgdev->buffer_lock, flags);

	/* TODO: Confirm this is how we want to communicate the change. */
	if (!fgdev->transmission_enabled || when != get_cstate_change(fgdev))
		r = POLLERR;

	return r;
}