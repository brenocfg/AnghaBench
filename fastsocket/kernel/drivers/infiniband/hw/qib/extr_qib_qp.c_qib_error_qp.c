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
typedef  int /*<<< orphan*/  wc ;
typedef  scalar_t__ u32 ;
struct qib_rwq {scalar_t__ head; scalar_t__ tail; } ;
struct TYPE_4__ {scalar_t__ event_handler; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  device; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  lock; struct qib_rwq* wq; } ;
struct qib_qp {scalar_t__ state; int s_flags; scalar_t__ s_last; scalar_t__ s_head; TYPE_1__ ibqp; TYPE_3__ r_rq; int /*<<< orphan*/  r_wr_id; int /*<<< orphan*/  r_aflags; int /*<<< orphan*/ * s_tx; int /*<<< orphan*/ * s_rdma_mr; scalar_t__ s_hdrwords; int /*<<< orphan*/  iowait; int /*<<< orphan*/  s_timer; } ;
struct qib_ibdev {int /*<<< orphan*/  pending_lock; } ;
struct ib_wc {int status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; TYPE_1__* qp; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_5__ {int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_ERR ; 
 scalar_t__ IB_QPS_RESET ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  QIB_R_WRID_VALID ; 
 int QIB_S_ANY_WAIT_IO ; 
 int QIB_S_ANY_WAIT_SEND ; 
 int QIB_S_BUSY ; 
 int QIB_S_TIMER ; 
 int QIB_S_WAIT_RNR ; 
 int /*<<< orphan*/  clear_mr_refs (struct qib_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 TYPE_2__* get_rwqe_ptr (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int /*<<< orphan*/  qib_put_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_put_txreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_schedule_send (struct qib_qp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

int qib_error_qp(struct qib_qp *qp, enum ib_wc_status err)
{
	struct qib_ibdev *dev = to_idev(qp->ibqp.device);
	struct ib_wc wc;
	int ret = 0;

	if (qp->state == IB_QPS_ERR || qp->state == IB_QPS_RESET)
		goto bail;

	qp->state = IB_QPS_ERR;

	if (qp->s_flags & (QIB_S_TIMER | QIB_S_WAIT_RNR)) {
		qp->s_flags &= ~(QIB_S_TIMER | QIB_S_WAIT_RNR);
		del_timer(&qp->s_timer);
	}

	if (qp->s_flags & QIB_S_ANY_WAIT_SEND)
		qp->s_flags &= ~QIB_S_ANY_WAIT_SEND;

	spin_lock(&dev->pending_lock);
	if (!list_empty(&qp->iowait) && !(qp->s_flags & QIB_S_BUSY)) {
		qp->s_flags &= ~QIB_S_ANY_WAIT_IO;
		list_del_init(&qp->iowait);
	}
	spin_unlock(&dev->pending_lock);

	if (!(qp->s_flags & QIB_S_BUSY)) {
		qp->s_hdrwords = 0;
		if (qp->s_rdma_mr) {
			qib_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = NULL;
		}
		if (qp->s_tx) {
			qib_put_txreq(qp->s_tx);
			qp->s_tx = NULL;
		}
	}

	/* Schedule the sending tasklet to drain the send work queue. */
	if (qp->s_last != qp->s_head)
		qib_schedule_send(qp);

	clear_mr_refs(qp, 0);

	memset(&wc, 0, sizeof(wc));
	wc.qp = &qp->ibqp;
	wc.opcode = IB_WC_RECV;

	if (test_and_clear_bit(QIB_R_WRID_VALID, &qp->r_aflags)) {
		wc.wr_id = qp->r_wr_id;
		wc.status = err;
		qib_cq_enter(to_icq(qp->ibqp.recv_cq), &wc, 1);
	}
	wc.status = IB_WC_WR_FLUSH_ERR;

	if (qp->r_rq.wq) {
		struct qib_rwq *wq;
		u32 head;
		u32 tail;

		spin_lock(&qp->r_rq.lock);

		/* sanity check pointers before trusting them */
		wq = qp->r_rq.wq;
		head = wq->head;
		if (head >= qp->r_rq.size)
			head = 0;
		tail = wq->tail;
		if (tail >= qp->r_rq.size)
			tail = 0;
		while (tail != head) {
			wc.wr_id = get_rwqe_ptr(&qp->r_rq, tail)->wr_id;
			if (++tail >= qp->r_rq.size)
				tail = 0;
			qib_cq_enter(to_icq(qp->ibqp.recv_cq), &wc, 1);
		}
		wq->tail = tail;

		spin_unlock(&qp->r_rq.lock);
	} else if (qp->ibqp.event_handler)
		ret = 1;

bail:
	return ret;
}