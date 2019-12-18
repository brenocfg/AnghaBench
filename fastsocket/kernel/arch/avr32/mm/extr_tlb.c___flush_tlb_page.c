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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRP ; 
 int /*<<< orphan*/  MMUCR ; 
 int /*<<< orphan*/  MMUCR_N ; 
 unsigned int SYSREG_BFEXT (int /*<<< orphan*/ ,int) ; 
 int SYSREG_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLBARLO ; 
 int /*<<< orphan*/  TLBEHI ; 
 int /*<<< orphan*/  __builtin_tlbs () ; 
 int /*<<< orphan*/  __builtin_tlbw () ; 
 int sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __flush_tlb_page(unsigned long asid, unsigned long page)
{
	u32 mmucr, tlbehi;

	/*
	 * Caller is responsible for masking out non-PFN bits in page
	 * and changing the current ASID if necessary. This means that
	 * we don't need to flush the pipeline after writing TLBEHI.
	 */
	tlbehi = page | asid;
	sysreg_write(TLBEHI, tlbehi);

	__builtin_tlbs();
	mmucr = sysreg_read(MMUCR);

	if (!(mmucr & SYSREG_BIT(MMUCR_N))) {
		unsigned int entry;
		u32 tlbarlo;

		/* Clear the "valid" bit */
		sysreg_write(TLBEHI, tlbehi);

		/* mark the entry as "not accessed" */
		entry = SYSREG_BFEXT(DRP, mmucr);
		tlbarlo = sysreg_read(TLBARLO);
		tlbarlo |= (0x80000000UL >> entry);
		sysreg_write(TLBARLO, tlbarlo);

		/* update the entry with valid bit clear */
		__builtin_tlbw();
	}
}