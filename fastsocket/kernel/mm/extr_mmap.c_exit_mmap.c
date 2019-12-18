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
struct vm_area_struct {int vm_flags; struct vm_area_struct* vm_next; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int nr_ptes; struct vm_area_struct* mmap; scalar_t__ locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FIRST_USER_ADDRESS ; 
 int PMD_SHIFT ; 
 int PMD_SIZE ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  arch_exit_mmap (struct mm_struct*) ; 
 int /*<<< orphan*/  arch_flush_exec_range (struct mm_struct*) ; 
 int /*<<< orphan*/  flush_cache_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  free_pgtables (struct mmu_gather*,struct vm_area_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mmu_notifier_release (struct mm_struct*) ; 
 int /*<<< orphan*/  munlock_vma_pages_all (struct vm_area_struct*) ; 
 struct vm_area_struct* remove_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long unmap_vmas (struct mmu_gather**,struct vm_area_struct*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 

void exit_mmap(struct mm_struct *mm)
{
	struct mmu_gather *tlb;
	struct vm_area_struct *vma;
	unsigned long nr_accounted = 0;
	unsigned long end;

	/* mm's last user has gone, and its about to be pulled down */
	mmu_notifier_release(mm);

	if (mm->locked_vm) {
		vma = mm->mmap;
		while (vma) {
			if (vma->vm_flags & VM_LOCKED)
				munlock_vma_pages_all(vma);
			vma = vma->vm_next;
		}
	}

	arch_exit_mmap(mm);

	vma = mm->mmap;
	if (!vma)	/* Can happen if dup_mmap() received an OOM */
		return;

	lru_add_drain();
	flush_cache_mm(mm);
	/* update_hiwater_rss(mm) here? but nobody should be looking */
	/* Use -1 here to ensure all VMAs in the mm are unmapped */
	end = unmap_vmas(&tlb, vma, 0, -1, &nr_accounted, NULL, 1);
	vm_unacct_memory(nr_accounted);

	free_pgtables(tlb, vma, FIRST_USER_ADDRESS, 0);
	tlb_finish_mmu(tlb, 0, end);
	arch_flush_exec_range(mm);

	/*
	 * Walk the list again, actually closing and freeing it,
	 * with preemption enabled, without holding any MM locks.
	 */
	while (vma)
		vma = remove_vma(vma);

	BUG_ON(mm->nr_ptes > (FIRST_USER_ADDRESS+PMD_SIZE-1)>>PMD_SHIFT);
}