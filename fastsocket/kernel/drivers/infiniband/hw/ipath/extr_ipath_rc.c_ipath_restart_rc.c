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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ opcode; } ;
struct ipath_swqe {TYPE_2__ wr; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct ipath_qp {scalar_t__ s_retry; int s_psn; int /*<<< orphan*/  piowait; int /*<<< orphan*/  timerwait; TYPE_1__ ibqp; int /*<<< orphan*/  s_last; } ;
struct ipath_ibdev {scalar_t__ n_rc_resends; int /*<<< orphan*/  pending_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 scalar_t__ IB_WR_RDMA_READ ; 
 int IPATH_PSN_MASK ; 
 struct ipath_swqe* get_swqe_ptr (struct ipath_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_error_qp (struct ipath_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_schedule_send (struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_send_complete (struct ipath_qp*,struct ipath_swqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_psn (struct ipath_qp*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 

void ipath_restart_rc(struct ipath_qp *qp, u32 psn)
{
	struct ipath_swqe *wqe = get_swqe_ptr(qp, qp->s_last);
	struct ipath_ibdev *dev;

	if (qp->s_retry == 0) {
		ipath_send_complete(qp, wqe, IB_WC_RETRY_EXC_ERR);
		ipath_error_qp(qp, IB_WC_WR_FLUSH_ERR);
		goto bail;
	}
	qp->s_retry--;

	/*
	 * Remove the QP from the timeout queue.
	 * Note: it may already have been removed by ipath_ib_timer().
	 */
	dev = to_idev(qp->ibqp.device);
	spin_lock(&dev->pending_lock);
	if (!list_empty(&qp->timerwait))
		list_del_init(&qp->timerwait);
	if (!list_empty(&qp->piowait))
		list_del_init(&qp->piowait);
	spin_unlock(&dev->pending_lock);

	if (wqe->wr.opcode == IB_WR_RDMA_READ)
		dev->n_rc_resends++;
	else
		dev->n_rc_resends += (qp->s_psn - psn) & IPATH_PSN_MASK;

	reset_psn(qp, psn);
	ipath_schedule_send(qp);

bail:
	return;
}