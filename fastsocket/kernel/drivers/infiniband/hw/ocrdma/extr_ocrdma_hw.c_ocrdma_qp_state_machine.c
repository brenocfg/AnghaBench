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
struct ocrdma_qp {int state; int /*<<< orphan*/  q_lock; } ;
typedef  enum ocrdma_qp_state { ____Placeholder_ocrdma_qp_state } ocrdma_qp_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int EINVAL ; 
#define  OCRDMA_QPS_ERR 134 
#define  OCRDMA_QPS_INIT 133 
#define  OCRDMA_QPS_RST 132 
#define  OCRDMA_QPS_RTR 131 
#define  OCRDMA_QPS_RTS 130 
#define  OCRDMA_QPS_SQD 129 
#define  OCRDMA_QPS_SQE 128 
 int get_ibqp_state (int) ; 
 int get_ocrdma_qp_state (int) ; 
 int /*<<< orphan*/  ocrdma_flush_qp (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ocrdma_qp_state_machine(struct ocrdma_qp *qp, enum ib_qp_state new_ib_state,
			    enum ib_qp_state *old_ib_state)
{
	unsigned long flags;
	int status = 0;
	enum ocrdma_qp_state new_state;
	new_state = get_ocrdma_qp_state(new_ib_state);

	/* sync with wqe and rqe posting */
	spin_lock_irqsave(&qp->q_lock, flags);

	if (old_ib_state)
		*old_ib_state = get_ibqp_state(qp->state);
	if (new_state == qp->state) {
		spin_unlock_irqrestore(&qp->q_lock, flags);
		return 1;
	}

	switch (qp->state) {
	case OCRDMA_QPS_RST:
		switch (new_state) {
		case OCRDMA_QPS_RST:
		case OCRDMA_QPS_INIT:
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case OCRDMA_QPS_INIT:
		/* qps: INIT->XXX */
		switch (new_state) {
		case OCRDMA_QPS_INIT:
		case OCRDMA_QPS_RTR:
			break;
		case OCRDMA_QPS_ERR:
			ocrdma_flush_qp(qp);
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case OCRDMA_QPS_RTR:
		/* qps: RTS->XXX */
		switch (new_state) {
		case OCRDMA_QPS_RTS:
			break;
		case OCRDMA_QPS_ERR:
			ocrdma_flush_qp(qp);
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case OCRDMA_QPS_RTS:
		/* qps: RTS->XXX */
		switch (new_state) {
		case OCRDMA_QPS_SQD:
		case OCRDMA_QPS_SQE:
			break;
		case OCRDMA_QPS_ERR:
			ocrdma_flush_qp(qp);
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case OCRDMA_QPS_SQD:
		/* qps: SQD->XXX */
		switch (new_state) {
		case OCRDMA_QPS_RTS:
		case OCRDMA_QPS_SQE:
		case OCRDMA_QPS_ERR:
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case OCRDMA_QPS_SQE:
		switch (new_state) {
		case OCRDMA_QPS_RTS:
		case OCRDMA_QPS_ERR:
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case OCRDMA_QPS_ERR:
		/* qps: ERR->XXX */
		switch (new_state) {
		case OCRDMA_QPS_RST:
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	default:
		status = -EINVAL;
		break;
	};
	if (!status)
		qp->state = new_state;

	spin_unlock_irqrestore(&qp->q_lock, flags);
	return status;
}