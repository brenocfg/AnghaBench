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
typedef  int u32 ;
struct ipath_devdata {unsigned long ipath_errormask; int ipath_flags; unsigned long ipath_hwerrmask; TYPE_2__* pcidev; TYPE_1__* ipath_kregs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kr_intclear; int /*<<< orphan*/  kr_errorclear; int /*<<< orphan*/  kr_hwerrclear; int /*<<< orphan*/  kr_errormask; int /*<<< orphan*/  kr_control; int /*<<< orphan*/  kr_hwerrstatus; } ;

/* Variables and functions */
 int INFINIPATH_C_FREEZEMODE ; 
 int IPATH_INITTED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,unsigned long,unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  ipath_dbg (char*,int,unsigned long,unsigned long) ; 
 int ipath_read_kreg32 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 unsigned long ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void ipath_chk_errormask(struct ipath_devdata *dd)
{
	static u32 fixed;
	u32 ctrl;
	unsigned long errormask;
	unsigned long hwerrs;

	if (!dd->ipath_errormask || !(dd->ipath_flags & IPATH_INITTED))
		return;

	errormask = ipath_read_kreg64(dd, dd->ipath_kregs->kr_errormask);

	if (errormask == dd->ipath_errormask)
		return;
	fixed++;

	hwerrs = ipath_read_kreg64(dd, dd->ipath_kregs->kr_hwerrstatus);
	ctrl = ipath_read_kreg32(dd, dd->ipath_kregs->kr_control);

	ipath_write_kreg(dd, dd->ipath_kregs->kr_errormask,
		dd->ipath_errormask);

	if ((hwerrs & dd->ipath_hwerrmask) ||
		(ctrl & INFINIPATH_C_FREEZEMODE)) {
		/* force re-interrupt of pending events, just in case */
		ipath_write_kreg(dd, dd->ipath_kregs->kr_hwerrclear, 0ULL);
		ipath_write_kreg(dd, dd->ipath_kregs->kr_errorclear, 0ULL);
		ipath_write_kreg(dd, dd->ipath_kregs->kr_intclear, 0ULL);
		dev_info(&dd->pcidev->dev,
			"errormask fixed(%u) %lx -> %lx, ctrl %x hwerr %lx\n",
			fixed, errormask, (unsigned long)dd->ipath_errormask,
			ctrl, hwerrs);
	} else
		ipath_dbg("errormask fixed(%u) %lx -> %lx, no freeze\n",
			fixed, errormask,
			(unsigned long)dd->ipath_errormask);
}