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
typedef  unsigned long long u64 ;
struct qib_devdata {TYPE_1__* cspec; } ;
struct TYPE_2__ {unsigned long long hwerrmask; int /*<<< orphan*/  sdepb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_7220_SERDES ; 
 int /*<<< orphan*/  IB_MPREG5 ; 
 int /*<<< orphan*/  IB_MPREG6 ; 
 unsigned long long QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR ; 
 int /*<<< orphan*/  epb_access (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kr_hwerrmask ; 
 int /*<<< orphan*/  kr_hwerrstatus ; 
 int /*<<< orphan*/  kr_ibserdesctrl ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 unsigned long long qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int qib_resync_ibepb (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_sd7220_clr_ibpar (struct qib_devdata*) ; 
 int qib_sd7220_reg_mod (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qib_ibsd_reset(struct qib_devdata *dd, int assert_rst)
{
	u64 rst_val;
	int ret = 0;
	unsigned long flags;

	rst_val = qib_read_kreg64(dd, kr_ibserdesctrl);
	if (assert_rst) {
		/*
		 * Vendor recommends "interrupting" uC before reset, to
		 * minimize possible glitches.
		 */
		spin_lock_irqsave(&dd->cspec->sdepb_lock, flags);
		epb_access(dd, IB_7220_SERDES, 1);
		rst_val |= 1ULL;
		/* Squelch possible parity error from _asserting_ reset */
		qib_write_kreg(dd, kr_hwerrmask,
			       dd->cspec->hwerrmask &
			       ~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR);
		qib_write_kreg(dd, kr_ibserdesctrl, rst_val);
		/* flush write, delay to ensure it took effect */
		qib_read_kreg32(dd, kr_scratch);
		udelay(2);
		/* once it's reset, can remove interrupt */
		epb_access(dd, IB_7220_SERDES, -1);
		spin_unlock_irqrestore(&dd->cspec->sdepb_lock, flags);
	} else {
		/*
		 * Before we de-assert reset, we need to deal with
		 * possible glitch on the Parity-error line.
		 * Suppress it around the reset, both in chip-level
		 * hwerrmask and in IB uC control reg. uC will allow
		 * it again during startup.
		 */
		u64 val;
		rst_val &= ~(1ULL);
		qib_write_kreg(dd, kr_hwerrmask,
			       dd->cspec->hwerrmask &
			       ~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR);

		ret = qib_resync_ibepb(dd);
		if (ret < 0)
			qib_dev_err(dd, "unable to re-sync IB EPB\n");

		/* set uC control regs to suppress parity errs */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG5, 1, 1);
		if (ret < 0)
			goto bail;
		/* IB uC code past Version 1.32.17 allow suppression of wdog */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6, 0x80,
			0x80);
		if (ret < 0) {
			qib_dev_err(dd, "Failed to set WDOG disable\n");
			goto bail;
		}
		qib_write_kreg(dd, kr_ibserdesctrl, rst_val);
		/* flush write, delay for startup */
		qib_read_kreg32(dd, kr_scratch);
		udelay(1);
		/* clear, then re-enable parity errs */
		qib_sd7220_clr_ibpar(dd);
		val = qib_read_kreg64(dd, kr_hwerrstatus);
		if (val & QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR) {
			qib_dev_err(dd, "IBUC Parity still set after RST\n");
			dd->cspec->hwerrmask &=
				~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR;
		}
		qib_write_kreg(dd, kr_hwerrmask,
			dd->cspec->hwerrmask);
	}

bail:
	return ret;
}