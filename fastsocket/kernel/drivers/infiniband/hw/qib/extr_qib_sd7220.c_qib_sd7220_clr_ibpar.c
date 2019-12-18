#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_7220_SERDES ; 
 int /*<<< orphan*/  IB_MPREG6 ; 
 int /*<<< orphan*/  QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR ; 
 int /*<<< orphan*/  UC_PAR_CLR_D ; 
 int /*<<< orphan*/  UC_PAR_CLR_M ; 
 int /*<<< orphan*/  kr_hwerrclear ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int qib_sd7220_reg_mod (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void qib_sd7220_clr_ibpar(struct qib_devdata *dd)
{
	int ret;

	/* clear, then re-enable parity errs */
	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6,
		UC_PAR_CLR_D, UC_PAR_CLR_M);
	if (ret < 0) {
		qib_dev_err(dd, "Failed clearing IBSerDes Parity err\n");
		goto bail;
	}
	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6, 0,
		UC_PAR_CLR_M);

	qib_read_kreg32(dd, kr_scratch);
	udelay(4);
	qib_write_kreg(dd, kr_hwerrclear,
		QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR);
	qib_read_kreg32(dd, kr_scratch);
bail:
	return;
}