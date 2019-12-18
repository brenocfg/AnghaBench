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
typedef  int u16 ;
struct ocrdma_dev {int dummy; } ;
struct ocrdma_cqe {int dummy; } ;
struct ocrdma_cq {int id; int armed; int solicited; int getp; int arm_needed; int /*<<< orphan*/  cq_lock; struct ocrdma_cqe* va; struct ocrdma_dev* dev; } ;
struct ib_cq {int dummy; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;

/* Variables and functions */
 int IB_CQ_NEXT_COMP ; 
 int IB_CQ_SOLICITED ; 
 struct ocrdma_cq* get_ocrdma_cq (struct ib_cq*) ; 
 int /*<<< orphan*/  is_cqe_valid (struct ocrdma_cq*,struct ocrdma_cqe*) ; 
 int /*<<< orphan*/  ocrdma_ring_cq_db (struct ocrdma_dev*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ocrdma_arm_cq(struct ib_cq *ibcq, enum ib_cq_notify_flags cq_flags)
{
	struct ocrdma_cq *cq;
	unsigned long flags;
	struct ocrdma_dev *dev;
	u16 cq_id;
	u16 cur_getp;
	struct ocrdma_cqe *cqe;

	cq = get_ocrdma_cq(ibcq);
	cq_id = cq->id;
	dev = cq->dev;

	spin_lock_irqsave(&cq->cq_lock, flags);
	if (cq_flags & IB_CQ_NEXT_COMP || cq_flags & IB_CQ_SOLICITED)
		cq->armed = true;
	if (cq_flags & IB_CQ_SOLICITED)
		cq->solicited = true;

	cur_getp = cq->getp;
	cqe = cq->va + cur_getp;

	/* check whether any valid cqe exist or not, if not then safe to
	 * arm. If cqe is not yet consumed, then let it get consumed and then
	 * we arm it to avoid false interrupts.
	 */
	if (!is_cqe_valid(cq, cqe) || cq->arm_needed) {
		cq->arm_needed = false;
		ocrdma_ring_cq_db(dev, cq_id, cq->armed, cq->solicited, 0);
	}
	spin_unlock_irqrestore(&cq->cq_lock, flags);
	return 0;
}