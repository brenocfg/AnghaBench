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
struct ipath_qp_table {int max; int /*<<< orphan*/  lock; struct ipath_qp** table; } ;
struct TYPE_2__ {int qp_num; } ;
struct ipath_qp {int /*<<< orphan*/  refcount; struct ipath_qp* next; TYPE_1__ ibqp; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int alloc_qpn (struct ipath_qp_table*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ipath_alloc_qpn(struct ipath_qp_table *qpt, struct ipath_qp *qp,
			   enum ib_qp_type type)
{
	unsigned long flags;
	int ret;

	ret = alloc_qpn(qpt, type);
	if (ret < 0)
		goto bail;
	qp->ibqp.qp_num = ret;

	/* Add the QP to the hash table. */
	spin_lock_irqsave(&qpt->lock, flags);

	ret %= qpt->max;
	qp->next = qpt->table[ret];
	qpt->table[ret] = qp;
	atomic_inc(&qp->refcount);

	spin_unlock_irqrestore(&qpt->lock, flags);
	ret = 0;

bail:
	return ret;
}