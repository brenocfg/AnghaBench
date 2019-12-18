#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ocrdma_qp {int id; int /*<<< orphan*/  rq; TYPE_2__* srq; int /*<<< orphan*/  sq; } ;
struct TYPE_3__ {int qpn; } ;
struct ocrdma_cqe {TYPE_1__ cmn; } ;
struct ocrdma_cq {int getp; int max_hw_cqe; int /*<<< orphan*/  cq_lock; struct ocrdma_cqe* va; } ;
struct TYPE_4__ {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int OCRDMA_CQE_QPN_MASK ; 
 scalar_t__ is_cqe_for_sq (struct ocrdma_cqe*) ; 
 scalar_t__ is_hw_rq_empty (struct ocrdma_qp*) ; 
 scalar_t__ is_hw_sq_empty (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_hwq_inc_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_srq_toggle_bit (TYPE_2__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ocrdma_discard_cqes(struct ocrdma_qp *qp, struct ocrdma_cq *cq)
{
	unsigned long cq_flags;
	unsigned long flags;
	int discard_cnt = 0;
	u32 cur_getp, stop_getp;
	struct ocrdma_cqe *cqe;
	u32 qpn = 0;

	spin_lock_irqsave(&cq->cq_lock, cq_flags);

	/* traverse through the CQEs in the hw CQ,
	 * find the matching CQE for a given qp,
	 * mark the matching one discarded by clearing qpn.
	 * ring the doorbell in the poll_cq() as
	 * we don't complete out of order cqe.
	 */

	cur_getp = cq->getp;
	/* find upto when do we reap the cq. */
	stop_getp = cur_getp;
	do {
		if (is_hw_sq_empty(qp) && (!qp->srq && is_hw_rq_empty(qp)))
			break;

		cqe = cq->va + cur_getp;
		/* if (a) done reaping whole hw cq, or
		 *    (b) qp_xq becomes empty.
		 * then exit
		 */
		qpn = cqe->cmn.qpn & OCRDMA_CQE_QPN_MASK;
		/* if previously discarded cqe found, skip that too. */
		/* check for matching qp */
		if (qpn == 0 || qpn != qp->id)
			goto skip_cqe;

		/* mark cqe discarded so that it is not picked up later
		 * in the poll_cq().
		 */
		discard_cnt += 1;
		cqe->cmn.qpn = 0;
		if (is_cqe_for_sq(cqe))
			ocrdma_hwq_inc_tail(&qp->sq);
		else {
			if (qp->srq) {
				spin_lock_irqsave(&qp->srq->q_lock, flags);
				ocrdma_hwq_inc_tail(&qp->srq->rq);
				ocrdma_srq_toggle_bit(qp->srq, cur_getp);
				spin_unlock_irqrestore(&qp->srq->q_lock, flags);

			} else
				ocrdma_hwq_inc_tail(&qp->rq);
		}
skip_cqe:
		cur_getp = (cur_getp + 1) % cq->max_hw_cqe;
	} while (cur_getp != stop_getp);
	spin_unlock_irqrestore(&cq->cq_lock, cq_flags);
}