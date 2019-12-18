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
struct ipath_rwq {scalar_t__ head; scalar_t__ tail; } ;
struct TYPE_4__ {scalar_t__ event_handler; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  device; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  lock; struct ipath_rwq* wq; } ;
struct ipath_qp {scalar_t__ state; scalar_t__ s_last; scalar_t__ s_head; TYPE_1__ ibqp; TYPE_3__ r_rq; int /*<<< orphan*/  r_wr_id; int /*<<< orphan*/  r_aflags; int /*<<< orphan*/  piowait; int /*<<< orphan*/  timerwait; } ;
struct ipath_ibdev {int /*<<< orphan*/  pending_lock; } ;
struct ib_wc {int status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; TYPE_1__* qp; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_5__ {int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  IPATH_R_WRID_VALID ; 
 TYPE_2__* get_rwqe_ptr (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ipath_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int /*<<< orphan*/  ipath_schedule_send (struct ipath_qp*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 

int ipath_error_qp(struct ipath_qp *qp, enum ib_wc_status err)
{
	struct ipath_ibdev *dev = to_idev(qp->ibqp.device);
	struct ib_wc wc;
	int ret = 0;

	if (qp->state == IB_QPS_ERR)
		goto bail;

	qp->state = IB_QPS_ERR;

	spin_lock(&dev->pending_lock);
	if (!list_empty(&qp->timerwait))
		list_del_init(&qp->timerwait);
	if (!list_empty(&qp->piowait))
		list_del_init(&qp->piowait);
	spin_unlock(&dev->pending_lock);

	/* Schedule the sending tasklet to drain the send work queue. */
	if (qp->s_last != qp->s_head)
		ipath_schedule_send(qp);

	memset(&wc, 0, sizeof(wc));
	wc.qp = &qp->ibqp;
	wc.opcode = IB_WC_RECV;

	if (test_and_clear_bit(IPATH_R_WRID_VALID, &qp->r_aflags)) {
		wc.wr_id = qp->r_wr_id;
		wc.status = err;
		ipath_cq_enter(to_icq(qp->ibqp.recv_cq), &wc, 1);
	}
	wc.status = IB_WC_WR_FLUSH_ERR;

	if (qp->r_rq.wq) {
		struct ipath_rwq *wq;
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
			ipath_cq_enter(to_icq(qp->ibqp.recv_cq), &wc, 1);
		}
		wq->tail = tail;

		spin_unlock(&qp->r_rq.lock);
	} else if (qp->ibqp.event_handler)
		ret = 1;

bail:
	return ret;
}