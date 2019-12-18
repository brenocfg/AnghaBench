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
struct c2_qp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  idr; } ;
struct c2_dev {TYPE_1__ qp_table; } ;

/* Variables and functions */
 struct c2_qp* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct c2_qp *c2_find_qpn(struct c2_dev *c2dev, int qpn)
{
	unsigned long flags;
	struct c2_qp *qp;

	spin_lock_irqsave(&c2dev->qp_table.lock, flags);
	qp = idr_find(&c2dev->qp_table.idr, qpn);
	spin_unlock_irqrestore(&c2dev->qp_table.lock, flags);
	return qp;
}