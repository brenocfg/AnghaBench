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
typedef  int u32 ;
struct TYPE_5__ {int qp_num; } ;
struct qib_qp {int /*<<< orphan*/  refcount; TYPE_2__ ibqp; int /*<<< orphan*/  next; } ;
struct qib_ibport {int /*<<< orphan*/  qp1; int /*<<< orphan*/  qp0; } ;
struct qib_ibdev {int /*<<< orphan*/ * qp_table; } ;
struct TYPE_6__ {TYPE_1__* dd; } ;
struct TYPE_4__ {struct qib_ibdev verbs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 TYPE_3__* ppd_from_ibp (struct qib_ibport*) ; 
 unsigned int qpn_hash (struct qib_ibdev*,int) ; 
 struct qib_qp* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct qib_qp *qib_lookup_qpn(struct qib_ibport *ibp, u32 qpn)
{
	struct qib_qp *qp = NULL;

	if (unlikely(qpn <= 1)) {
		rcu_read_lock();
		if (qpn == 0)
			qp = rcu_dereference(ibp->qp0);
		else
			qp = rcu_dereference(ibp->qp1);
	} else {
		struct qib_ibdev *dev = &ppd_from_ibp(ibp)->dd->verbs_dev;
		unsigned n = qpn_hash(dev, qpn);

		rcu_read_lock();
		for (qp = rcu_dereference(dev->qp_table[n]); qp;
			qp = rcu_dereference(qp->next))
			if (qp->ibqp.qp_num == qpn)
				break;
	}
	if (qp)
		if (unlikely(!atomic_inc_not_zero(&qp->refcount)))
			qp = NULL;

	rcu_read_unlock();
	return qp;
}