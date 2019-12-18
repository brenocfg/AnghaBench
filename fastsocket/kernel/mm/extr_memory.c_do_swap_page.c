#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAYACCT_PF_SWAPIN ; 
 unsigned int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PGMAJFAULT ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 scalar_t__ PageMlocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_HWPOISON ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_RETRY ; 
 int VM_FAULT_SIGBUS ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayacct_clear_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayacct_set_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_page_add_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int do_wp_page (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_icache_page (struct vm_area_struct*,struct page*) ; 
 int /*<<< orphan*/  grab_swap_token (struct mm_struct*) ; 
 int /*<<< orphan*/  inc_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_hwpoison_entry (TYPE_1__) ; 
 scalar_t__ is_migration_entry (TYPE_1__) ; 
 struct page* ksm_might_need_to_copy (struct page*,struct vm_area_struct*,unsigned long) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int lock_page_or_retry (struct page*,struct mm_struct*,unsigned int) ; 
 struct page* lookup_swap_cache (TYPE_1__) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge_swapin (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge_swapin (struct page*,struct mem_cgroup*) ; 
 scalar_t__ mem_cgroup_try_charge_swapin (struct mm_struct*,struct page*,int /*<<< orphan*/ ,struct mem_cgroup**) ; 
 int /*<<< orphan*/  migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int non_swap_entry (TYPE_1__) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  print_bad_pte (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_same (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ reuse_swap_page (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_free (TYPE_1__) ; 
 int /*<<< orphan*/  swap_usage ; 
 struct page* swapin_readahead (TYPE_1__,int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  trace_mm_anon_pgin (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  try_to_free_swap (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_swap_full () ; 

__attribute__((used)) static int do_swap_page(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, pte_t *page_table, pmd_t *pmd,
		unsigned int flags, pte_t orig_pte)
{
	spinlock_t *ptl;
	struct page *page = NULL, *swapcache = NULL;
	swp_entry_t entry;
	pte_t pte;
	int locked;
	struct mem_cgroup *ptr = NULL;
	int exclusive = 0;
	int ret = 0;

	if (!pte_unmap_same(mm, pmd, page_table, orig_pte))
		goto out;

	entry = pte_to_swp_entry(orig_pte);
	if (unlikely(non_swap_entry(entry))) {
		if (is_migration_entry(entry)) {
			migration_entry_wait(mm, pmd, address);
		} else if (is_hwpoison_entry(entry)) {
			ret = VM_FAULT_HWPOISON;
		} else {
			print_bad_pte(vma, address, orig_pte, NULL);
			ret = VM_FAULT_SIGBUS;
		}
		goto out;
	}
	delayacct_set_flag(DELAYACCT_PF_SWAPIN);
	page = lookup_swap_cache(entry);
	if (!page) {
		grab_swap_token(mm); /* Contend for token _before_ read-in */
		page = swapin_readahead(entry,
					GFP_HIGHUSER_MOVABLE, vma, address);
		if (!page) {
			/*
			 * Back out if somebody else faulted in this pte
			 * while we released the pte lock.
			 */
			page_table = pte_offset_map_lock(mm, pmd, address, &ptl);
			if (likely(pte_same(*page_table, orig_pte)))
				ret = VM_FAULT_OOM;
			delayacct_clear_flag(DELAYACCT_PF_SWAPIN);
			goto unlock;
		}

		/* Had to read the page from swap area: Major fault */
		ret = VM_FAULT_MAJOR;
		count_vm_event(PGMAJFAULT);
	} else if (PageHWPoison(page)) {
		/*
		 * hwpoisoned dirty swapcache pages are kept for killing
		 * owner processes (which may be unknown at hwpoison time)
		 */
		ret = VM_FAULT_HWPOISON;
		delayacct_clear_flag(DELAYACCT_PF_SWAPIN);
		goto out_release;
	}

	locked = lock_page_or_retry(page, mm, flags);
	delayacct_clear_flag(DELAYACCT_PF_SWAPIN);
	if (!locked) {
		ret |= VM_FAULT_RETRY;
		goto out_release;
	}

	/*
	 * Make sure try_to_free_swap or reuse_swap_page or swapoff did not
	 * release the swapcache from under us.  The page pin, and pte_same
	 * test below, are not enough to exclude that.  Even if it is still
	 * swapcache, we need to check that the page's swap has not changed.
	 */
	if (unlikely(!PageSwapCache(page) || page_private(page) != entry.val))
		goto out_page;

	swapcache = page;
	page = ksm_might_need_to_copy(page, vma, address);
	if (unlikely(!page)) {
		ret = VM_FAULT_OOM;
		page = swapcache;
		swapcache = NULL;
		goto out_page;
	}
	if (page == swapcache)
		swapcache = NULL;

	if (mem_cgroup_try_charge_swapin(mm, page, GFP_KERNEL, &ptr)) {
		ret = VM_FAULT_OOM;
		goto out_page;
	}

	/*
	 * Back out if somebody else already faulted in this pte.
	 */
	page_table = pte_offset_map_lock(mm, pmd, address, &ptl);
	if (unlikely(!pte_same(*page_table, orig_pte)))
		goto out_nomap;

	if (unlikely(!PageUptodate(page))) {
		ret = VM_FAULT_SIGBUS;
		goto out_nomap;
	}

	/*
	 * The page isn't present yet, go ahead with the fault.
	 *
	 * Be careful about the sequence of operations here.
	 * To get its accounting right, reuse_swap_page() must be called
	 * while the page is counted on swap but not yet in mapcount i.e.
	 * before page_add_anon_rmap() and swap_free(); try_to_free_swap()
	 * must be called after the swap_free(), or it will never succeed.
	 * Because delete_from_swap_page() may be called by reuse_swap_page(),
	 * mem_cgroup_commit_charge_swapin() may not be able to find swp_entry
	 * in page->private. In this case, a record in swap_cgroup  is silently
	 * discarded at swap_free().
	 */

	inc_mm_counter(mm, anon_rss);
	dec_mm_counter(mm, swap_usage);
	pte = mk_pte(page, vma->vm_page_prot);
	if ((flags & FAULT_FLAG_WRITE) && reuse_swap_page(page)) {
		pte = maybe_mkwrite(pte_mkdirty(pte), vma);
		flags &= ~FAULT_FLAG_WRITE;
		exclusive = 1;
	}
	flush_icache_page(vma, page);
	set_pte_at(mm, address, page_table, pte);
	do_page_add_anon_rmap(page, vma, address, exclusive);
	/* It's better to call commit-charge after rmap is established */
	mem_cgroup_commit_charge_swapin(page, ptr);

	swap_free(entry);
	if (vm_swap_full() || (vma->vm_flags & VM_LOCKED) || PageMlocked(page))
		try_to_free_swap(page);
	unlock_page(page);
	if (swapcache) {
		/*
		 * Hold the lock to avoid the swap entry to be reused
		 * until we take the PT lock for the pte_same() check
		 * (to avoid false positives from pte_same). For
		 * further safety release the lock after the swap_free
		 * so that the swap count won't change under a
		 * parallel locked swapcache.
		 */
		unlock_page(swapcache);
		page_cache_release(swapcache);
	}

	if (flags & FAULT_FLAG_WRITE) {
		ret |= do_wp_page(mm, vma, address, page_table, pmd, ptl, pte);
		if (ret & VM_FAULT_ERROR)
			ret &= VM_FAULT_ERROR;
		goto out;
	}

	/* No need to invalidate - it was non-present before */
	update_mmu_cache(vma, address, pte);
unlock:
	pte_unmap_unlock(page_table, ptl);
out:
	trace_mm_anon_pgin(mm, address);
	return ret;
out_nomap:
	mem_cgroup_cancel_charge_swapin(ptr);
	pte_unmap_unlock(page_table, ptl);
out_page:
	unlock_page(page);
out_release:
	page_cache_release(page);
	if (swapcache) {
		unlock_page(swapcache);
		page_cache_release(swapcache);
	}
	return ret;
}