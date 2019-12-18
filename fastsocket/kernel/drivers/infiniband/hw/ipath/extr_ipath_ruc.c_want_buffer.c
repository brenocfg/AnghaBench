#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ qp_type; } ;
struct ipath_qp {TYPE_2__ ibqp; } ;
struct ipath_devdata {int ipath_flags; int /*<<< orphan*/  ipath_sendctrl_lock; TYPE_1__* ipath_kregs; int /*<<< orphan*/  ipath_sendctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  kr_scratch; int /*<<< orphan*/  kr_sendctrl; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_SMI ; 
 int /*<<< orphan*/  INFINIPATH_S_PIOINTBUFAVAIL ; 
 int IPATH_HAS_SEND_DMA ; 
 int /*<<< orphan*/  ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void want_buffer(struct ipath_devdata *dd, struct ipath_qp *qp)
{
	if (!(dd->ipath_flags & IPATH_HAS_SEND_DMA) ||
	    qp->ibqp.qp_type == IB_QPT_SMI) {
		unsigned long flags;

		spin_lock_irqsave(&dd->ipath_sendctrl_lock, flags);
		dd->ipath_sendctrl |= INFINIPATH_S_PIOINTBUFAVAIL;
		ipath_write_kreg(dd, dd->ipath_kregs->kr_sendctrl,
				 dd->ipath_sendctrl);
		ipath_read_kreg64(dd, dd->ipath_kregs->kr_scratch);
		spin_unlock_irqrestore(&dd->ipath_sendctrl_lock, flags);
	}
}