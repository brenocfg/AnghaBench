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
struct ipath_qp {size_t state; scalar_t__ s_last; scalar_t__ s_head; int s_flags; int /*<<< orphan*/  wait_dma; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_dma_busy; } ;

/* Variables and functions */
 int IPATH_FLUSH_SEND ; 
 int IPATH_S_WAIT_DMA ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int* ib_ipath_state_ops ; 
 int /*<<< orphan*/  ipath_schedule_send (struct ipath_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decrement_dma_busy(struct ipath_qp *qp)
{
	unsigned long flags;

	if (atomic_dec_and_test(&qp->s_dma_busy)) {
		spin_lock_irqsave(&qp->s_lock, flags);
		if ((ib_ipath_state_ops[qp->state] & IPATH_FLUSH_SEND &&
		     qp->s_last != qp->s_head) ||
		    (qp->s_flags & IPATH_S_WAIT_DMA))
			ipath_schedule_send(qp);
		spin_unlock_irqrestore(&qp->s_lock, flags);
		wake_up(&qp->wait_dma);
	}
}