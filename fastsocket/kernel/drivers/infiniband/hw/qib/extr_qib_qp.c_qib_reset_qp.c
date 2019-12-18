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
struct TYPE_6__ {scalar_t__ num_sge; } ;
struct TYPE_5__ {TYPE_1__* wq; } ;
struct qib_qp {int s_ssn; TYPE_3__ r_sge; TYPE_2__ r_rq; scalar_t__ s_num_rd_atomic; scalar_t__ s_tail_ack_queue; scalar_t__ r_head_ack_queue; int /*<<< orphan*/  s_ack_queue; int /*<<< orphan*/  s_mig_state; scalar_t__ s_lsn; scalar_t__ s_last; scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_tail; scalar_t__ s_head; scalar_t__ r_flags; scalar_t__ r_aflags; scalar_t__ r_nak_state; int /*<<< orphan*/  s_ack_state; void* r_state; void* s_state; scalar_t__ r_msn; scalar_t__ r_psn; scalar_t__ s_psn; scalar_t__ s_sending_hpsn; scalar_t__ s_sending_psn; scalar_t__ s_last_psn; scalar_t__ s_next_psn; scalar_t__ s_draining; int /*<<< orphan*/ * s_wqe; scalar_t__ s_hdrwords; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_dma_busy; scalar_t__ qp_access_flags; scalar_t__ qkey; scalar_t__ remote_qpn; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_4__ {scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MIG_MIGRATED ; 
 int /*<<< orphan*/  IB_OPCODE_RC_ACKNOWLEDGE ; 
 void* IB_OPCODE_RC_SEND_LAST ; 
 void* IB_OPCODE_UC_SEND_LAST ; 
 int IB_QPT_RC ; 
 int /*<<< orphan*/  QIB_S_SIGNAL_REQ_WR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qib_reset_qp(struct qib_qp *qp, enum ib_qp_type type)
{
	qp->remote_qpn = 0;
	qp->qkey = 0;
	qp->qp_access_flags = 0;
	atomic_set(&qp->s_dma_busy, 0);
	qp->s_flags &= QIB_S_SIGNAL_REQ_WR;
	qp->s_hdrwords = 0;
	qp->s_wqe = NULL;
	qp->s_draining = 0;
	qp->s_next_psn = 0;
	qp->s_last_psn = 0;
	qp->s_sending_psn = 0;
	qp->s_sending_hpsn = 0;
	qp->s_psn = 0;
	qp->r_psn = 0;
	qp->r_msn = 0;
	if (type == IB_QPT_RC) {
		qp->s_state = IB_OPCODE_RC_SEND_LAST;
		qp->r_state = IB_OPCODE_RC_SEND_LAST;
	} else {
		qp->s_state = IB_OPCODE_UC_SEND_LAST;
		qp->r_state = IB_OPCODE_UC_SEND_LAST;
	}
	qp->s_ack_state = IB_OPCODE_RC_ACKNOWLEDGE;
	qp->r_nak_state = 0;
	qp->r_aflags = 0;
	qp->r_flags = 0;
	qp->s_head = 0;
	qp->s_tail = 0;
	qp->s_cur = 0;
	qp->s_acked = 0;
	qp->s_last = 0;
	qp->s_ssn = 1;
	qp->s_lsn = 0;
	qp->s_mig_state = IB_MIG_MIGRATED;
	memset(qp->s_ack_queue, 0, sizeof(qp->s_ack_queue));
	qp->r_head_ack_queue = 0;
	qp->s_tail_ack_queue = 0;
	qp->s_num_rd_atomic = 0;
	if (qp->r_rq.wq) {
		qp->r_rq.wq->head = 0;
		qp->r_rq.wq->tail = 0;
	}
	qp->r_sge.num_sge = 0;
}