#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_8__ {size_t opcode; int send_flags; int /*<<< orphan*/  wr_id; } ;
struct ipath_swqe {int lpsn; int psn; TYPE_4__ wr; int /*<<< orphan*/  length; TYPE_3__* sg_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  send_cq; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; } ;
struct ipath_qp {scalar_t__ s_last; int s_flags; scalar_t__ s_cur; scalar_t__ s_size; scalar_t__ s_tail; int s_state; int s_psn; scalar_t__ state; int s_rnr_retry; int s_rnr_retry_cnt; int /*<<< orphan*/  s_rnr_timeout; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; int /*<<< orphan*/  timerwait; scalar_t__ s_draining; TYPE_2__ ibqp; TYPE_1__ remote_ah_attr; int /*<<< orphan*/  remote_qpn; scalar_t__ s_num_rd_atomic; } ;
struct ipath_ibdev {size_t pending_index; int n_rc_resends; int /*<<< orphan*/  n_other_naks; int /*<<< orphan*/  n_seq_naks; int /*<<< orphan*/  n_rnr_naks; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/ * pending; int /*<<< orphan*/  n_rc_acks; } ;
struct ib_wc {int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  src_qp; TYPE_2__* qp; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_7__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACKNOWLEDGE ; 
 scalar_t__ IB_QPS_SQD ; 
 int IB_SEND_SIGNALED ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 size_t IB_WR_ATOMIC_CMP_AND_SWP ; 
 size_t IB_WR_ATOMIC_FETCH_AND_ADD ; 
 size_t IB_WR_RDMA_READ ; 
 int IPATH_AETH_CREDIT_MASK ; 
 int IPATH_AETH_CREDIT_SHIFT ; 
 int IPATH_PSN_MASK ; 
 int IPATH_S_FENCE_PENDING ; 
 int IPATH_S_RDMAR_PENDING ; 
 int IPATH_S_SIGNAL_REQ_WR ; 
 int OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_LAST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_ONLY ; 
 int /*<<< orphan*/  SEND_LAST ; 
 struct ipath_swqe* get_swqe_ptr (struct ipath_qp*,scalar_t__) ; 
 int /*<<< orphan*/ * ib_ipath_rnr_table ; 
 int /*<<< orphan*/ * ib_ipath_wc_opcode ; 
 int ipath_cmp24 (int,int) ; 
 int /*<<< orphan*/  ipath_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_error_qp (struct ipath_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_get_credit (struct ipath_qp*,int) ; 
 int /*<<< orphan*/  ipath_insert_rnr_queue (struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_restart_rc (struct ipath_qp*,int) ; 
 int /*<<< orphan*/  ipath_schedule_send (struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_send_complete (struct ipath_qp*,struct ipath_swqe*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_psn (struct ipath_qp*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_last_psn (struct ipath_qp*,int) ; 

__attribute__((used)) static int do_rc_ack(struct ipath_qp *qp, u32 aeth, u32 psn, int opcode,
		     u64 val)
{
	struct ipath_ibdev *dev = to_idev(qp->ibqp.device);
	struct ib_wc wc;
	enum ib_wc_status status;
	struct ipath_swqe *wqe;
	int ret = 0;
	u32 ack_psn;
	int diff;

	/*
	 * Remove the QP from the timeout queue (or RNR timeout queue).
	 * If ipath_ib_timer() has already removed it,
	 * it's OK since we hold the QP s_lock and ipath_restart_rc()
	 * just won't find anything to restart if we ACK everything.
	 */
	spin_lock(&dev->pending_lock);
	if (!list_empty(&qp->timerwait))
		list_del_init(&qp->timerwait);
	spin_unlock(&dev->pending_lock);

	/*
	 * Note that NAKs implicitly ACK outstanding SEND and RDMA write
	 * requests and implicitly NAK RDMA read and atomic requests issued
	 * before the NAK'ed request.  The MSN won't include the NAK'ed
	 * request but will include an ACK'ed request(s).
	 */
	ack_psn = psn;
	if (aeth >> 29)
		ack_psn--;
	wqe = get_swqe_ptr(qp, qp->s_last);

	/*
	 * The MSN might be for a later WQE than the PSN indicates so
	 * only complete WQEs that the PSN finishes.
	 */
	while ((diff = ipath_cmp24(ack_psn, wqe->lpsn)) >= 0) {
		/*
		 * RDMA_READ_RESPONSE_ONLY is a special case since
		 * we want to generate completion events for everything
		 * before the RDMA read, copy the data, then generate
		 * the completion for the read.
		 */
		if (wqe->wr.opcode == IB_WR_RDMA_READ &&
		    opcode == OP(RDMA_READ_RESPONSE_ONLY) &&
		    diff == 0) {
			ret = 1;
			goto bail;
		}
		/*
		 * If this request is a RDMA read or atomic, and the ACK is
		 * for a later operation, this ACK NAKs the RDMA read or
		 * atomic.  In other words, only a RDMA_READ_LAST or ONLY
		 * can ACK a RDMA read and likewise for atomic ops.  Note
		 * that the NAK case can only happen if relaxed ordering is
		 * used and requests are sent after an RDMA read or atomic
		 * is sent but before the response is received.
		 */
		if ((wqe->wr.opcode == IB_WR_RDMA_READ &&
		     (opcode != OP(RDMA_READ_RESPONSE_LAST) || diff != 0)) ||
		    ((wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		      wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) &&
		     (opcode != OP(ATOMIC_ACKNOWLEDGE) || diff != 0))) {
			/*
			 * The last valid PSN seen is the previous
			 * request's.
			 */
			update_last_psn(qp, wqe->psn - 1);
			/* Retry this request. */
			ipath_restart_rc(qp, wqe->psn);
			/*
			 * No need to process the ACK/NAK since we are
			 * restarting an earlier request.
			 */
			goto bail;
		}
		if (wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)
			*(u64 *) wqe->sg_list[0].vaddr = val;
		if (qp->s_num_rd_atomic &&
		    (wqe->wr.opcode == IB_WR_RDMA_READ ||
		     wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		     wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)) {
			qp->s_num_rd_atomic--;
			/* Restart sending task if fence is complete */
			if (((qp->s_flags & IPATH_S_FENCE_PENDING) &&
			     !qp->s_num_rd_atomic) ||
			    qp->s_flags & IPATH_S_RDMAR_PENDING)
				ipath_schedule_send(qp);
		}
		/* Post a send completion queue entry if requested. */
		if (!(qp->s_flags & IPATH_S_SIGNAL_REQ_WR) ||
		    (wqe->wr.send_flags & IB_SEND_SIGNALED)) {
			memset(&wc, 0, sizeof wc);
			wc.wr_id = wqe->wr.wr_id;
			wc.status = IB_WC_SUCCESS;
			wc.opcode = ib_ipath_wc_opcode[wqe->wr.opcode];
			wc.byte_len = wqe->length;
			wc.qp = &qp->ibqp;
			wc.src_qp = qp->remote_qpn;
			wc.slid = qp->remote_ah_attr.dlid;
			wc.sl = qp->remote_ah_attr.sl;
			ipath_cq_enter(to_icq(qp->ibqp.send_cq), &wc, 0);
		}
		qp->s_retry = qp->s_retry_cnt;
		/*
		 * If we are completing a request which is in the process of
		 * being resent, we can stop resending it since we know the
		 * responder has already seen it.
		 */
		if (qp->s_last == qp->s_cur) {
			if (++qp->s_cur >= qp->s_size)
				qp->s_cur = 0;
			qp->s_last = qp->s_cur;
			if (qp->s_last == qp->s_tail)
				break;
			wqe = get_swqe_ptr(qp, qp->s_cur);
			qp->s_state = OP(SEND_LAST);
			qp->s_psn = wqe->psn;
		} else {
			if (++qp->s_last >= qp->s_size)
				qp->s_last = 0;
			if (qp->state == IB_QPS_SQD && qp->s_last == qp->s_cur)
				qp->s_draining = 0;
			if (qp->s_last == qp->s_tail)
				break;
			wqe = get_swqe_ptr(qp, qp->s_last);
		}
	}

	switch (aeth >> 29) {
	case 0:		/* ACK */
		dev->n_rc_acks++;
		/* If this is a partial ACK, reset the retransmit timer. */
		if (qp->s_last != qp->s_tail) {
			spin_lock(&dev->pending_lock);
			if (list_empty(&qp->timerwait))
				list_add_tail(&qp->timerwait,
					&dev->pending[dev->pending_index]);
			spin_unlock(&dev->pending_lock);
			/*
			 * If we get a partial ACK for a resent operation,
			 * we can stop resending the earlier packets and
			 * continue with the next packet the receiver wants.
			 */
			if (ipath_cmp24(qp->s_psn, psn) <= 0) {
				reset_psn(qp, psn + 1);
				ipath_schedule_send(qp);
			}
		} else if (ipath_cmp24(qp->s_psn, psn) <= 0) {
			qp->s_state = OP(SEND_LAST);
			qp->s_psn = psn + 1;
		}
		ipath_get_credit(qp, aeth);
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		qp->s_retry = qp->s_retry_cnt;
		update_last_psn(qp, psn);
		ret = 1;
		goto bail;

	case 1:		/* RNR NAK */
		dev->n_rnr_naks++;
		if (qp->s_last == qp->s_tail)
			goto bail;
		if (qp->s_rnr_retry == 0) {
			status = IB_WC_RNR_RETRY_EXC_ERR;
			goto class_b;
		}
		if (qp->s_rnr_retry_cnt < 7)
			qp->s_rnr_retry--;

		/* The last valid PSN is the previous PSN. */
		update_last_psn(qp, psn - 1);

		if (wqe->wr.opcode == IB_WR_RDMA_READ)
			dev->n_rc_resends++;
		else
			dev->n_rc_resends +=
				(qp->s_psn - psn) & IPATH_PSN_MASK;

		reset_psn(qp, psn);

		qp->s_rnr_timeout =
			ib_ipath_rnr_table[(aeth >> IPATH_AETH_CREDIT_SHIFT) &
					   IPATH_AETH_CREDIT_MASK];
		ipath_insert_rnr_queue(qp);
		ipath_schedule_send(qp);
		goto bail;

	case 3:		/* NAK */
		if (qp->s_last == qp->s_tail)
			goto bail;
		/* The last valid PSN is the previous PSN. */
		update_last_psn(qp, psn - 1);
		switch ((aeth >> IPATH_AETH_CREDIT_SHIFT) &
			IPATH_AETH_CREDIT_MASK) {
		case 0:	/* PSN sequence error */
			dev->n_seq_naks++;
			/*
			 * Back up to the responder's expected PSN.
			 * Note that we might get a NAK in the middle of an
			 * RDMA READ response which terminates the RDMA
			 * READ.
			 */
			ipath_restart_rc(qp, psn);
			break;

		case 1:	/* Invalid Request */
			status = IB_WC_REM_INV_REQ_ERR;
			dev->n_other_naks++;
			goto class_b;

		case 2:	/* Remote Access Error */
			status = IB_WC_REM_ACCESS_ERR;
			dev->n_other_naks++;
			goto class_b;

		case 3:	/* Remote Operation Error */
			status = IB_WC_REM_OP_ERR;
			dev->n_other_naks++;
		class_b:
			ipath_send_complete(qp, wqe, status);
			ipath_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			break;

		default:
			/* Ignore other reserved NAK error codes */
			goto reserved;
		}
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		goto bail;

	default:		/* 2: reserved */
	reserved:
		/* Ignore reserved NAK codes. */
		goto bail;
	}

bail:
	return ret;
}