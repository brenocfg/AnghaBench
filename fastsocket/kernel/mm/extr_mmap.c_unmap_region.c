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
struct vm_area_struct {int /*<<< orphan*/  vm_start; int /*<<< orphan*/  vm_end; struct vm_area_struct* vm_next; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_USER_ADDRESS ; 
 int /*<<< orphan*/  free_pgtables (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unmap_vmas (struct mmu_gather**,struct vm_area_struct*,unsigned long,unsigned long,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_hiwater_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 

__attribute__((used)) static void unmap_region(struct mm_struct *mm,
		struct vm_area_struct *vma, struct vm_area_struct *prev,
		unsigned long start, unsigned long end)
{
	struct vm_area_struct *next = prev? prev->vm_next: mm->mmap;
	struct mmu_gather *tlb;
	unsigned long nr_accounted = 0;

	lru_add_drain();
	update_hiwater_rss(mm);
	unmap_vmas(&tlb, vma, start, end, &nr_accounted, NULL, 0);
	vm_unacct_memory(nr_accounted);
	free_pgtables(tlb, vma, prev? prev->vm_end: FIRST_USER_ADDRESS,
				 next? next->vm_start: 0);
	tlb_finish_mmu(tlb, start, end);
}