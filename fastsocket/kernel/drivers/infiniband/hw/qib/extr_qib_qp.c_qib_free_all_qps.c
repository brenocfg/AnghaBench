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
struct qib_qp {int /*<<< orphan*/  next; } ;
struct qib_ibport {int /*<<< orphan*/  qp1; int /*<<< orphan*/  qp0; } ;
struct qib_ibdev {unsigned int qp_table_size; int /*<<< orphan*/  qpt_lock; int /*<<< orphan*/ * qp_table; } ;
struct qib_devdata {unsigned int num_pports; TYPE_1__* pport; struct qib_ibdev verbs_dev; } ;
struct TYPE_2__ {struct qib_ibport ibport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_mcast_tree_empty (struct qib_ibport*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_dereference (int /*<<< orphan*/ ) ; 
 struct qib_qp* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

unsigned qib_free_all_qps(struct qib_devdata *dd)
{
	struct qib_ibdev *dev = &dd->verbs_dev;
	unsigned long flags;
	struct qib_qp *qp;
	unsigned n, qp_inuse = 0;

	for (n = 0; n < dd->num_pports; n++) {
		struct qib_ibport *ibp = &dd->pport[n].ibport_data;

		if (!qib_mcast_tree_empty(ibp))
			qp_inuse++;
		rcu_read_lock();
		if (rcu_dereference(ibp->qp0))
			qp_inuse++;
		if (rcu_dereference(ibp->qp1))
			qp_inuse++;
		rcu_read_unlock();
	}

	spin_lock_irqsave(&dev->qpt_lock, flags);
	for (n = 0; n < dev->qp_table_size; n++) {
		qp = rcu_dereference_protected(dev->qp_table[n],
			lockdep_is_held(&dev->qpt_lock));
		rcu_assign_pointer(dev->qp_table[n], NULL);

		for (; qp; qp = rcu_dereference_protected(qp->next,
					lockdep_is_held(&dev->qpt_lock)))
			qp_inuse++;
	}
	spin_unlock_irqrestore(&dev->qpt_lock, flags);
	synchronize_rcu();

	return qp_inuse;
}