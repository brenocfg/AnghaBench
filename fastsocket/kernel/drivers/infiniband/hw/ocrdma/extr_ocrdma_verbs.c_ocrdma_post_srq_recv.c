#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_4__ {scalar_t__ max_sges; } ;
struct ocrdma_srq {int /*<<< orphan*/  q_lock; TYPE_1__ rq; int /*<<< orphan*/ * rqe_wr_id_tbl; } ;
struct ocrdma_hdr_wqe {int dummy; } ;
struct ib_srq {int dummy; } ;
struct ib_recv_wr {scalar_t__ num_sge; struct ib_recv_wr* next; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ocrdma_srq* get_ocrdma_srq (struct ib_srq*) ; 
 int /*<<< orphan*/  ocrdma_build_rqe (struct ocrdma_hdr_wqe*,struct ib_recv_wr*,size_t) ; 
 scalar_t__ ocrdma_hwq_free_cnt (TYPE_1__*) ; 
 struct ocrdma_hdr_wqe* ocrdma_hwq_head (TYPE_1__*) ; 
 int /*<<< orphan*/  ocrdma_hwq_inc_head (TYPE_1__*) ; 
 int /*<<< orphan*/  ocrdma_ring_srq_db (struct ocrdma_srq*) ; 
 size_t ocrdma_srq_get_idx (struct ocrdma_srq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

int ocrdma_post_srq_recv(struct ib_srq *ibsrq, struct ib_recv_wr *wr,
			 struct ib_recv_wr **bad_wr)
{
	int status = 0;
	unsigned long flags;
	struct ocrdma_srq *srq;
	struct ocrdma_hdr_wqe *rqe;
	u16 tag;

	srq = get_ocrdma_srq(ibsrq);

	spin_lock_irqsave(&srq->q_lock, flags);
	while (wr) {
		if (ocrdma_hwq_free_cnt(&srq->rq) == 0 ||
		    wr->num_sge > srq->rq.max_sges) {
			status = -ENOMEM;
			*bad_wr = wr;
			break;
		}
		tag = ocrdma_srq_get_idx(srq);
		rqe = ocrdma_hwq_head(&srq->rq);
		ocrdma_build_rqe(rqe, wr, tag);

		srq->rqe_wr_id_tbl[tag] = wr->wr_id;
		/* make sure rqe is written before adapter can perform DMA */
		wmb();
		/* inform hw to start processing it */
		ocrdma_ring_srq_db(srq);
		/* update pointer, counter for next wr */
		ocrdma_hwq_inc_head(&srq->rq);
		wr = wr->next;
	}
	spin_unlock_irqrestore(&srq->q_lock, flags);
	return status;
}