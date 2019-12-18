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
typedef  int u64 ;
struct qib_pportdata {struct qib_devdata* dd; TYPE_1__* cpspec; int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  lflags; } ;
struct qib_devdata {int control; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  autoneg_work; int /*<<< orphan*/  autoneg_wait; scalar_t__ iblnkerrdelta; scalar_t__ iblnkerrsnap; scalar_t__ ibdeltainprog; scalar_t__ ibsymdelta; scalar_t__ ibsymsnap; TYPE_2__ chase_timer; scalar_t__ chase_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  CounterWrEnable ; 
 int /*<<< orphan*/  HwDiagCtrl ; 
 int /*<<< orphan*/  QIBL_IB_AUTONEG_INPROG ; 
 int QLOGIC_IB_C_FREEZEMODE ; 
 int QLOGIC_IB_C_LINKENABLE ; 
 int /*<<< orphan*/  QLOGIC_IB_IBCC_LINKINITCMD_DISABLE ; 
 int QLOGIC_IB_XGXS_RESET ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cr_iblinkerrrecov ; 
 int /*<<< orphan*/  cr_ibsymbolerr ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  kr_control ; 
 int /*<<< orphan*/  kr_hwdiagctrl ; 
 int /*<<< orphan*/  kr_xgxs_cfg ; 
 int qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_set_ib_7220_lstate (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int read_7220_creg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_7220_relock_poll (struct qib_devdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_7220_creg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qib_7220_quiet_serdes(struct qib_pportdata *ppd)
{
	u64 val;
	struct qib_devdata *dd = ppd->dd;
	unsigned long flags;

	/* disable IBC */
	dd->control &= ~QLOGIC_IB_C_LINKENABLE;
	qib_write_kreg(dd, kr_control,
		       dd->control | QLOGIC_IB_C_FREEZEMODE);

	ppd->cpspec->chase_end = 0;
	if (ppd->cpspec->chase_timer.data) /* if initted */
		del_timer_sync(&ppd->cpspec->chase_timer);

	if (ppd->cpspec->ibsymdelta || ppd->cpspec->iblnkerrdelta ||
	    ppd->cpspec->ibdeltainprog) {
		u64 diagc;

		/* enable counter writes */
		diagc = qib_read_kreg64(dd, kr_hwdiagctrl);
		qib_write_kreg(dd, kr_hwdiagctrl,
			       diagc | SYM_MASK(HwDiagCtrl, CounterWrEnable));

		if (ppd->cpspec->ibsymdelta || ppd->cpspec->ibdeltainprog) {
			val = read_7220_creg32(dd, cr_ibsymbolerr);
			if (ppd->cpspec->ibdeltainprog)
				val -= val - ppd->cpspec->ibsymsnap;
			val -= ppd->cpspec->ibsymdelta;
			write_7220_creg(dd, cr_ibsymbolerr, val);
		}
		if (ppd->cpspec->iblnkerrdelta || ppd->cpspec->ibdeltainprog) {
			val = read_7220_creg32(dd, cr_iblinkerrrecov);
			if (ppd->cpspec->ibdeltainprog)
				val -= val - ppd->cpspec->iblnkerrsnap;
			val -= ppd->cpspec->iblnkerrdelta;
			write_7220_creg(dd, cr_iblinkerrrecov, val);
		}

		/* and disable counter writes */
		qib_write_kreg(dd, kr_hwdiagctrl, diagc);
	}
	qib_set_ib_7220_lstate(ppd, 0, QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags &= ~QIBL_IB_AUTONEG_INPROG;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	wake_up(&ppd->cpspec->autoneg_wait);
	cancel_delayed_work_sync(&ppd->cpspec->autoneg_work);

	shutdown_7220_relock_poll(ppd->dd);
	val = qib_read_kreg64(ppd->dd, kr_xgxs_cfg);
	val |= QLOGIC_IB_XGXS_RESET;
	qib_write_kreg(ppd->dd, kr_xgxs_cfg, val);
}