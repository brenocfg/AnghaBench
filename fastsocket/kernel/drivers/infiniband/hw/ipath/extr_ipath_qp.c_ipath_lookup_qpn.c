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
typedef  size_t u32 ;
struct ipath_qp_table {size_t max; int /*<<< orphan*/  lock; struct ipath_qp** table; } ;
struct TYPE_2__ {size_t qp_num; } ;
struct ipath_qp {int /*<<< orphan*/  refcount; TYPE_1__ ibqp; struct ipath_qp* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ipath_qp *ipath_lookup_qpn(struct ipath_qp_table *qpt, u32 qpn)
{
	unsigned long flags;
	struct ipath_qp *qp;

	spin_lock_irqsave(&qpt->lock, flags);

	for (qp = qpt->table[qpn % qpt->max]; qp; qp = qp->next) {
		if (qp->ibqp.qp_num == qpn) {
			atomic_inc(&qp->refcount);
			break;
		}
	}

	spin_unlock_irqrestore(&qpt->lock, flags);
	return qp;
}