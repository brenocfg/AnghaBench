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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SIGBUS ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_zeroed_user_highpage_movable (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  anon_vma_prepare (struct vm_area_struct*) ; 
 scalar_t__ check_stack_guard_page (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  inc_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ mem_cgroup_newpage_charge (struct page*,struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_page (struct page*) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_zero_pfn (unsigned long) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkspecial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mm_anon_fault (struct mm_struct*,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_anonymous_page(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, pte_t *page_table, pmd_t *pmd,
		unsigned int flags)
{
	struct page *page;
	spinlock_t *ptl;
	pte_t entry;

	pte_unmap(page_table);

	/* Check if we need to add a guard page to the stack */
	if (check_stack_guard_page(vma, address) < 0)
		return VM_FAULT_SIGBUS;

	/* Use the zero-page for reads */
	if (!(flags & FAULT_FLAG_WRITE)) {
		entry = pte_mkspecial(pfn_pte(my_zero_pfn(address),
						vma->vm_page_prot));
		page_table = pte_offset_map_lock(mm, pmd, address, &ptl);
		if (!pte_none(*page_table))
			goto unlock;
		goto setpte;
	}

	/* Allocate our own private page. */
	if (unlikely(anon_vma_prepare(vma)))
		goto oom;
	page = alloc_zeroed_user_highpage_movable(vma, address);
	if (!page)
		goto oom;
	__SetPageUptodate(page);

	trace_mm_anon_fault(mm, address);
	if (mem_cgroup_newpage_charge(page, mm, GFP_KERNEL))
		goto oom_free_page;

	entry = mk_pte(page, vma->vm_page_prot);
	if (vma->vm_flags & VM_WRITE)
		entry = pte_mkwrite(pte_mkdirty(entry));

	page_table = pte_offset_map_lock(mm, pmd, address, &ptl);
	if (!pte_none(*page_table))
		goto release;

	inc_mm_counter(mm, anon_rss);
	page_add_new_anon_rmap(page, vma, address);
setpte:
	set_pte_at(mm, address, page_table, entry);

	/* No need to invalidate - it was non-present before */
	update_mmu_cache(vma, address, entry);
unlock:
	pte_unmap_unlock(page_table, ptl);
	return 0;
release:
	mem_cgroup_uncharge_page(page);
	page_cache_release(page);
	goto unlock;
oom_free_page:
	page_cache_release(page);
oom:
	return VM_FAULT_OOM;
}