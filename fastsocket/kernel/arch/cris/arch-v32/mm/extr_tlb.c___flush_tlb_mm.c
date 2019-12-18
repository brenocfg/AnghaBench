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
struct TYPE_2__ {unsigned long page_id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int INVALID_PAGEID ; 
 unsigned long NO_CONTEXT ; 
 int NUM_TLB_ENTRIES ; 
 unsigned long REG_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RW_MM_TLB_HI ; 
 int /*<<< orphan*/  SUPP_BANK_SEL (int) ; 
 int /*<<< orphan*/  SUPP_REG_RD (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  UPDATE_TLB_HILO (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_TLB_SEL_IDX (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pid ; 
 int /*<<< orphan*/  rw_mm_tlb_hi ; 
 int /*<<< orphan*/  vpn ; 

void
__flush_tlb_mm(struct mm_struct *mm)
{
	int i;
	int mmu;
	unsigned long flags;
	unsigned long page_id;
	unsigned long tlb_hi;
	unsigned long mmu_tlb_hi;

	page_id = mm->context.page_id;

	if (page_id == NO_CONTEXT)
		return;

	/* Mark the TLB entries that match the page_id as invalid. */
	local_irq_save(flags);

	for (mmu = 1; mmu <= 2; mmu++) {
		SUPP_BANK_SEL(mmu);
		for (i = 0; i < NUM_TLB_ENTRIES; i++) {
			UPDATE_TLB_SEL_IDX(i);

			/* Get the page_id */
			SUPP_REG_RD(RW_MM_TLB_HI, tlb_hi);

			/* Check if the page_id match. */
			if ((tlb_hi & 0xff) == page_id) {
				mmu_tlb_hi = (REG_FIELD(mmu, rw_mm_tlb_hi, pid,
				                        INVALID_PAGEID)
				            | REG_FIELD(mmu, rw_mm_tlb_hi, vpn,
				                        i & 0xf));

				UPDATE_TLB_HILO(mmu_tlb_hi, 0);
			}
		}
	}

	local_irq_restore(flags);
}