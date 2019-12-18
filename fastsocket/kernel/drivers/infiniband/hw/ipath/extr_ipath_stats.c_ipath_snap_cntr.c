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
typedef  int u32 ;
struct ipath_devdata {int ipath_flags; int ipath_lastsword; unsigned long long ipath_sword; int ipath_lastrword; unsigned long long ipath_rword; int ipath_lastspkts; unsigned long long ipath_spkts; int ipath_lastrpkts; unsigned long long ipath_rpkts; unsigned long long ibsymsnap; unsigned long long iblnkerrsnap; scalar_t__ iblnkerrdelta; scalar_t__ ibdeltainprog; TYPE_1__* ipath_cregs; scalar_t__ ibsymdelta; } ;
typedef  scalar_t__ ipath_creg ;
struct TYPE_2__ {scalar_t__ cr_wordsendcnt; scalar_t__ cr_wordrcvcnt; scalar_t__ cr_pktsendcnt; scalar_t__ cr_pktrcvcnt; scalar_t__ cr_ibsymbolerrcnt; scalar_t__ cr_iblinkerrrecovcnt; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int IPATH_32BITCOUNTERS ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,scalar_t__) ; 
 unsigned long long ipath_read_creg (struct ipath_devdata*,scalar_t__) ; 
 int ipath_read_creg32 (struct ipath_devdata*,scalar_t__) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (scalar_t__,unsigned long) ; 

u64 ipath_snap_cntr(struct ipath_devdata *dd, ipath_creg creg)
{
	u32 val, reg64 = 0;
	u64 val64;
	unsigned long t0, t1;
	u64 ret;

	t0 = jiffies;
	/* If fast increment counters are only 32 bits, snapshot them,
	 * and maintain them as 64bit values in the driver */
	if (!(dd->ipath_flags & IPATH_32BITCOUNTERS) &&
	    (creg == dd->ipath_cregs->cr_wordsendcnt ||
	     creg == dd->ipath_cregs->cr_wordrcvcnt ||
	     creg == dd->ipath_cregs->cr_pktsendcnt ||
	     creg == dd->ipath_cregs->cr_pktrcvcnt)) {
		val64 = ipath_read_creg(dd, creg);
		val = val64 == ~0ULL ? ~0U : 0;
		reg64 = 1;
	} else			/* val64 just to keep gcc quiet... */
		val64 = val = ipath_read_creg32(dd, creg);
	/*
	 * See if a second has passed.  This is just a way to detect things
	 * that are quite broken.  Normally this should take just a few
	 * cycles (the check is for long enough that we don't care if we get
	 * pre-empted.)  An Opteron HT O read timeout is 4 seconds with
	 * normal NB values
	 */
	t1 = jiffies;
	if (time_before(t0 + HZ, t1) && val == -1) {
		ipath_dev_err(dd, "Error!  Read counter 0x%x timed out\n",
			      creg);
		ret = 0ULL;
		goto bail;
	}
	if (reg64) {
		ret = val64;
		goto bail;
	}

	if (creg == dd->ipath_cregs->cr_wordsendcnt) {
		if (val != dd->ipath_lastsword) {
			dd->ipath_sword += val - dd->ipath_lastsword;
			dd->ipath_lastsword = val;
		}
		val64 = dd->ipath_sword;
	} else if (creg == dd->ipath_cregs->cr_wordrcvcnt) {
		if (val != dd->ipath_lastrword) {
			dd->ipath_rword += val - dd->ipath_lastrword;
			dd->ipath_lastrword = val;
		}
		val64 = dd->ipath_rword;
	} else if (creg == dd->ipath_cregs->cr_pktsendcnt) {
		if (val != dd->ipath_lastspkts) {
			dd->ipath_spkts += val - dd->ipath_lastspkts;
			dd->ipath_lastspkts = val;
		}
		val64 = dd->ipath_spkts;
	} else if (creg == dd->ipath_cregs->cr_pktrcvcnt) {
		if (val != dd->ipath_lastrpkts) {
			dd->ipath_rpkts += val - dd->ipath_lastrpkts;
			dd->ipath_lastrpkts = val;
		}
		val64 = dd->ipath_rpkts;
	} else if (creg == dd->ipath_cregs->cr_ibsymbolerrcnt) {
		if (dd->ibdeltainprog)
			val64 -= val64 - dd->ibsymsnap;
		val64 -= dd->ibsymdelta;
	} else if (creg == dd->ipath_cregs->cr_iblinkerrrecovcnt) {
		if (dd->ibdeltainprog)
			val64 -= val64 - dd->iblnkerrsnap;
		val64 -= dd->iblnkerrdelta;
	} else
		val64 = (u64) val;

	ret = val64;

bail:
	return ret;
}