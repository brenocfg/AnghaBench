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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int send_flags; size_t opcode; int /*<<< orphan*/  wr_id; } ;
struct ipath_swqe {int /*<<< orphan*/  length; TYPE_1__ wr; } ;
struct TYPE_4__ {int /*<<< orphan*/  send_cq; } ;
struct ipath_qp {size_t state; int s_flags; scalar_t__ s_last; scalar_t__ s_size; scalar_t__ s_cur; scalar_t__ s_tail; scalar_t__ s_draining; TYPE_2__ ibqp; } ;
struct ib_wc {int status; int /*<<< orphan*/  byte_len; TYPE_2__* qp; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wr_id; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 size_t IB_QPS_SQD ; 
 int IB_SEND_SIGNALED ; 
 int IB_WC_SUCCESS ; 
 int IPATH_PROCESS_OR_FLUSH_SEND ; 
 int IPATH_S_SIGNAL_REQ_WR ; 
 int* ib_ipath_state_ops ; 
 int /*<<< orphan*/ * ib_ipath_wc_opcode ; 
 int /*<<< orphan*/  ipath_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 

void ipath_send_complete(struct ipath_qp *qp, struct ipath_swqe *wqe,
			 enum ib_wc_status status)
{
	u32 old_last, last;

	if (!(ib_ipath_state_ops[qp->state] & IPATH_PROCESS_OR_FLUSH_SEND))
		return;

	/* See ch. 11.2.4.1 and 10.7.3.1 */
	if (!(qp->s_flags & IPATH_S_SIGNAL_REQ_WR) ||
	    (wqe->wr.send_flags & IB_SEND_SIGNALED) ||
	    status != IB_WC_SUCCESS) {
		struct ib_wc wc;

		memset(&wc, 0, sizeof wc);
		wc.wr_id = wqe->wr.wr_id;
		wc.status = status;
		wc.opcode = ib_ipath_wc_opcode[wqe->wr.opcode];
		wc.qp = &qp->ibqp;
		if (status == IB_WC_SUCCESS)
			wc.byte_len = wqe->length;
		ipath_cq_enter(to_icq(qp->ibqp.send_cq), &wc,
			       status != IB_WC_SUCCESS);
	}

	old_last = last = qp->s_last;
	if (++last >= qp->s_size)
		last = 0;
	qp->s_last = last;
	if (qp->s_cur == old_last)
		qp->s_cur = last;
	if (qp->s_tail == old_last)
		qp->s_tail = last;
	if (qp->state == IB_QPS_SQD && last == qp->s_cur)
		qp->s_draining = 0;
}