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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 unsigned int FAULT_FLAG_WRITE ; 
 int VM_FAULT_HWPOISON_LARGE ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SET_HINDEX (struct hstate*) ; 
 int VM_MAYSHARE ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 int hstates ; 
 int /*<<< orphan*/  huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/ * huge_pte_alloc (struct mm_struct*,unsigned long,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 scalar_t__ huge_ptep_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int hugetlb_cow (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page*) ; 
 int hugetlb_no_page (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* hugetlbfs_pagecache_page (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 int is_hugetlb_entry_hwpoisoned (int /*<<< orphan*/ ) ; 
 int is_hugetlb_entry_migration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ vma_needs_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 

int hugetlb_fault(struct mm_struct *mm, struct vm_area_struct *vma,
			unsigned long address, unsigned int flags)
{
	pte_t *ptep;
	pte_t entry;
	int ret;
	struct page *page = NULL;
	struct page *pagecache_page = NULL;
	static DEFINE_MUTEX(hugetlb_instantiation_mutex);
	struct hstate *h = hstate_vma(vma);
	bool shared = false;

	ptep = huge_pte_offset(mm, address);
	if (ptep) {
		entry = huge_ptep_get(ptep);
		if (unlikely(is_hugetlb_entry_migration(entry))) {
			migration_entry_wait(mm, (pmd_t *)ptep, address);
			return 0;
		} else if (unlikely(is_hugetlb_entry_hwpoisoned(entry)))
			return VM_FAULT_HWPOISON_LARGE | 
			       VM_FAULT_SET_HINDEX(h - hstates);
	}

	ptep = huge_pte_alloc(mm, address, huge_page_size(h), &shared);
	if (!ptep)
		return VM_FAULT_OOM;

	/* If the pagetable is shared, no other work is necessary */
	if (shared)
		return 0;

	/*
	 * Serialize hugepage allocation and instantiation, so that we don't
	 * get spurious allocation failures if two CPUs race to instantiate
	 * the same page in the page cache.
	 */
	mutex_lock(&hugetlb_instantiation_mutex);
	entry = huge_ptep_get(ptep);
	if (huge_pte_none(entry)) {
		ret = hugetlb_no_page(mm, vma, address, ptep, flags);
		goto out_mutex;
	}

	ret = 0;

	/*
	 * If we are going to COW the mapping later, we examine the pending
	 * reservations for this page now. This will ensure that any
	 * allocations necessary to record that reservation occur outside the
	 * spinlock. For private mappings, we also lookup the pagecache
	 * page now as it is used to determine if a reservation has been
	 * consumed.
	 */
	if ((flags & FAULT_FLAG_WRITE) && !pte_write(entry)) {
		if (vma_needs_reservation(h, vma, address) < 0) {
			ret = VM_FAULT_OOM;
			goto out_mutex;
		}

		if (!(vma->vm_flags & VM_MAYSHARE))
			pagecache_page = hugetlbfs_pagecache_page(h,
								vma, address);
	}

	/*
	 * hugetlb_cow() requires page locks of pte_page(entry) and
	 * pagecache_page, so here we need take the former one
	 * when page != pagecache_page or !pagecache_page.
	 * Note that locking order is always pagecache_page -> page,
	 * so no worry about deadlock.
	 */
	page = pte_page(entry);
	if (page != pagecache_page)
		lock_page(page);

	spin_lock(&mm->page_table_lock);
	/* Check for a racing update before calling hugetlb_cow */
	if (unlikely(!pte_same(entry, huge_ptep_get(ptep))))
		goto out_page_table_lock;


	if (flags & FAULT_FLAG_WRITE) {
		if (!pte_write(entry)) {
			ret = hugetlb_cow(mm, vma, address, ptep, entry,
							pagecache_page);
			goto out_page_table_lock;
		}
		entry = pte_mkdirty(entry);
	}
	entry = pte_mkyoung(entry);
	if (huge_ptep_set_access_flags(vma, address, ptep, entry,
						flags & FAULT_FLAG_WRITE))
		update_mmu_cache(vma, address, entry);

out_page_table_lock:
	spin_unlock(&mm->page_table_lock);

	if (pagecache_page) {
		unlock_page(pagecache_page);
		put_page(pagecache_page);
	}
	if (page != pagecache_page)
		unlock_page(page);

out_mutex:
	mutex_unlock(&hugetlb_instantiation_mutex);

	return ret;
}