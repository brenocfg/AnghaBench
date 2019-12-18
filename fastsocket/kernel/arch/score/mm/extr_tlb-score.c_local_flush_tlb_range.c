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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {unsigned long context; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 unsigned long ASID_MASK ; 
 unsigned long KSEG1 ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TLBSIZE ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_new_mmu_context (struct mm_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pectx_set (int /*<<< orphan*/ ) ; 
 unsigned long pevn_get () ; 
 int /*<<< orphan*/  pevn_set (unsigned long) ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int tlbpt_get () ; 

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
	unsigned long end)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long vma_mm_context = mm->context;
	if (mm->context != 0) {
		unsigned long flags;
		int size;

		local_irq_save(flags);
		size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		if (size <= TLBSIZE) {
			int oldpid = pevn_get() & ASID_MASK;
			int newpid = vma_mm_context & ASID_MASK;

			start &= PAGE_MASK;
			end += (PAGE_SIZE - 1);
			end &= PAGE_MASK;
			while (start < end) {
				int idx;

				pevn_set(start | newpid);
				start += PAGE_SIZE;
				barrier();
				tlb_probe();
				idx = tlbpt_get();
				pectx_set(0);
				pevn_set(KSEG1);
				if (idx < 0)
					continue;
				tlb_write_indexed();
			}
			pevn_set(oldpid);
		} else {
			/* Bigger than TLBSIZE, get new ASID directly */
			get_new_mmu_context(mm);
			if (mm == current->active_mm)
				pevn_set(vma_mm_context & ASID_MASK);
		}
		local_irq_restore(flags);
	}
}