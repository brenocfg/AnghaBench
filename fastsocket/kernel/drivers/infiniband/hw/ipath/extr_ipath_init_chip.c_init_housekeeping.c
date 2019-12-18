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
typedef  void* u8 ;
struct ipath_devdata {int ipath_flags; int ipath_revision; int ipath_sregbase; int ipath_cregbase; int ipath_uregbase; int ipath_pcirev; int ipath_majrev; int ipath_minrev; int (* ipath_f_get_boardname ) (struct ipath_devdata*,char*,int) ;int /*<<< orphan*/  ipath_boardversion; void* ipath_boardrev; TYPE_1__* ipath_kregs; int /*<<< orphan*/  ipath_kregbase; scalar_t__ ipath_rcvhdrsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_errorclear; int /*<<< orphan*/  kr_hwdiagctrl; int /*<<< orphan*/  kr_userregbase; int /*<<< orphan*/  kr_counterregbase; int /*<<< orphan*/  kr_sendregbase; int /*<<< orphan*/  kr_revision; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  INFINIPATH_E_RESET ; 
 unsigned int INFINIPATH_R_ARCH_MASK ; 
 int INFINIPATH_R_ARCH_SHIFT ; 
 int INFINIPATH_R_BOARDID_MASK ; 
 int INFINIPATH_R_BOARDID_SHIFT ; 
 int INFINIPATH_R_CHIPREVMAJOR_MASK ; 
 int INFINIPATH_R_CHIPREVMAJOR_SHIFT ; 
 int INFINIPATH_R_CHIPREVMINOR_MASK ; 
 int INFINIPATH_R_CHIPREVMINOR_SHIFT ; 
 int INFINIPATH_R_SOFTWARE_MASK ; 
 int INFINIPATH_R_SOFTWARE_SHIFT ; 
 int IPATH_CHIP_SWVERSION ; 
 int IPATH_CHIP_VERS_MAJ ; 
 int IPATH_CHIP_VERS_MIN ; 
 int IPATH_LINKACTIVE ; 
 int IPATH_LINKARMED ; 
 int IPATH_LINKDOWN ; 
 int IPATH_LINKINIT ; 
 int IPATH_LINKUNK ; 
 int IPATH_PRESENT ; 
 int /*<<< orphan*/  VERBOSE ; 
 int init_chip_first (struct ipath_devdata*) ; 
 int init_chip_reset (struct ipath_devdata*) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ipath_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,...) ; 
 void* ipath_read_kreg32 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,char*,unsigned int,int,int,int,unsigned int) ; 
 int stub1 (struct ipath_devdata*,char*,int) ; 

__attribute__((used)) static int init_housekeeping(struct ipath_devdata *dd, int reinit)
{
	char boardn[40];
	int ret = 0;

	/*
	 * have to clear shadow copies of registers at init that are
	 * not otherwise set here, or all kinds of bizarre things
	 * happen with driver on chip reset
	 */
	dd->ipath_rcvhdrsize = 0;

	/*
	 * Don't clear ipath_flags as 8bit mode was set before
	 * entering this func. However, we do set the linkstate to
	 * unknown, so we can watch for a transition.
	 * PRESENT is set because we want register reads to work,
	 * and the kernel infrastructure saw it in config space;
	 * We clear it if we have failures.
	 */
	dd->ipath_flags |= IPATH_LINKUNK | IPATH_PRESENT;
	dd->ipath_flags &= ~(IPATH_LINKACTIVE | IPATH_LINKARMED |
			     IPATH_LINKDOWN | IPATH_LINKINIT);

	ipath_cdbg(VERBOSE, "Try to read spc chip revision\n");
	dd->ipath_revision =
		ipath_read_kreg64(dd, dd->ipath_kregs->kr_revision);

	/*
	 * set up fundamental info we need to use the chip; we assume
	 * if the revision reg and these regs are OK, we don't need to
	 * special case the rest
	 */
	dd->ipath_sregbase =
		ipath_read_kreg32(dd, dd->ipath_kregs->kr_sendregbase);
	dd->ipath_cregbase =
		ipath_read_kreg32(dd, dd->ipath_kregs->kr_counterregbase);
	dd->ipath_uregbase =
		ipath_read_kreg32(dd, dd->ipath_kregs->kr_userregbase);
	ipath_cdbg(VERBOSE, "ipath_kregbase %p, sendbase %x usrbase %x, "
		   "cntrbase %x\n", dd->ipath_kregbase, dd->ipath_sregbase,
		   dd->ipath_uregbase, dd->ipath_cregbase);
	if ((dd->ipath_revision & 0xffffffff) == 0xffffffff
	    || (dd->ipath_sregbase & 0xffffffff) == 0xffffffff
	    || (dd->ipath_cregbase & 0xffffffff) == 0xffffffff
	    || (dd->ipath_uregbase & 0xffffffff) == 0xffffffff) {
		ipath_dev_err(dd, "Register read failures from chip, "
			      "giving up initialization\n");
		dd->ipath_flags &= ~IPATH_PRESENT;
		ret = -ENODEV;
		goto done;
	}


	/* clear diagctrl register, in case diags were running and crashed */
	ipath_write_kreg (dd, dd->ipath_kregs->kr_hwdiagctrl, 0);

	/* clear the initial reset flag, in case first driver load */
	ipath_write_kreg(dd, dd->ipath_kregs->kr_errorclear,
			 INFINIPATH_E_RESET);

	ipath_cdbg(VERBOSE, "Revision %llx (PCI %x)\n",
		   (unsigned long long) dd->ipath_revision,
		   dd->ipath_pcirev);

	if (((dd->ipath_revision >> INFINIPATH_R_SOFTWARE_SHIFT) &
	     INFINIPATH_R_SOFTWARE_MASK) != IPATH_CHIP_SWVERSION) {
		ipath_dev_err(dd, "Driver only handles version %d, "
			      "chip swversion is %d (%llx), failng\n",
			      IPATH_CHIP_SWVERSION,
			      (int)(dd->ipath_revision >>
				    INFINIPATH_R_SOFTWARE_SHIFT) &
			      INFINIPATH_R_SOFTWARE_MASK,
			      (unsigned long long) dd->ipath_revision);
		ret = -ENOSYS;
		goto done;
	}
	dd->ipath_majrev = (u8) ((dd->ipath_revision >>
				  INFINIPATH_R_CHIPREVMAJOR_SHIFT) &
				 INFINIPATH_R_CHIPREVMAJOR_MASK);
	dd->ipath_minrev = (u8) ((dd->ipath_revision >>
				  INFINIPATH_R_CHIPREVMINOR_SHIFT) &
				 INFINIPATH_R_CHIPREVMINOR_MASK);
	dd->ipath_boardrev = (u8) ((dd->ipath_revision >>
				    INFINIPATH_R_BOARDID_SHIFT) &
				   INFINIPATH_R_BOARDID_MASK);

	ret = dd->ipath_f_get_boardname(dd, boardn, sizeof boardn);

	snprintf(dd->ipath_boardversion, sizeof(dd->ipath_boardversion),
		 "ChipABI %u.%u, %s, InfiniPath%u %u.%u, PCI %u, "
		 "SW Compat %u\n",
		 IPATH_CHIP_VERS_MAJ, IPATH_CHIP_VERS_MIN, boardn,
		 (unsigned)(dd->ipath_revision >> INFINIPATH_R_ARCH_SHIFT) &
		 INFINIPATH_R_ARCH_MASK,
		 dd->ipath_majrev, dd->ipath_minrev, dd->ipath_pcirev,
		 (unsigned)(dd->ipath_revision >>
			    INFINIPATH_R_SOFTWARE_SHIFT) &
		 INFINIPATH_R_SOFTWARE_MASK);

	ipath_dbg("%s", dd->ipath_boardversion);

	if (ret)
		goto done;

	if (reinit)
		ret = init_chip_reset(dd);
	else
		ret = init_chip_first(dd);

done:
	return ret;
}