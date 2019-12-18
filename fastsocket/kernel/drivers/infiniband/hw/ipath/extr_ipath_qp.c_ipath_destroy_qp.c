#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  wq; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp_num; } ;
struct ipath_qp {scalar_t__ state; int /*<<< orphan*/  s_wq; struct ipath_qp* r_ud_sg_list; TYPE_5__ r_rq; TYPE_4__* ip; TYPE_3__ ibqp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; TYPE_2__* s_tx; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_dma_busy; int /*<<< orphan*/  wait_dma; int /*<<< orphan*/  s_task; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  piowait; int /*<<< orphan*/  timerwait; } ;
struct ipath_ibdev {int /*<<< orphan*/  n_qps_lock; int /*<<< orphan*/  n_qps_allocated; int /*<<< orphan*/  qp_table; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  txreq_free; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  list; struct ipath_qp* map_addr; } ;
struct TYPE_7__ {TYPE_1__ txreq; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_RESET ; 
 int IPATH_SDMA_TXREQ_F_FREEBUF ; 
 int /*<<< orphan*/  IPATH_S_ANY_WAIT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_qpn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_free_qp (int /*<<< orphan*/ *,struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_release_mmap_info ; 
 int /*<<< orphan*/  kfree (struct ipath_qp*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 struct ipath_qp* to_iqp (struct ib_qp*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int ipath_destroy_qp(struct ib_qp *ibqp)
{
	struct ipath_qp *qp = to_iqp(ibqp);
	struct ipath_ibdev *dev = to_idev(ibqp->device);

	/* Make sure HW and driver activity is stopped. */
	spin_lock_irq(&qp->s_lock);
	if (qp->state != IB_QPS_RESET) {
		qp->state = IB_QPS_RESET;
		spin_lock(&dev->pending_lock);
		if (!list_empty(&qp->timerwait))
			list_del_init(&qp->timerwait);
		if (!list_empty(&qp->piowait))
			list_del_init(&qp->piowait);
		spin_unlock(&dev->pending_lock);
		qp->s_flags &= ~IPATH_S_ANY_WAIT;
		spin_unlock_irq(&qp->s_lock);
		/* Stop the sending tasklet */
		tasklet_kill(&qp->s_task);
		wait_event(qp->wait_dma, !atomic_read(&qp->s_dma_busy));
	} else
		spin_unlock_irq(&qp->s_lock);

	ipath_free_qp(&dev->qp_table, qp);

	if (qp->s_tx) {
		atomic_dec(&qp->refcount);
		if (qp->s_tx->txreq.flags & IPATH_SDMA_TXREQ_F_FREEBUF)
			kfree(qp->s_tx->txreq.map_addr);
		spin_lock_irq(&dev->pending_lock);
		list_add(&qp->s_tx->txreq.list, &dev->txreq_free);
		spin_unlock_irq(&dev->pending_lock);
		qp->s_tx = NULL;
	}

	wait_event(qp->wait, !atomic_read(&qp->refcount));

	/* all user's cleaned up, mark it available */
	free_qpn(&dev->qp_table, qp->ibqp.qp_num);
	spin_lock(&dev->n_qps_lock);
	dev->n_qps_allocated--;
	spin_unlock(&dev->n_qps_lock);

	if (qp->ip)
		kref_put(&qp->ip->ref, ipath_release_mmap_info);
	else
		vfree(qp->r_rq.wq);
	kfree(qp->r_ud_sg_list);
	vfree(qp->s_wq);
	kfree(qp);
	return 0;
}