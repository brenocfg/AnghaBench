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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ opcode; } ;
struct qib_swqe {TYPE_1__ wr; int /*<<< orphan*/  lpsn; } ;
struct qib_qp {int s_flags; int /*<<< orphan*/  rspwait; int /*<<< orphan*/  refcount; int /*<<< orphan*/  r_flags; scalar_t__ s_last_psn; int /*<<< orphan*/  s_acked; int /*<<< orphan*/  s_timer; } ;
struct qib_ibport {int /*<<< orphan*/  n_rdma_seq; } ;
struct qib_ctxtdata {int /*<<< orphan*/  qp_wait_list; } ;

/* Variables and functions */
 scalar_t__ IB_WR_ATOMIC_CMP_AND_SWP ; 
 scalar_t__ IB_WR_ATOMIC_FETCH_AND_ADD ; 
 scalar_t__ IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  QIB_R_RDMAR_SEQ ; 
 int /*<<< orphan*/  QIB_R_RSP_SEND ; 
 int QIB_S_TIMER ; 
 int QIB_S_WAIT_RNR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct qib_swqe* do_rc_completion (struct qib_qp*,struct qib_swqe*,struct qib_ibport*) ; 
 struct qib_swqe* get_swqe_ptr (struct qib_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ qib_cmp24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_restart_rc (struct qib_qp*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdma_seq_err(struct qib_qp *qp, struct qib_ibport *ibp, u32 psn,
			 struct qib_ctxtdata *rcd)
{
	struct qib_swqe *wqe;

	/* Remove QP from retry timer */
	if (qp->s_flags & (QIB_S_TIMER | QIB_S_WAIT_RNR)) {
		qp->s_flags &= ~(QIB_S_TIMER | QIB_S_WAIT_RNR);
		del_timer(&qp->s_timer);
	}

	wqe = get_swqe_ptr(qp, qp->s_acked);

	while (qib_cmp24(psn, wqe->lpsn) > 0) {
		if (wqe->wr.opcode == IB_WR_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)
			break;
		wqe = do_rc_completion(qp, wqe, ibp);
	}

	ibp->n_rdma_seq++;
	qp->r_flags |= QIB_R_RDMAR_SEQ;
	qib_restart_rc(qp, qp->s_last_psn + 1, 0);
	if (list_empty(&qp->rspwait)) {
		qp->r_flags |= QIB_R_RSP_SEND;
		atomic_inc(&qp->refcount);
		list_add_tail(&qp->rspwait, &rcd->qp_wait_list);
	}
}