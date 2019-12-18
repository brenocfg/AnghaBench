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
struct ipath_devdata {TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_senddmahead; int /*<<< orphan*/  kr_senddmatail; int /*<<< orphan*/  kr_senddmabufmask2; int /*<<< orphan*/  kr_senddmabufmask1; int /*<<< orphan*/  kr_senddmabufmask0; int /*<<< orphan*/  kr_sendctrl; int /*<<< orphan*/  kr_senddmastatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 unsigned long ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_sdma_state(struct ipath_devdata *dd)
{
	unsigned long reg;

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmastatus);
	ipath_cdbg(VERBOSE, "kr_senddmastatus: 0x%016lx\n", reg);

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_sendctrl);
	ipath_cdbg(VERBOSE, "kr_sendctrl: 0x%016lx\n", reg);

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmabufmask0);
	ipath_cdbg(VERBOSE, "kr_senddmabufmask0: 0x%016lx\n", reg);

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmabufmask1);
	ipath_cdbg(VERBOSE, "kr_senddmabufmask1: 0x%016lx\n", reg);

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmabufmask2);
	ipath_cdbg(VERBOSE, "kr_senddmabufmask2: 0x%016lx\n", reg);

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmatail);
	ipath_cdbg(VERBOSE, "kr_senddmatail: 0x%016lx\n", reg);

	reg = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmahead);
	ipath_cdbg(VERBOSE, "kr_senddmahead: 0x%016lx\n", reg);
}