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
struct TYPE_3__ {unsigned int num_sge; int send_flags; size_t opcode; int /*<<< orphan*/  wr_id; } ;
struct qib_swqe {int /*<<< orphan*/  psn; int /*<<< orphan*/  lpsn; int /*<<< orphan*/  length; TYPE_1__ wr; struct qib_sge* sg_list; } ;
struct qib_sge {int /*<<< orphan*/  mr; } ;
struct TYPE_4__ {int /*<<< orphan*/  send_cq; } ;
struct qib_qp {int s_flags; scalar_t__ s_last; scalar_t__ s_size; scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_tail; scalar_t__ state; scalar_t__ s_draining; int /*<<< orphan*/  s_psn; int /*<<< orphan*/  s_state; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; TYPE_2__ ibqp; int /*<<< orphan*/  s_sending_hpsn; int /*<<< orphan*/  s_sending_psn; } ;
struct qib_ibport {int /*<<< orphan*/  n_rc_delayed_comp; } ;
struct ib_wc {TYPE_2__* qp; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_SQD ; 
 int IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ) ; 
 int QIB_S_SIGNAL_REQ_WR ; 
 int /*<<< orphan*/  SEND_LAST ; 
 struct qib_swqe* get_swqe_ptr (struct qib_qp*,scalar_t__) ; 
 int /*<<< orphan*/ * ib_qib_wc_opcode ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qib_cmp24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_put_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_last_psn (struct qib_qp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qib_swqe *do_rc_completion(struct qib_qp *qp,
					 struct qib_swqe *wqe,
					 struct qib_ibport *ibp)
{
	struct ib_wc wc;
	unsigned i;

	/*
	 * Don't decrement refcount and don't generate a
	 * completion if the SWQE is being resent until the send
	 * is finished.
	 */
	if (qib_cmp24(wqe->lpsn, qp->s_sending_psn) < 0 ||
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0) {
		for (i = 0; i < wqe->wr.num_sge; i++) {
			struct qib_sge *sge = &wqe->sg_list[i];

			qib_put_mr(sge->mr);
		}
		/* Post a send completion queue entry if requested. */
		if (!(qp->s_flags & QIB_S_SIGNAL_REQ_WR) ||
		    (wqe->wr.send_flags & IB_SEND_SIGNALED)) {
			memset(&wc, 0, sizeof wc);
			wc.wr_id = wqe->wr.wr_id;
			wc.status = IB_WC_SUCCESS;
			wc.opcode = ib_qib_wc_opcode[wqe->wr.opcode];
			wc.byte_len = wqe->length;
			wc.qp = &qp->ibqp;
			qib_cq_enter(to_icq(qp->ibqp.send_cq), &wc, 0);
		}
		if (++qp->s_last >= qp->s_size)
			qp->s_last = 0;
	} else
		ibp->n_rc_delayed_comp++;

	qp->s_retry = qp->s_retry_cnt;
	update_last_psn(qp, wqe->lpsn);

	/*
	 * If we are completing a request which is in the process of
	 * being resent, we can stop resending it since we know the
	 * responder has already seen it.
	 */
	if (qp->s_acked == qp->s_cur) {
		if (++qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		qp->s_acked = qp->s_cur;
		wqe = get_swqe_ptr(qp, qp->s_cur);
		if (qp->s_acked != qp->s_tail) {
			qp->s_state = OP(SEND_LAST);
			qp->s_psn = wqe->psn;
		}
	} else {
		if (++qp->s_acked >= qp->s_size)
			qp->s_acked = 0;
		if (qp->state == IB_QPS_SQD && qp->s_acked == qp->s_cur)
			qp->s_draining = 0;
		wqe = get_swqe_ptr(qp, qp->s_acked);
	}
	return wqe;
}