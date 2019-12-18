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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_SIZE ; 
 unsigned long LATENCY_LIMIT ; 
 unsigned long PMD_MASK ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (scalar_t__) ; 
 scalar_t__ __pte_alloc (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * alloc_new_pmd (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * get_old_pmd (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int move_huge_pmd (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_ptes (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_huge_page_pmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned long move_page_tables(struct vm_area_struct *vma,
		unsigned long old_addr, struct vm_area_struct *new_vma,
		unsigned long new_addr, unsigned long len)
{
	unsigned long extent, next, old_end;
	pmd_t *old_pmd, *new_pmd;
	bool need_flush = false;

	old_end = old_addr + len;
	flush_cache_range(vma, old_addr, old_end);

	mmu_notifier_invalidate_range_start(vma->vm_mm, old_addr, old_end);

	for (; old_addr < old_end; old_addr += extent, new_addr += extent) {
		cond_resched();
		next = (old_addr + PMD_SIZE) & PMD_MASK;
		if (next - 1 > old_end)
			next = old_end;
		extent = next - old_addr;
		old_pmd = get_old_pmd(vma->vm_mm, old_addr);
		if (!old_pmd)
			continue;
		new_pmd = alloc_new_pmd(vma->vm_mm, vma, new_addr);
		if (!new_pmd)
			break;
		if (pmd_trans_huge(*old_pmd)) {
			int err = 0;
			if (extent == HPAGE_PMD_SIZE)
				err = move_huge_pmd(vma, old_addr,
						    new_addr, old_end,
						    old_pmd, new_pmd);
			if (err > 0) {
				need_flush = true;
				continue;
			} else if (!err)
				split_huge_page_pmd(vma->vm_mm, old_pmd);
			VM_BUG_ON(pmd_trans_huge(*old_pmd));
		}
		if (pmd_none(*new_pmd) && __pte_alloc(new_vma->vm_mm, new_vma,
						      new_pmd,
						      new_addr))
			break;
		next = (new_addr + PMD_SIZE) & PMD_MASK;
		if (extent > next - new_addr)
			extent = next - new_addr;
		if (extent > LATENCY_LIMIT)
			extent = LATENCY_LIMIT;
		move_ptes(vma, old_pmd, old_addr, old_addr + extent,
				new_vma, new_pmd, new_addr);
		need_flush = true;
	}
	if (likely(need_flush))
		flush_tlb_range(vma, old_end-len, old_addr);

	mmu_notifier_invalidate_range_end(vma->vm_mm, old_end-len, old_end);

	return len + old_addr - old_end;	/* how much done */
}