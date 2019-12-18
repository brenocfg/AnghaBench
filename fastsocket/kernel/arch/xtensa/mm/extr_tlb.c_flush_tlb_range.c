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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct mm_struct {scalar_t__ context; } ;

/* Variables and functions */
 int ASID_INSERT (scalar_t__) ; 
 scalar_t__ NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int VM_EXEC ; 
 int _TLB_ENTRIES ; 
 int /*<<< orphan*/  flush_tlb_mm (struct mm_struct*) ; 
 int get_rasid_register () ; 
 int /*<<< orphan*/  invalidate_dtlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  invalidate_itlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_rasid_register (int) ; 

void flush_tlb_range (struct vm_area_struct *vma,
    		      unsigned long start, unsigned long end)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long flags;

	if (mm->context == NO_CONTEXT)
		return;

#if 0
	printk("[tlbrange<%02lx,%08lx,%08lx>]\n",
			(unsigned long)mm->context, start, end);
#endif
	local_save_flags(flags);

	if (end-start + (PAGE_SIZE-1) <= _TLB_ENTRIES << PAGE_SHIFT) {
		int oldpid = get_rasid_register();
		set_rasid_register (ASID_INSERT(mm->context));
		start &= PAGE_MASK;
 		if (vma->vm_flags & VM_EXEC)
			while(start < end) {
				invalidate_itlb_mapping(start);
				invalidate_dtlb_mapping(start);
				start += PAGE_SIZE;
			}
		else
			while(start < end) {
				invalidate_dtlb_mapping(start);
				start += PAGE_SIZE;
			}

		set_rasid_register(oldpid);
	} else {
		flush_tlb_mm(mm);
	}
	local_irq_restore(flags);
}