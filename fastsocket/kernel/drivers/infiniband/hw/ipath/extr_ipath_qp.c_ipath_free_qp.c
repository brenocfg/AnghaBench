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
struct ipath_qp_table {size_t max; int /*<<< orphan*/  lock; struct ipath_qp** table; } ;
struct TYPE_2__ {size_t qp_num; } ;
struct ipath_qp {int /*<<< orphan*/  refcount; struct ipath_qp* next; TYPE_1__ ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipath_free_qp(struct ipath_qp_table *qpt, struct ipath_qp *qp)
{
	struct ipath_qp *q, **qpp;
	unsigned long flags;

	spin_lock_irqsave(&qpt->lock, flags);

	/* Remove QP from the hash table. */
	qpp = &qpt->table[qp->ibqp.qp_num % qpt->max];
	for (; (q = *qpp) != NULL; qpp = &q->next) {
		if (q == qp) {
			*qpp = qp->next;
			qp->next = NULL;
			atomic_dec(&qp->refcount);
			break;
		}
	}

	spin_unlock_irqrestore(&qpt->lock, flags);
}