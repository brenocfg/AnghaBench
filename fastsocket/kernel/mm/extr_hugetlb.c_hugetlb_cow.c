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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageAnon (struct page*) ; 
 int VM_FAULT_OOM ; 
 int VM_MAYSHARE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_huge_page (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  anon_vma_prepare (struct vm_area_struct*) ; 
 int /*<<< orphan*/  copy_user_huge_page (struct page*,struct page*,unsigned long,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 unsigned long huge_page_mask (struct hstate*) ; 
 scalar_t__ huge_page_size (struct hstate*) ; 
 int huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  huge_ptep_clear_flush (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hugepage_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_huge_pte (struct vm_area_struct*,struct page*,int) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int page_count (struct page*) ; 
 int page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_move_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_ptep_writable (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ unmap_ref_private (struct mm_struct*,struct vm_area_struct*,struct page*,unsigned long) ; 

__attribute__((used)) static int hugetlb_cow(struct mm_struct *mm, struct vm_area_struct *vma,
			unsigned long address, pte_t *ptep, pte_t pte,
			struct page *pagecache_page)
{
	struct hstate *h = hstate_vma(vma);
	struct page *old_page, *new_page;
	int avoidcopy;
	int outside_reserve = 0;

	old_page = pte_page(pte);

retry_avoidcopy:
	/* If no-one else is actually using this page, avoid the copy
	 * and just make the page writable */
	avoidcopy = (page_mapcount(old_page) == 1);
	if (avoidcopy) {
		if (PageAnon(old_page))
			page_move_anon_rmap(old_page, vma, address);
		set_huge_ptep_writable(vma, address, ptep);
		return 0;
	}

	/*
	 * If the process that created a MAP_PRIVATE mapping is about to
	 * perform a COW due to a shared page count, attempt to satisfy
	 * the allocation without using the existing reserves. The pagecache
	 * page is used to determine if the reserve at this address was
	 * consumed or not. If reserves were used, a partial faulted mapping
	 * at the time of fork() could consume its reserves on COW instead
	 * of the full address range.
	 */
	if (!(vma->vm_flags & VM_MAYSHARE) &&
			is_vma_resv_set(vma, HPAGE_RESV_OWNER) &&
			old_page != pagecache_page)
		outside_reserve = 1;

	page_cache_get(old_page);

	/* Drop page_table_lock as buddy allocator may be called */
	spin_unlock(&mm->page_table_lock);
	new_page = alloc_huge_page(vma, address, outside_reserve);

	if (IS_ERR(new_page)) {
		page_cache_release(old_page);

		/*
		 * If a process owning a MAP_PRIVATE mapping fails to COW,
		 * it is due to references held by a child and an insufficient
		 * huge page pool. To guarantee the original mappers
		 * reliability, unmap the page from child processes. The child
		 * may get SIGKILLed if it later faults.
		 */
		if (outside_reserve) {
			BUG_ON(huge_pte_none(pte));
			if (unmap_ref_private(mm, vma, old_page, address)) {
				BUG_ON(page_count(old_page) != 1);
				BUG_ON(huge_pte_none(pte));
				spin_lock(&mm->page_table_lock);
				goto retry_avoidcopy;
			}
			WARN_ON_ONCE(1);
		}

		/* Caller expects lock to be held */
		spin_lock(&mm->page_table_lock);
		return -PTR_ERR(new_page);
	}

	/*
	 * When the original hugepage is shared one, it does not have
	 * anon_vma prepared.
	 */
	if (unlikely(anon_vma_prepare(vma))) {
		/* Caller expects lock to be held */
		spin_lock(&mm->page_table_lock);
		return VM_FAULT_OOM;
	}

	copy_user_huge_page(new_page, old_page, address, vma,
			    pages_per_huge_page(h));
	__SetPageUptodate(new_page);

	/*
	 * Retake the page_table_lock to check for racing updates
	 * before the page tables are altered
	 */
	spin_lock(&mm->page_table_lock);
	ptep = huge_pte_offset(mm, address & huge_page_mask(h));
	if (likely(pte_same(huge_ptep_get(ptep), pte))) {
		/* Break COW */
		mmu_notifier_invalidate_range_start(mm,
			address & huge_page_mask(h),
			(address & huge_page_mask(h)) + huge_page_size(h));
		huge_ptep_clear_flush(vma, address, ptep);
		set_huge_pte_at(mm, address, ptep,
				make_huge_pte(vma, new_page, 1));
		page_remove_rmap(old_page);
		hugepage_add_new_anon_rmap(new_page, vma, address);
		/* Make the old page be freed below */
		new_page = old_page;
		mmu_notifier_invalidate_range_end(mm,
			address & huge_page_mask(h),
			(address & huge_page_mask(h)) + huge_page_size(h));
	}
	page_cache_release(new_page);
	page_cache_release(old_page);
	return 0;
}