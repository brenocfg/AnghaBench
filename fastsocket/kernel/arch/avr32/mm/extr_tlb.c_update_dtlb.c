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
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASID ; 
 int /*<<< orphan*/  DRP ; 
 int /*<<< orphan*/  MMUCR ; 
 int /*<<< orphan*/  MMUCR_N ; 
 unsigned long MMU_VPN_MASK ; 
 unsigned long SYSREG_BF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSREG_BFEXT (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long SYSREG_BFINS (int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 unsigned long SYSREG_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLBARLO ; 
 int /*<<< orphan*/  TLBEHI ; 
 int /*<<< orphan*/  TLBEHI_V ; 
 int /*<<< orphan*/  TLBELO ; 
 unsigned long _PAGE_FLAGS_HARDWARE_MASK ; 
 int /*<<< orphan*/  __builtin_tlbs () ; 
 int /*<<< orphan*/  __builtin_tlbw () ; 
 int fls (unsigned long) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 unsigned long sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void update_dtlb(unsigned long address, pte_t pte)
{
	u32 tlbehi;
	u32 mmucr;

	/*
	 * We're not changing the ASID here, so no need to flush the
	 * pipeline.
	 */
	tlbehi = sysreg_read(TLBEHI);
	tlbehi = SYSREG_BF(ASID, SYSREG_BFEXT(ASID, tlbehi));
	tlbehi |= address & MMU_VPN_MASK;
	tlbehi |= SYSREG_BIT(TLBEHI_V);
	sysreg_write(TLBEHI, tlbehi);

	/* Does this mapping already exist? */
	__builtin_tlbs();
	mmucr = sysreg_read(MMUCR);

	if (mmucr & SYSREG_BIT(MMUCR_N)) {
		/* Not found -- pick a not-recently-accessed entry */
		unsigned int rp;
		u32 tlbar = sysreg_read(TLBARLO);

		rp = 32 - fls(tlbar);
		if (rp == 32) {
			rp = 0;
			sysreg_write(TLBARLO, -1L);
		}

		mmucr = SYSREG_BFINS(DRP, rp, mmucr);
		sysreg_write(MMUCR, mmucr);
	}

	sysreg_write(TLBELO, pte_val(pte) & _PAGE_FLAGS_HARDWARE_MASK);

	/* Let's go */
	__builtin_tlbw();
}