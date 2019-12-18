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
struct zone {int /*<<< orphan*/  lru_lock; } ;
struct page {int flags; int mapping; int /*<<< orphan*/  _count; scalar_t__ index; int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageCompound (struct page*) ; 
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  NR_ANON_PAGES ; 
 int /*<<< orphan*/  NR_ANON_TRANSPARENT_HUGEPAGES ; 
 int PAGE_FLAGS_CHECK_AT_PREP ; 
 long PG_dirty ; 
 long PG_mlocked ; 
 long PG_referenced ; 
 long PG_swapbacked ; 
 long PG_uptodate ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int __PG_HWPOISON ; 
 int /*<<< orphan*/  __dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_zone_page_state (struct zone*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compound_lock (struct page*) ; 
 int /*<<< orphan*/  compound_unlock (struct page*) ; 
 int /*<<< orphan*/  lru_add_page_tail (struct zone*,struct page*,struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_split_hugepage_commit (struct page*,struct page*) ; 
 scalar_t__ page_count (struct page*) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __split_huge_page_refcount(struct page *page)
{
	int i;
	struct zone *zone = page_zone(page);
	int tail_count = 0;

	/* prevent PageLRU to go away from under us, and freeze lru stats */
	spin_lock_irq(&zone->lru_lock);
	compound_lock(page);

	for (i = HPAGE_PMD_NR - 1; i >= 1; i--) {
		struct page *page_tail = page + i;

		/* tail_page->_mapcount cannot change */
		BUG_ON(page_mapcount(page_tail) < 0);
		tail_count += page_mapcount(page_tail);
		/* check for overflow */
		BUG_ON(tail_count < 0);
		BUG_ON(atomic_read(&page_tail->_count) != 0);
		atomic_add(page_mapcount(page) + page_mapcount(page_tail) + 1,
			   &page_tail->_count);

		/* after clearing PageTail the gup refcount can be released */
		smp_mb();

		/*
		 * retain hwpoison flag of the poisoned tail page:
		 *   fix for the unsuitable process killed on Guest Machine(KVM)
		 *   by the memory-failure.
		 */
		page_tail->flags &= ~PAGE_FLAGS_CHECK_AT_PREP | __PG_HWPOISON;
		page_tail->flags |= (page->flags &
				     ((1L << PG_referenced) |
				      (1L << PG_swapbacked) |
				      (1L << PG_mlocked) |
				      (1L << PG_uptodate)));
		page_tail->flags |= (1L << PG_dirty);

		/* clear PageTail before overwriting first_page */
		smp_wmb();

		/*
		 * __split_huge_page_splitting() already set the
		 * splitting bit in all pmd that could map this
		 * hugepage, that will ensure no CPU can alter the
		 * mapcount on the head page. The mapcount is only
		 * accounted in the head page and it has to be
		 * transferred to all tail pages in the below code. So
		 * for this code to be safe, the split the mapcount
		 * can't change. But that doesn't mean userland can't
		 * keep changing and reading the page contents while
		 * we transfer the mapcount, so the pmd splitting
		 * status is achieved setting a reserved bit in the
		 * pmd, not by clearing the present bit.
		*/
		page_tail->_mapcount = page->_mapcount;

		BUG_ON(page_tail->mapping);
		page_tail->mapping = page->mapping;

		page_tail->index = page->index + i;

		BUG_ON(!PageAnon(page_tail));
		BUG_ON(!PageUptodate(page_tail));
		BUG_ON(!PageDirty(page_tail));
		BUG_ON(!PageSwapBacked(page_tail));

		mem_cgroup_split_hugepage_commit(page_tail, page);
		lru_add_page_tail(zone, page, page_tail);
	}
	atomic_sub(tail_count, &page->_count);
	BUG_ON(atomic_read(&page->_count) <= 0);

	__dec_zone_page_state(page, NR_ANON_TRANSPARENT_HUGEPAGES);
	__mod_zone_page_state(zone, NR_ANON_PAGES, HPAGE_PMD_NR);

	ClearPageCompound(page);
	compound_unlock(page);
	spin_unlock_irq(&zone->lru_lock);

	for (i = 1; i < HPAGE_PMD_NR; i++) {
		struct page *page_tail = page + i;
		BUG_ON(page_count(page_tail) <= 0);
		/*
		 * Tail pages may be freed if there wasn't any mapping
		 * like if add_to_swap() is running on a lru page that
		 * had its mapping zapped. And freeing these pages
		 * requires taking the lru_lock so we do the put_page
		 * of the tail pages after the split is complete.
		 */
		put_page(page_tail);
	}

	/*
	 * Only the head page (now become a regular page) is required
	 * to be pinned by the caller.
	 */
	BUG_ON(page_count(page) <= 0);
}