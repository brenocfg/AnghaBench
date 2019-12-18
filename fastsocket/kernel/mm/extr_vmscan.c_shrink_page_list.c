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
struct scan_control {int gfp_mask; int /*<<< orphan*/  may_writepage; int /*<<< orphan*/  nr_scanned; int /*<<< orphan*/  may_unmap; } ;
struct pagevec {int dummy; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct mem_cgroup_zone {scalar_t__ zone; } ;
struct list_head {int dummy; } ;
struct address_space {int dummy; } ;
typedef  enum pageout_io { ____Placeholder_pageout_io } pageout_io ;
typedef  enum page_references { ____Placeholder_page_references } page_references ;

/* Variables and functions */
 int DEF_PRIORITY ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PAGEOUT_IO_SYNC ; 
#define  PAGEREF_ACTIVATE 139 
#define  PAGEREF_KEEP 138 
#define  PAGEREF_RECLAIM 137 
#define  PAGEREF_RECLAIM_CLEAN 136 
#define  PAGE_ACTIVATE 135 
#define  PAGE_CLEAN 134 
#define  PAGE_KEEP 133 
#define  PAGE_SUCCESS 132 
 int /*<<< orphan*/  PGACTIVATE ; 
 int PageActive (struct page*) ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ PageUnevictable (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
#define  SWAP_AGAIN 131 
#define  SWAP_FAIL 130 
#define  SWAP_MLOCK 129 
#define  SWAP_SUCCESS 128 
 int /*<<< orphan*/  SetPageActive (struct page*) ; 
 int /*<<< orphan*/  SetPageReclaim (struct page*) ; 
 int /*<<< orphan*/  TTU_UNMAP ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  ZONE_CONGESTED ; 
 int __GFP_FS ; 
 int __GFP_IO ; 
 int /*<<< orphan*/  __clear_page_locked (struct page*) ; 
 int /*<<< orphan*/  __pagevec_free (struct pagevec*) ; 
 int /*<<< orphan*/  __remove_mapping (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  add_to_swap (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  count_vm_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_is_kswapd () ; 
 scalar_t__ global_reclaim (struct scan_control*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,struct list_head*) ; 
 struct page* lru_to_page (struct list_head*) ; 
 int page_check_references (struct page*,struct mem_cgroup_zone*,struct scan_control*) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  page_evictable (struct page*,int /*<<< orphan*/ *) ; 
 scalar_t__ page_has_private (struct page*) ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 scalar_t__ page_mapped (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ page_zone (struct page*) ; 
 int pageout (struct page*,struct address_space*,int) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 scalar_t__ pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int) ; 
 int /*<<< orphan*/  pagevec_reinit (struct pagevec*) ; 
 scalar_t__ put_page_testzero (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 
 int /*<<< orphan*/  ret_pages ; 
 int /*<<< orphan*/  trace_mm_pagereclaim_free (unsigned long) ; 
 int /*<<< orphan*/  try_to_free_swap (struct page*) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int) ; 
 int try_to_unmap (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ vm_swap_full () ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 
 int /*<<< orphan*/  zone_set_flag (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long shrink_page_list(struct list_head *page_list,
					struct scan_control *sc,
					struct mem_cgroup_zone *mz,
					enum pageout_io sync_writeback,
					int priority,
					unsigned long *ret_nr_dirty,
					unsigned long *ret_nr_writeback)
{
	LIST_HEAD(ret_pages);
	struct pagevec freed_pvec;
	int pgactivate = 0;
	unsigned long nr_dirty = 0;
	unsigned long nr_congested = 0;
	unsigned long nr_reclaimed = 0;
	unsigned long nr_writeback = 0;

	cond_resched();

	pagevec_init(&freed_pvec, 1);
	while (!list_empty(page_list)) {
		enum page_references references;
		struct address_space *mapping;
		struct page *page;
		int may_enter_fs;

		cond_resched();

		page = lru_to_page(page_list);
		list_del(&page->lru);

		if (!trylock_page(page))
			goto keep;

		VM_BUG_ON(PageActive(page));
		VM_BUG_ON(page_zone(page) != mz->zone);

		sc->nr_scanned++;

		if (unlikely(!page_evictable(page, NULL)))
			goto cull_mlocked;

		if (!sc->may_unmap && page_mapped(page))
			goto keep_locked;

		/* Double the slab pressure for mapped and swapcache pages */
		if (page_mapped(page) || PageSwapCache(page))
			sc->nr_scanned++;

		may_enter_fs = (sc->gfp_mask & __GFP_FS) ||
			(PageSwapCache(page) && (sc->gfp_mask & __GFP_IO));

		if (PageWriteback(page)) {
			nr_writeback++;
			/*
			 * Synchronous reclaim cannot queue pages for
			 * writeback due to the possibility of stack overflow
			 * but if it encounters a page under writeback, wait
			 * for the IO to complete.
			 */
			if (sync_writeback == PAGEOUT_IO_SYNC && may_enter_fs)
				wait_on_page_writeback(page);
			else
				goto keep_locked;
		}

		references = page_check_references(page, mz, sc);
		switch (references) {
		case PAGEREF_ACTIVATE:
			goto activate_locked;
		case PAGEREF_KEEP:
			goto keep_locked;
		case PAGEREF_RECLAIM:
		case PAGEREF_RECLAIM_CLEAN:
			; /* try to reclaim the page below */
		}

		/*
		 * Anonymous process memory has backing store?
		 * Try to allocate it some swap space here.
		 */
		if (PageAnon(page) && !PageSwapCache(page)) {
			if (!(sc->gfp_mask & __GFP_IO))
				goto keep_locked;
			if (!add_to_swap(page))
				goto activate_locked;
			may_enter_fs = 1;
		}

		mapping = page_mapping(page);

		/*
		 * The page is mapped into the page tables of one or more
		 * processes. Try to unmap it here.
		 */
		if (page_mapped(page) && mapping) {
			switch (try_to_unmap(page, TTU_UNMAP)) {
			case SWAP_FAIL:
				goto activate_locked;
			case SWAP_AGAIN:
				goto keep_locked;
			case SWAP_MLOCK:
				goto cull_mlocked;
			case SWAP_SUCCESS:
				; /* try to free the page below */
			}
		}

		if (PageDirty(page)) {
			nr_dirty++;

			/*
			 * Only kswapd can writeback filesystem pages to
			 * avoid risk of stack overflow but do not writeback
			 * unless under significant pressure.
			 */
			if (page_is_file_cache(page) &&
					(!current_is_kswapd() || priority >= DEF_PRIORITY - 2)) {
				/*
				 * Immediately reclaim when written back.
				 * Similar in principal to deactivate_page()
				 * except we already have the page isolated
				 * and know it's dirty
				 */
				SetPageReclaim(page);

				goto keep_locked;
			}

			if (references == PAGEREF_RECLAIM_CLEAN)
				goto keep_locked;
			if (!may_enter_fs)
				goto keep_locked;
			if (!sc->may_writepage)
				goto keep_locked;

			/* Page is dirty, try to write it out here */
			switch (pageout(page, mapping, sync_writeback)) {
			case PAGE_KEEP:
				nr_congested++;
				goto keep_locked;
			case PAGE_ACTIVATE:
				goto activate_locked;
			case PAGE_SUCCESS:
				if (PageWriteback(page) || PageDirty(page))
					goto keep;
				/*
				 * A synchronous write - probably a ramdisk.  Go
				 * ahead and try to reclaim the page.
				 */
				if (!trylock_page(page))
					goto keep;
				if (PageDirty(page) || PageWriteback(page))
					goto keep_locked;
				mapping = page_mapping(page);
			case PAGE_CLEAN:
				; /* try to free the page below */
			}
		}

		/*
		 * If the page has buffers, try to free the buffer mappings
		 * associated with this page. If we succeed we try to free
		 * the page as well.
		 *
		 * We do this even if the page is PageDirty().
		 * try_to_release_page() does not perform I/O, but it is
		 * possible for a page to have PageDirty set, but it is actually
		 * clean (all its buffers are clean).  This happens if the
		 * buffers were written out directly, with submit_bh(). ext3
		 * will do this, as well as the blockdev mapping.
		 * try_to_release_page() will discover that cleanness and will
		 * drop the buffers and mark the page clean - it can be freed.
		 *
		 * Rarely, pages can have buffers and no ->mapping.  These are
		 * the pages which were not successfully invalidated in
		 * truncate_complete_page().  We try to drop those buffers here
		 * and if that worked, and the page is no longer mapped into
		 * process address space (page_count == 1) it can be freed.
		 * Otherwise, leave the page on the LRU so it is swappable.
		 */
		if (page_has_private(page)) {
			if (!try_to_release_page(page, sc->gfp_mask))
				goto activate_locked;
			if (!mapping && page_count(page) == 1) {
				unlock_page(page);
				if (put_page_testzero(page))
					goto free_it;
				else {
					/*
					 * rare race with speculative reference.
					 * the speculative reference will free
					 * this page shortly, so we may
					 * increment nr_reclaimed here (and
					 * leave it off the LRU).
					 */
					nr_reclaimed++;
					continue;
				}
			}
		}

		if (!mapping || !__remove_mapping(mapping, page))
			goto keep_locked;

		/*
		 * At this point, we have no other references and there is
		 * no way to pick any more up (removed from LRU, removed
		 * from pagecache). Can use non-atomic bitops now (and
		 * we obviously don't have to worry about waking up a process
		 * waiting on the page lock, because there are no references.
		 */
		__clear_page_locked(page);
free_it:
		nr_reclaimed++;
		if (!pagevec_add(&freed_pvec, page)) {
			__pagevec_free(&freed_pvec);
			pagevec_reinit(&freed_pvec);
		}
		continue;

cull_mlocked:
		if (PageSwapCache(page))
			try_to_free_swap(page);
		unlock_page(page);
		putback_lru_page(page);
		continue;

activate_locked:
		/* Not a candidate for swapping, so reclaim swap space. */
		if (PageSwapCache(page) && vm_swap_full())
			try_to_free_swap(page);
		VM_BUG_ON(PageActive(page));
		SetPageActive(page);
		pgactivate++;
keep_locked:
		unlock_page(page);
keep:
		list_add(&page->lru, &ret_pages);
		VM_BUG_ON(PageLRU(page) || PageUnevictable(page));
	}

	/*
	 * Tag a zone as congested if all the dirty pages encountered were
	 * backed by a congested BDI. In this case, reclaimers should just
	 * back off and wait for congestion to clear because further reclaim
	 * will encounter the same problem
	 */
	if (nr_dirty && nr_dirty == nr_congested && global_reclaim(sc))
		zone_set_flag(mz->zone, ZONE_CONGESTED);

	list_splice(&ret_pages, page_list);
	if (pagevec_count(&freed_pvec))
		__pagevec_free(&freed_pvec);
	count_vm_events(PGACTIVATE, pgactivate);
	trace_mm_pagereclaim_free(nr_reclaimed);
        *ret_nr_dirty += nr_dirty;
        *ret_nr_writeback += nr_writeback;
	return nr_reclaimed;
}