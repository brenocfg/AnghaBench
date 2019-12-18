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
struct TYPE_6__ {int /*<<< orphan*/  wq; } ;
struct TYPE_4__ {int /*<<< orphan*/  qp_num; } ;
struct qib_qp {scalar_t__ state; int s_flags; struct qib_qp* s_hdr; int /*<<< orphan*/  s_wq; TYPE_3__ r_rq; TYPE_2__* ip; TYPE_1__ ibqp; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; int /*<<< orphan*/ * s_tx; int /*<<< orphan*/  s_dma_busy; int /*<<< orphan*/  wait_dma; int /*<<< orphan*/  s_timer; int /*<<< orphan*/  s_work; int /*<<< orphan*/  iowait; } ;
struct qib_ibdev {int /*<<< orphan*/  n_qps_lock; int /*<<< orphan*/  n_qps_allocated; int /*<<< orphan*/  qpn_table; int /*<<< orphan*/  pending_lock; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_RESET ; 
 int QIB_S_ANY_WAIT ; 
 int QIB_S_TIMER ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_mr_refs (struct qib_qp*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_qpn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qib_qp*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_put_txreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_release_mmap_info ; 
 int /*<<< orphan*/  remove_qp (struct qib_ibdev*,struct qib_qp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 struct qib_qp* to_iqp (struct ib_qp*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int qib_destroy_qp(struct ib_qp *ibqp)
{
	struct qib_qp *qp = to_iqp(ibqp);
	struct qib_ibdev *dev = to_idev(ibqp->device);

	/* Make sure HW and driver activity is stopped. */
	spin_lock_irq(&qp->s_lock);
	if (qp->state != IB_QPS_RESET) {
		qp->state = IB_QPS_RESET;
		spin_lock(&dev->pending_lock);
		if (!list_empty(&qp->iowait))
			list_del_init(&qp->iowait);
		spin_unlock(&dev->pending_lock);
		qp->s_flags &= ~(QIB_S_TIMER | QIB_S_ANY_WAIT);
		spin_unlock_irq(&qp->s_lock);
		cancel_work_sync(&qp->s_work);
		del_timer_sync(&qp->s_timer);
		wait_event(qp->wait_dma, !atomic_read(&qp->s_dma_busy));
		if (qp->s_tx) {
			qib_put_txreq(qp->s_tx);
			qp->s_tx = NULL;
		}
		remove_qp(dev, qp);
		wait_event(qp->wait, !atomic_read(&qp->refcount));
		clear_mr_refs(qp, 1);
	} else
		spin_unlock_irq(&qp->s_lock);

	/* all user's cleaned up, mark it available */
	free_qpn(&dev->qpn_table, qp->ibqp.qp_num);
	spin_lock(&dev->n_qps_lock);
	dev->n_qps_allocated--;
	spin_unlock(&dev->n_qps_lock);

	if (qp->ip)
		kref_put(&qp->ip->ref, qib_release_mmap_info);
	else
		vfree(qp->r_rq.wq);
	vfree(qp->s_wq);
	kfree(qp->s_hdr);
	kfree(qp);
	return 0;
}