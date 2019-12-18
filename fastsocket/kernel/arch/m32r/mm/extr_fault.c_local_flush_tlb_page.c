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
struct vm_area_struct {scalar_t__ vm_mm; } ;

/* Variables and functions */
 unsigned long MMU_CONTEXT_ASID_MASK ; 
 unsigned long NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  __flush_tlb_page (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long mm_context (scalar_t__) ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	if (vma->vm_mm && mm_context(vma->vm_mm) != NO_CONTEXT) {
		unsigned long flags;

		local_irq_save(flags);
		page &= PAGE_MASK;
		page |= (mm_context(vma->vm_mm) & MMU_CONTEXT_ASID_MASK);
		__flush_tlb_page(page);
		local_irq_restore(flags);
	}
}