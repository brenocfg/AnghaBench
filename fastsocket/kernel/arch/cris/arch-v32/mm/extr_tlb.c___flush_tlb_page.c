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
struct vm_area_struct {TYPE_2__* vm_mm; } ;
struct TYPE_3__ {unsigned long page_id; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PAGEID ; 
 unsigned long NO_CONTEXT ; 
 int NUM_TLB_ENTRIES ; 
 unsigned long PAGE_MASK ; 
 unsigned long REG_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_MM_TLB_HI ; 
 int /*<<< orphan*/  SUPP_BANK_SEL (int) ; 
 int /*<<< orphan*/  SUPP_REG_RD (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  UPDATE_TLB_HILO (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_TLB_SEL_IDX (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pid ; 
 int /*<<< orphan*/  rw_mm_tlb_hi ; 

void
__flush_tlb_page(struct vm_area_struct *vma, unsigned long addr)
{
	int i;
	int mmu;
	unsigned long page_id;
	unsigned long flags;
	unsigned long tlb_hi;
	unsigned long mmu_tlb_hi;

	page_id = vma->vm_mm->context.page_id;

	if (page_id == NO_CONTEXT)
		return;

	addr &= PAGE_MASK;

	/*
	 * Invalidate those TLB entries that match both the mm context and the
	 * requested virtual address.
	 */
	local_irq_save(flags);

	for (mmu = 1; mmu <= 2; mmu++) {
		SUPP_BANK_SEL(mmu);
		for (i = 0; i < NUM_TLB_ENTRIES; i++) {
			UPDATE_TLB_SEL_IDX(i);
			SUPP_REG_RD(RW_MM_TLB_HI, tlb_hi);

			/* Check if page_id and address matches */
			if (((tlb_hi & 0xff) == page_id) &&
			    ((tlb_hi & PAGE_MASK) == addr)) {
				mmu_tlb_hi = REG_FIELD(mmu, rw_mm_tlb_hi, pid,
				                       INVALID_PAGEID) | addr;

				UPDATE_TLB_HILO(mmu_tlb_hi, 0);
			}
		}
	}

	local_irq_restore(flags);
}