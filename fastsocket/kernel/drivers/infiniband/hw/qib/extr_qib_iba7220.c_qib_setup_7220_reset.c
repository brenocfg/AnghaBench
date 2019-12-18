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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qib_devdata {int flags; int control; int revision; TYPE_3__* pport; TYPE_2__* cspec; int /*<<< orphan*/  lbus_width; int /*<<< orphan*/ * kregbase; scalar_t__ int_counter; int /*<<< orphan*/  unit; } ;
struct TYPE_6__ {int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  lflags; TYPE_1__* cpspec; } ;
struct TYPE_5__ {int presets_needed; } ;
struct TYPE_4__ {int ibcddrctrl; scalar_t__ iblnkerrdelta; scalar_t__ ibsymdelta; scalar_t__ ibdeltainprog; } ;

/* Variables and functions */
 int IBA7220_IBC_IBTA_1_2_MASK ; 
 int /*<<< orphan*/  QIBL_IB_AUTONEG_FAILED ; 
 int /*<<< orphan*/  QIBL_IB_FORCE_NOTIFY ; 
 int QIB_INITTED ; 
 int QIB_PRESENT ; 
 int QLOGIC_IB_C_RESET ; 
 size_t kr_control ; 
 size_t kr_revision ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qib_7220_init_hwerrors (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_7220_set_intr_state (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 int /*<<< orphan*/  qib_pcie_getcmd (struct qib_devdata*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qib_pcie_params (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_pcie_reenable (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qib_reinit_intr (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,size_t,unsigned long long) ; 
 int readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qib_setup_7220_reset(struct qib_devdata *dd)
{
	u64 val;
	int i;
	int ret;
	u16 cmdval;
	u8 int_line, clinesz;
	unsigned long flags;

	qib_pcie_getcmd(dd, &cmdval, &int_line, &clinesz);

	/* Use dev_err so it shows up in logs, etc. */
	qib_dev_err(dd, "Resetting InfiniPath unit %u\n", dd->unit);

	/* no interrupts till re-initted */
	qib_7220_set_intr_state(dd, 0);

	dd->pport->cpspec->ibdeltainprog = 0;
	dd->pport->cpspec->ibsymdelta = 0;
	dd->pport->cpspec->iblnkerrdelta = 0;

	/*
	 * Keep chip from being accessed until we are ready.  Use
	 * writeq() directly, to allow the write even though QIB_PRESENT
	 * isn't' set.
	 */
	dd->flags &= ~(QIB_INITTED | QIB_PRESENT);
	dd->int_counter = 0; /* so we check interrupts work again */
	val = dd->control | QLOGIC_IB_C_RESET;
	writeq(val, &dd->kregbase[kr_control]);
	mb(); /* prevent compiler reordering around actual reset */

	for (i = 1; i <= 5; i++) {
		/*
		 * Allow MBIST, etc. to complete; longer on each retry.
		 * We sometimes get machine checks from bus timeout if no
		 * response, so for now, make it *really* long.
		 */
		msleep(1000 + (1 + i) * 2000);

		qib_pcie_reenable(dd, cmdval, int_line, clinesz);

		/*
		 * Use readq directly, so we don't need to mark it as PRESENT
		 * until we get a successful indication that all is well.
		 */
		val = readq(&dd->kregbase[kr_revision]);
		if (val == dd->revision) {
			dd->flags |= QIB_PRESENT; /* it's back */
			ret = qib_reinit_intr(dd);
			goto bail;
		}
	}
	ret = 0; /* failed */

bail:
	if (ret) {
		if (qib_pcie_params(dd, dd->lbus_width, NULL, NULL))
			qib_dev_err(dd,
				"Reset failed to setup PCIe or interrupts; continuing anyway\n");

		/* hold IBC in reset, no sends, etc till later */
		qib_write_kreg(dd, kr_control, 0ULL);

		/* clear the reset error, init error/hwerror mask */
		qib_7220_init_hwerrors(dd);

		/* do setup similar to speed or link-width changes */
		if (dd->pport->cpspec->ibcddrctrl & IBA7220_IBC_IBTA_1_2_MASK)
			dd->cspec->presets_needed = 1;
		spin_lock_irqsave(&dd->pport->lflags_lock, flags);
		dd->pport->lflags |= QIBL_IB_FORCE_NOTIFY;
		dd->pport->lflags &= ~QIBL_IB_AUTONEG_FAILED;
		spin_unlock_irqrestore(&dd->pport->lflags_lock, flags);
	}

	return ret;
}