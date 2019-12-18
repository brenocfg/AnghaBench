#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int tail; } ;
struct ocrdma_qp {TYPE_3__ sq; int /*<<< orphan*/  ibqp; TYPE_1__* wqe_wr_id_tbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  wqeidx; } ;
struct ocrdma_cqe {TYPE_2__ wq; } ;
struct ib_wc {int /*<<< orphan*/ * qp; scalar_t__ wc_flags; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  signaled; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int OCRDMA_CQE_WQEIDX_MASK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_hwq_inc_tail (TYPE_3__*) ; 
 int /*<<< orphan*/  ocrdma_update_wc (struct ocrdma_qp*,struct ib_wc*,int) ; 

__attribute__((used)) static bool ocrdma_poll_success_scqe(struct ocrdma_qp *qp,
				     struct ocrdma_cqe *cqe,
				     struct ib_wc *ibwc, bool *polled)
{
	bool expand = false;
	int tail = qp->sq.tail;
	u32 wqe_idx;

	if (!qp->wqe_wr_id_tbl[tail].signaled) {
		*polled = false;    /* WC cannot be consumed yet */
	} else {
		ibwc->status = IB_WC_SUCCESS;
		ibwc->wc_flags = 0;
		ibwc->qp = &qp->ibqp;
		ocrdma_update_wc(qp, ibwc, tail);
		*polled = true;
	}
	wqe_idx = le32_to_cpu(cqe->wq.wqeidx) &	OCRDMA_CQE_WQEIDX_MASK;
	if (tail != wqe_idx)
		expand = true; /* Coalesced CQE can't be consumed yet */

	ocrdma_hwq_inc_tail(&qp->sq);
	return expand;
}