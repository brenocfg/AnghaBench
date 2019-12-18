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
struct qib_qp {size_t state; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  iowait; } ;
struct qib_ibdev {int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  memwait; int /*<<< orphan*/  mem_timer; } ;

/* Variables and functions */
 int EBUSY ; 
 int QIB_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  QIB_S_BUSY ; 
 int /*<<< orphan*/  QIB_S_WAIT_KMEM ; 
 int* ib_qib_state_ops ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int wait_kmem(struct qib_ibdev *dev, struct qib_qp *qp)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&qp->s_lock, flags);
	if (ib_qib_state_ops[qp->state] & QIB_PROCESS_RECV_OK) {
		spin_lock(&dev->pending_lock);
		if (list_empty(&qp->iowait)) {
			if (list_empty(&dev->memwait))
				mod_timer(&dev->mem_timer, jiffies + 1);
			qp->s_flags |= QIB_S_WAIT_KMEM;
			list_add_tail(&qp->iowait, &dev->memwait);
		}
		spin_unlock(&dev->pending_lock);
		qp->s_flags &= ~QIB_S_BUSY;
		ret = -EBUSY;
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);

	return ret;
}