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
struct ipath_devdata {int ipath_flags; int ipath_boardrev; int ipath_hwerrmask; TYPE_1__* ipath_kregs; } ;
typedef  int ipath_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  kr_extstatus; } ;

/* Variables and functions */
 int INFINIPATH_EXTS_MEMBIST_CORRECT ; 
 int INFINIPATH_EXTS_MEMBIST_ENDTEST ; 
 int INFINIPATH_HWE_HTCMISCERR4 ; 
 int INFINIPATH_HWE_RXDSYNCMEMPARITYERR ; 
 int INFINIPATH_HWE_SERDESPLLFAILED ; 
 int IPATH_8BIT_IN_HT0 ; 
 int IPATH_8BIT_IN_HT1 ; 
 int infinipath_hwe_htclnkabyte1crcerr ; 
 int infinipath_hwe_htclnkbbyte1crcerr ; 
 int /*<<< orphan*/  ipath_check_htlink (struct ipath_devdata*) ; 
 int /*<<< orphan*/  ipath_dbg (char*) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 int ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipath_ht_init_hwerrors(struct ipath_devdata *dd)
{
	ipath_err_t val;
	u64 extsval;

	extsval = ipath_read_kreg64(dd, dd->ipath_kregs->kr_extstatus);

	if (!(extsval & INFINIPATH_EXTS_MEMBIST_ENDTEST))
		ipath_dev_err(dd, "MemBIST did not complete!\n");
	if (extsval & INFINIPATH_EXTS_MEMBIST_CORRECT)
		ipath_dbg("MemBIST corrected\n");

	ipath_check_htlink(dd);

	/* barring bugs, all hwerrors become interrupts, which can */
	val = -1LL;
	/* don't look at crc lane1 if 8 bit */
	if (dd->ipath_flags & IPATH_8BIT_IN_HT0)
		val &= ~infinipath_hwe_htclnkabyte1crcerr;
	/* don't look at crc lane1 if 8 bit */
	if (dd->ipath_flags & IPATH_8BIT_IN_HT1)
		val &= ~infinipath_hwe_htclnkbbyte1crcerr;

	/*
	 * disable RXDSYNCMEMPARITY because external serdes is unused,
	 * and therefore the logic will never be used or initialized,
	 * and uninitialized state will normally result in this error
	 * being asserted.  Similarly for the external serdess pll
	 * lock signal.
	 */
	val &= ~(INFINIPATH_HWE_SERDESPLLFAILED |
		 INFINIPATH_HWE_RXDSYNCMEMPARITYERR);

	/*
	 * Disable MISCERR4 because of an inversion in the HT core
	 * logic checking for errors that cause this bit to be set.
	 * The errata can also cause the protocol error bit to be set
	 * in the HT config space linkerror register(s).
	 */
	val &= ~INFINIPATH_HWE_HTCMISCERR4;

	/*
	 * PLL ignored because unused MDIO interface has a logic problem
	 */
	if (dd->ipath_boardrev == 4 || dd->ipath_boardrev == 9)
		val &= ~INFINIPATH_HWE_SERDESPLLFAILED;
	dd->ipath_hwerrmask = val;
}