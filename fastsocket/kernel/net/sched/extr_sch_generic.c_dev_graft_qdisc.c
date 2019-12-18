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
struct netdev_queue {int /*<<< orphan*/  qdisc; struct Qdisc* qdisc_sleeping; } ;
struct Qdisc {int /*<<< orphan*/  refcnt; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (struct Qdisc*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct Qdisc *dev_graft_qdisc(struct netdev_queue *dev_queue,
			      struct Qdisc *qdisc)
{
	struct Qdisc *oqdisc = dev_queue->qdisc_sleeping;
	spinlock_t *root_lock;

	root_lock = qdisc_lock(oqdisc);
	spin_lock_bh(root_lock);

	/* Prune old scheduler */
	if (oqdisc && atomic_read(&oqdisc->refcnt) <= 1)
		qdisc_reset(oqdisc);

	/* ... and graft new one */
	if (qdisc == NULL)
		qdisc = &noop_qdisc;
	dev_queue->qdisc_sleeping = qdisc;
	rcu_assign_pointer(dev_queue->qdisc, &noop_qdisc);

	spin_unlock_bh(root_lock);

	return oqdisc;
}