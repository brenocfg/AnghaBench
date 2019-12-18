#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qib_pportdata {int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  lflags; TYPE_1__* cpspec; } ;
struct qib_devdata {int flags; int control; int revision; int num_pports; struct qib_pportdata* pport; TYPE_3__* cspec; int /*<<< orphan*/  lbus_width; int /*<<< orphan*/ * kregbase; scalar_t__ int_counter; int /*<<< orphan*/  unit; } ;
struct TYPE_6__ {int entry; } ;
struct TYPE_8__ {TYPE_2__ msix; } ;
struct TYPE_7__ {int num_msix_entries; TYPE_4__* msix_entries; } ;
struct TYPE_5__ {scalar_t__ ibmalfdelta; scalar_t__ iblnkerrdelta; scalar_t__ ibsymdelta; scalar_t__ ibdeltainprog; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QIBL_IB_AUTONEG_FAILED ; 
 int /*<<< orphan*/  QIBL_IB_FORCE_NOTIFY ; 
 int QIB_7322_MsixTable_OFFS ; 
 int QIB_BADINTR ; 
 int QIB_DOING_RESET ; 
 int QIB_INITTED ; 
 int QIB_PRESENT ; 
 int QLOGIC_IB_C_RESET ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 size_t kr_control ; 
 size_t kr_revision ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qib_7322_nomsix (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_7322_set_intr_state (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 int /*<<< orphan*/  qib_pcie_getcmd (struct qib_devdata*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qib_pcie_params (struct qib_devdata*,int /*<<< orphan*/ ,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  qib_pcie_reenable (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qib_read_kreg64 (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  qib_setup_7322_interrupt (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int,int) ; 
 int readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_7322_init_portregs (struct qib_pportdata*) ; 
 int /*<<< orphan*/  write_7322_initregs (struct qib_devdata*) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qib_do_7322_reset(struct qib_devdata *dd)
{
	u64 val;
	u64 *msix_vecsave;
	int i, msix_entries, ret = 1;
	u16 cmdval;
	u8 int_line, clinesz;
	unsigned long flags;

	/* Use dev_err so it shows up in logs, etc. */
	qib_dev_err(dd, "Resetting InfiniPath unit %u\n", dd->unit);

	qib_pcie_getcmd(dd, &cmdval, &int_line, &clinesz);

	msix_entries = dd->cspec->num_msix_entries;

	/* no interrupts till re-initted */
	qib_7322_set_intr_state(dd, 0);

	if (msix_entries) {
		qib_7322_nomsix(dd);
		/* can be up to 512 bytes, too big for stack */
		msix_vecsave = kmalloc(2 * dd->cspec->num_msix_entries *
			sizeof(u64), GFP_KERNEL);
		if (!msix_vecsave)
			qib_dev_err(dd, "No mem to save MSIx data\n");
	} else
		msix_vecsave = NULL;

	/*
	 * Core PCI (as of 2.6.18) doesn't save or rewrite the full vector
	 * info that is set up by the BIOS, so we have to save and restore
	 * it ourselves.   There is some risk something could change it,
	 * after we save it, but since we have disabled the MSIx, it
	 * shouldn't be touched...
	 */
	for (i = 0; i < msix_entries; i++) {
		u64 vecaddr, vecdata;
		vecaddr = qib_read_kreg64(dd, 2 * i +
				  (QIB_7322_MsixTable_OFFS / sizeof(u64)));
		vecdata = qib_read_kreg64(dd, 1 + 2 * i +
				  (QIB_7322_MsixTable_OFFS / sizeof(u64)));
		if (msix_vecsave) {
			msix_vecsave[2 * i] = vecaddr;
			/* save it without the masked bit set */
			msix_vecsave[1 + 2 * i] = vecdata & ~0x100000000ULL;
		}
	}

	dd->pport->cpspec->ibdeltainprog = 0;
	dd->pport->cpspec->ibsymdelta = 0;
	dd->pport->cpspec->iblnkerrdelta = 0;
	dd->pport->cpspec->ibmalfdelta = 0;
	dd->int_counter = 0; /* so we check interrupts work again */

	/*
	 * Keep chip from being accessed until we are ready.  Use
	 * writeq() directly, to allow the write even though QIB_PRESENT
	 * isn't' set.
	 */
	dd->flags &= ~(QIB_INITTED | QIB_PRESENT | QIB_BADINTR);
	dd->flags |= QIB_DOING_RESET;
	val = dd->control | QLOGIC_IB_C_RESET;
	writeq(val, &dd->kregbase[kr_control]);

	for (i = 1; i <= 5; i++) {
		/*
		 * Allow MBIST, etc. to complete; longer on each retry.
		 * We sometimes get machine checks from bus timeout if no
		 * response, so for now, make it *really* long.
		 */
		msleep(1000 + (1 + i) * 3000);

		qib_pcie_reenable(dd, cmdval, int_line, clinesz);

		/*
		 * Use readq directly, so we don't need to mark it as PRESENT
		 * until we get a successful indication that all is well.
		 */
		val = readq(&dd->kregbase[kr_revision]);
		if (val == dd->revision)
			break;
		if (i == 5) {
			qib_dev_err(dd,
				"Failed to initialize after reset, unusable\n");
			ret = 0;
			goto  bail;
		}
	}

	dd->flags |= QIB_PRESENT; /* it's back */

	if (msix_entries) {
		/* restore the MSIx vector address and data if saved above */
		for (i = 0; i < msix_entries; i++) {
			dd->cspec->msix_entries[i].msix.entry = i;
			if (!msix_vecsave || !msix_vecsave[2 * i])
				continue;
			qib_write_kreg(dd, 2 * i +
				(QIB_7322_MsixTable_OFFS / sizeof(u64)),
				msix_vecsave[2 * i]);
			qib_write_kreg(dd, 1 + 2 * i +
				(QIB_7322_MsixTable_OFFS / sizeof(u64)),
				msix_vecsave[1 + 2 * i]);
		}
	}

	/* initialize the remaining registers.  */
	for (i = 0; i < dd->num_pports; ++i)
		write_7322_init_portregs(&dd->pport[i]);
	write_7322_initregs(dd);

	if (qib_pcie_params(dd, dd->lbus_width,
			    &dd->cspec->num_msix_entries,
			    dd->cspec->msix_entries))
		qib_dev_err(dd,
			"Reset failed to setup PCIe or interrupts; continuing anyway\n");

	qib_setup_7322_interrupt(dd, 1);

	for (i = 0; i < dd->num_pports; ++i) {
		struct qib_pportdata *ppd = &dd->pport[i];

		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_IB_FORCE_NOTIFY;
		ppd->lflags &= ~QIBL_IB_AUTONEG_FAILED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	}

bail:
	dd->flags &= ~QIB_DOING_RESET; /* OK or not, no longer resetting */
	kfree(msix_vecsave);
	return ret;
}