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
struct vm_area_struct {unsigned long vm_end; int vm_flags; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int VM_EXEC ; 
 unsigned long cpu_asid (int /*<<< orphan*/ ,struct mm_struct*) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long get_asid () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sh64_icache_inv_all () ; 
 int /*<<< orphan*/  sh64_icache_inv_user_page (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  switch_and_save_asid (unsigned long) ; 

__attribute__((used)) static void sh64_icache_inv_user_page_range(struct mm_struct *mm,
			  unsigned long start, unsigned long end)
{
	/* Used for invalidating big chunks of I-cache, i.e. assume the range
	   is whole pages.  If 'start' or 'end' is not page aligned, the code
	   is conservative and invalidates to the ends of the enclosing pages.
	   This is functionally OK, just a performance loss. */

	/* See the comments below in sh64_dcache_purge_user_range() regarding
	   the choice of algorithm.  However, for the I-cache option (2) isn't
	   available because there are no physical tags so aliases can't be
	   resolved.  The icbi instruction has to be used through the user
	   mapping.   Because icbi is cheaper than ocbp on a cache hit, it
	   would be cheaper to use the selective code for a large range than is
	   possible with the D-cache.  Just assume 64 for now as a working
	   figure.
	   */
	int n_pages;

	if (!mm)
		return;

	n_pages = ((end - start) >> PAGE_SHIFT);
	if (n_pages >= 64) {
		sh64_icache_inv_all();
	} else {
		unsigned long aligned_start;
		unsigned long eaddr;
		unsigned long after_last_page_start;
		unsigned long mm_asid, current_asid;
		unsigned long flags = 0;

		mm_asid = cpu_asid(smp_processor_id(), mm);
		current_asid = get_asid();

		if (mm_asid != current_asid) {
			/* Switch ASID and run the invalidate loop under cli */
			local_irq_save(flags);
			switch_and_save_asid(mm_asid);
		}

		aligned_start = start & PAGE_MASK;
		after_last_page_start = PAGE_SIZE + ((end - 1) & PAGE_MASK);

		while (aligned_start < after_last_page_start) {
			struct vm_area_struct *vma;
			unsigned long vma_end;
			vma = find_vma(mm, aligned_start);
			if (!vma || (aligned_start <= vma->vm_end)) {
				/* Avoid getting stuck in an error condition */
				aligned_start += PAGE_SIZE;
				continue;
			}
			vma_end = vma->vm_end;
			if (vma->vm_flags & VM_EXEC) {
				/* Executable */
				eaddr = aligned_start;
				while (eaddr < vma_end) {
					sh64_icache_inv_user_page(vma, eaddr);
					eaddr += PAGE_SIZE;
				}
			}
			aligned_start = vma->vm_end; /* Skip to start of next region */
		}

		if (mm_asid != current_asid) {
			switch_and_save_asid(current_asid);
			local_irq_restore(flags);
		}
	}
}