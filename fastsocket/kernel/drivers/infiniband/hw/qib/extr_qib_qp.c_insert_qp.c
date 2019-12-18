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
struct TYPE_2__ {int qp_num; int /*<<< orphan*/  device; } ;
struct qib_qp {int /*<<< orphan*/  next; TYPE_1__ ibqp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  port_num; } ;
struct qib_ibport {int /*<<< orphan*/  qp1; int /*<<< orphan*/  qp0; } ;
struct qib_ibdev {int /*<<< orphan*/  qpt_lock; int /*<<< orphan*/ * qp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int qpn_hash (struct qib_ibdev*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct qib_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insert_qp(struct qib_ibdev *dev, struct qib_qp *qp)
{
	struct qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	unsigned long flags;
	unsigned n = qpn_hash(dev, qp->ibqp.qp_num);

	spin_lock_irqsave(&dev->qpt_lock, flags);
	atomic_inc(&qp->refcount);

	if (qp->ibqp.qp_num == 0)
		rcu_assign_pointer(ibp->qp0, qp);
	else if (qp->ibqp.qp_num == 1)
		rcu_assign_pointer(ibp->qp1, qp);
	else {
		qp->next = dev->qp_table[n];
		rcu_assign_pointer(dev->qp_table[n], qp);
	}

	spin_unlock_irqrestore(&dev->qpt_lock, flags);
	synchronize_rcu();
}