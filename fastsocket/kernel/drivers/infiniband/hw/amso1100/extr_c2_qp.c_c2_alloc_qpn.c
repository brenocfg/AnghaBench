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
struct c2_qp {int /*<<< orphan*/  qpn; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  last; int /*<<< orphan*/  idr; } ;
struct c2_dev {TYPE_1__ qp_table; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct c2_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int c2_alloc_qpn(struct c2_dev *c2dev, struct c2_qp *qp)
{
	int ret;

        do {
		spin_lock_irq(&c2dev->qp_table.lock);
		ret = idr_get_new_above(&c2dev->qp_table.idr, qp,
					c2dev->qp_table.last++, &qp->qpn);
		spin_unlock_irq(&c2dev->qp_table.lock);
        } while ((ret == -EAGAIN) &&
	 	 idr_pre_get(&c2dev->qp_table.idr, GFP_KERNEL));
	return ret;
}