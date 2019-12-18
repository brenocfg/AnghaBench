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
typedef  int u64 ;
typedef  int u16 ;
struct qib_pportdata {int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  lflags; struct qib_devdata* dd; } ;
struct qib_devdata {TYPE_1__* cspec; } ;
struct TYPE_2__ {int ibcctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIBL_IB_LINK_DISABLED ; 
 int QLOGIC_IB_IBCC_LINKCMD_DOWN ; 
 int QLOGIC_IB_IBCC_LINKCMD_SHIFT ; 
 int QLOGIC_IB_IBCC_LINKINITCMD_DISABLE ; 
 int QLOGIC_IB_IBCC_LINKINITCMD_SHIFT ; 
 int /*<<< orphan*/  kr_ibcctrl ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_set_ib_6120_lstate(struct qib_pportdata *ppd, u16 linkcmd,
				   u16 linitcmd)
{
	u64 mod_wd;
	struct qib_devdata *dd = ppd->dd;
	unsigned long flags;

	if (linitcmd == QLOGIC_IB_IBCC_LINKINITCMD_DISABLE) {
		/*
		 * If we are told to disable, note that so link-recovery
		 * code does not attempt to bring us back up.
		 */
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_IB_LINK_DISABLED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	} else if (linitcmd || linkcmd == QLOGIC_IB_IBCC_LINKCMD_DOWN) {
		/*
		 * Any other linkinitcmd will lead to LINKDOWN and then
		 * to INIT (if all is well), so clear flag to let
		 * link-recovery code attempt to bring us back up.
		 */
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_IB_LINK_DISABLED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	}

	mod_wd = (linkcmd << QLOGIC_IB_IBCC_LINKCMD_SHIFT) |
		(linitcmd << QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);

	qib_write_kreg(dd, kr_ibcctrl, dd->cspec->ibcctrl | mod_wd);
	/* write to chip to prevent back-to-back writes of control reg */
	qib_write_kreg(dd, kr_scratch, 0);
}