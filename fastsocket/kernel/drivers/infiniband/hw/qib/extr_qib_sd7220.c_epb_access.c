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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int EPB_ACC_GNT ; 
 int EPB_ACC_REQ ; 
#define  IB_7220_SERDES 130 
#define  PCIE_SERDES0 129 
#define  PCIE_SERDES1 128 
 int /*<<< orphan*/  kr_ibsd_epb_access_ctrl ; 
 int /*<<< orphan*/  kr_pciesd_epb_access_ctrl ; 
 int /*<<< orphan*/  kr_scratch ; 
 int qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int epb_access(struct qib_devdata *dd, int sdnum, int claim)
{
	u16 acc;
	u64 accval;
	int owned = 0;
	u64 oct_sel = 0;

	switch (sdnum) {
	case IB_7220_SERDES:
		/*
		 * The IB SERDES "ownership" is fairly simple. A single each
		 * request/grant.
		 */
		acc = kr_ibsd_epb_access_ctrl;
		break;

	case PCIE_SERDES0:
	case PCIE_SERDES1:
		/* PCIe SERDES has two "octants", need to select which */
		acc = kr_pciesd_epb_access_ctrl;
		oct_sel = (2 << (sdnum - PCIE_SERDES0));
		break;

	default:
		return 0;
	}

	/* Make sure any outstanding transaction was seen */
	qib_read_kreg32(dd, kr_scratch);
	udelay(15);

	accval = qib_read_kreg32(dd, acc);

	owned = !!(accval & EPB_ACC_GNT);
	if (claim < 0) {
		/* Need to release */
		u64 pollval;
		/*
		 * The only writeable bits are the request and CS.
		 * Both should be clear
		 */
		u64 newval = 0;
		qib_write_kreg(dd, acc, newval);
		/* First read after write is not trustworthy */
		pollval = qib_read_kreg32(dd, acc);
		udelay(5);
		pollval = qib_read_kreg32(dd, acc);
		if (pollval & EPB_ACC_GNT)
			owned = -1;
	} else if (claim > 0) {
		/* Need to claim */
		u64 pollval;
		u64 newval = EPB_ACC_REQ | oct_sel;
		qib_write_kreg(dd, acc, newval);
		/* First read after write is not trustworthy */
		pollval = qib_read_kreg32(dd, acc);
		udelay(5);
		pollval = qib_read_kreg32(dd, acc);
		if (!(pollval & EPB_ACC_GNT))
			owned = -1;
	}
	return owned;
}