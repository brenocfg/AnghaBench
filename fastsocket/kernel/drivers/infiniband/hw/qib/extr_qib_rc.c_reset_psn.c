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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ opcode; } ;
struct qib_swqe {TYPE_1__ wr; int /*<<< orphan*/  psn; } ;
struct qib_qp {scalar_t__ s_acked; scalar_t__ s_size; scalar_t__ s_tail; scalar_t__ s_psn; scalar_t__ s_sending_psn; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_sending_hpsn; void* s_state; scalar_t__ s_cur; } ;

/* Variables and functions */
#define  IB_WR_RDMA_READ 132 
#define  IB_WR_RDMA_WRITE 131 
#define  IB_WR_RDMA_WRITE_WITH_IMM 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_IMM 128 
 void* OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QIB_S_WAIT_PSN ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_FIRST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_LAST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_MIDDLE ; 
 int /*<<< orphan*/  SEND_LAST ; 
 struct qib_swqe* get_swqe_ptr (struct qib_qp*,scalar_t__) ; 
 int qib_cmp24 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_psn(struct qib_qp *qp, u32 psn)
{
	u32 n = qp->s_acked;
	struct qib_swqe *wqe = get_swqe_ptr(qp, n);
	u32 opcode;

	qp->s_cur = n;

	/*
	 * If we are starting the request from the beginning,
	 * let the normal send code handle initialization.
	 */
	if (qib_cmp24(psn, wqe->psn) <= 0) {
		qp->s_state = OP(SEND_LAST);
		goto done;
	}

	/* Find the work request opcode corresponding to the given PSN. */
	opcode = wqe->wr.opcode;
	for (;;) {
		int diff;

		if (++n == qp->s_size)
			n = 0;
		if (n == qp->s_tail)
			break;
		wqe = get_swqe_ptr(qp, n);
		diff = qib_cmp24(psn, wqe->psn);
		if (diff < 0)
			break;
		qp->s_cur = n;
		/*
		 * If we are starting the request from the beginning,
		 * let the normal send code handle initialization.
		 */
		if (diff == 0) {
			qp->s_state = OP(SEND_LAST);
			goto done;
		}
		opcode = wqe->wr.opcode;
	}

	/*
	 * Set the state to restart in the middle of a request.
	 * Don't change the s_sge, s_cur_sge, or s_cur_size.
	 * See qib_make_rc_req().
	 */
	switch (opcode) {
	case IB_WR_SEND:
	case IB_WR_SEND_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_FIRST);
		break;

	case IB_WR_RDMA_WRITE:
	case IB_WR_RDMA_WRITE_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_LAST);
		break;

	case IB_WR_RDMA_READ:
		qp->s_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		break;

	default:
		/*
		 * This case shouldn't happen since its only
		 * one PSN per req.
		 */
		qp->s_state = OP(SEND_LAST);
	}
done:
	qp->s_psn = psn;
	/*
	 * Set QIB_S_WAIT_PSN as qib_rc_complete() may start the timer
	 * asynchronously before the send tasklet can get scheduled.
	 * Doing it in qib_make_rc_req() is too late.
	 */
	if ((qib_cmp24(qp->s_psn, qp->s_sending_hpsn) <= 0) &&
	    (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0))
		qp->s_flags |= QIB_S_WAIT_PSN;
}