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
struct ipath_devdata {int ipath_rx_pol_inv; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_xgxsconfig; int /*<<< orphan*/  kr_serdesstatus; int /*<<< orphan*/  kr_serdesconfig1; int /*<<< orphan*/  kr_serdesconfig0; int /*<<< orphan*/  kr_scratch; int /*<<< orphan*/  kr_hwerrclear; int /*<<< orphan*/  kr_hwerrstatus; } ;

/* Variables and functions */
 int INFINIPATH_HWE_SERDESPLLFAILED ; 
 int INFINIPATH_SERDC0_RESET_MASK ; 
 int INFINIPATH_SERDC0_RESET_PLL ; 
 int INFINIPATH_SERDC0_TXIDLE ; 
 int INFINIPATH_XGXS_RESET ; 
 int INFINIPATH_XGXS_RX_POL_MASK ; 
 int INFINIPATH_XGXS_RX_POL_SHIFT ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  ipath_dbg (char*) ; 
 int ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ipath_ht_bringup_serdes(struct ipath_devdata *dd)
{
	u64 val, config1;
	int ret = 0, change = 0;

	ipath_dbg("Trying to bringup serdes\n");

	if (ipath_read_kreg64(dd, dd->ipath_kregs->kr_hwerrstatus) &
	    INFINIPATH_HWE_SERDESPLLFAILED)
	{
		ipath_dbg("At start, serdes PLL failed bit set in "
			  "hwerrstatus, clearing and continuing\n");
		ipath_write_kreg(dd, dd->ipath_kregs->kr_hwerrclear,
				 INFINIPATH_HWE_SERDESPLLFAILED);
	}

	val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_serdesconfig0);
	config1 = ipath_read_kreg64(dd, dd->ipath_kregs->kr_serdesconfig1);

	ipath_cdbg(VERBOSE, "Initial serdes status is config0=%llx "
		   "config1=%llx, sstatus=%llx xgxs %llx\n",
		   (unsigned long long) val, (unsigned long long) config1,
		   (unsigned long long)
		   ipath_read_kreg64(dd, dd->ipath_kregs->kr_serdesstatus),
		   (unsigned long long)
		   ipath_read_kreg64(dd, dd->ipath_kregs->kr_xgxsconfig));

	/* force reset on */
	val |= INFINIPATH_SERDC0_RESET_PLL
		/* | INFINIPATH_SERDC0_RESET_MASK */
		;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_serdesconfig0, val);
	udelay(15);		/* need pll reset set at least for a bit */

	if (val & INFINIPATH_SERDC0_RESET_PLL) {
		u64 val2 = val &= ~INFINIPATH_SERDC0_RESET_PLL;
		/* set lane resets, and tx idle, during pll reset */
		val2 |= INFINIPATH_SERDC0_RESET_MASK |
			INFINIPATH_SERDC0_TXIDLE;
		ipath_cdbg(VERBOSE, "Clearing serdes PLL reset (writing "
			   "%llx)\n", (unsigned long long) val2);
		ipath_write_kreg(dd, dd->ipath_kregs->kr_serdesconfig0,
				 val2);
		/*
		 * be sure chip saw it
		 */
		val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_scratch);
		/*
		 * need pll reset clear at least 11 usec before lane
		 * resets cleared; give it a few more
		 */
		udelay(15);
		val = val2;	/* for check below */
	}

	if (val & (INFINIPATH_SERDC0_RESET_PLL |
		   INFINIPATH_SERDC0_RESET_MASK |
		   INFINIPATH_SERDC0_TXIDLE)) {
		val &= ~(INFINIPATH_SERDC0_RESET_PLL |
			 INFINIPATH_SERDC0_RESET_MASK |
			 INFINIPATH_SERDC0_TXIDLE);
		/* clear them */
		ipath_write_kreg(dd, dd->ipath_kregs->kr_serdesconfig0,
				 val);
	}

	val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_xgxsconfig);
	if (val & INFINIPATH_XGXS_RESET) {
		/* normally true after boot */
		val &= ~INFINIPATH_XGXS_RESET;
		change = 1;
	}
	if (((val >> INFINIPATH_XGXS_RX_POL_SHIFT) &
	     INFINIPATH_XGXS_RX_POL_MASK) != dd->ipath_rx_pol_inv ) {
		/* need to compensate for Tx inversion in partner */
		val &= ~(INFINIPATH_XGXS_RX_POL_MASK <<
		         INFINIPATH_XGXS_RX_POL_SHIFT);
		val |= dd->ipath_rx_pol_inv <<
			INFINIPATH_XGXS_RX_POL_SHIFT;
		change = 1;
	}
	if (change)
		ipath_write_kreg(dd, dd->ipath_kregs->kr_xgxsconfig, val);

	val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_serdesconfig0);

	/* clear current and de-emphasis bits */
	config1 &= ~0x0ffffffff00ULL;
	/* set current to 20ma */
	config1 |= 0x00000000000ULL;
	/* set de-emphasis to -5.68dB */
	config1 |= 0x0cccc000000ULL;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_serdesconfig1, config1);

	ipath_cdbg(VERBOSE, "After setup: serdes status is config0=%llx "
		   "config1=%llx, sstatus=%llx xgxs %llx\n",
		   (unsigned long long) val, (unsigned long long) config1,
		   (unsigned long long)
		   ipath_read_kreg64(dd, dd->ipath_kregs->kr_serdesstatus),
		   (unsigned long long)
		   ipath_read_kreg64(dd, dd->ipath_kregs->kr_xgxsconfig));

	return ret;		/* for now, say we always succeeded */
}