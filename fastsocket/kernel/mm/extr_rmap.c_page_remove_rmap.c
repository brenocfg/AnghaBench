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
struct page {int /*<<< orphan*/  _mapcount; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_ANON_PAGES ; 
 int /*<<< orphan*/  NR_ANON_TRANSPARENT_HUGEPAGES ; 
 int /*<<< orphan*/  NR_FILE_MAPPED ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  __dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_cap_account_dirty (struct address_space*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_page (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_update_file_mapped (struct page*,int) ; 
 int /*<<< orphan*/  page_clear_dirty (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ page_test_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void page_remove_rmap(struct page *page)
{
	struct address_space *mapping = page_mapping(page);

	/* page still mapped by someone else? */
	if (!atomic_add_negative(-1, &page->_mapcount))
		return;

	/*
	 * Now that the last pte has gone, s390 must transfer dirty
	 * flag from storage key to struct page.  We can usually skip
	 * this if the page is anon, so about to be freed; but perhaps
	 * not if it's in swapcache - there might be another pte slot
	 * containing the swap entry, but page not yet written to swap.
	 *
	 * And we can skip it on file pages, so long as the filesystem
	 * participates in dirty tracking; but need to catch shm and tmpfs
	 * and ramfs pages which have been modified since creation by read
	 * fault.
	 *
	 * Note that mapping must be decided above, before decrementing
	 * mapcount (which luckily provides a barrier): once page is unmapped,
	 * it could be truncated and page->mapping reset to NULL at any moment.
	 * Note also that we are relying on page_mapping(page) to set mapping
	 * to &swapper_space when PageSwapCache(page).
	 */
	if (mapping && !mapping_cap_account_dirty(mapping) &&
	    page_test_dirty(page)) {
		page_clear_dirty(page);
		set_page_dirty(page);
	}
	/*
	 * Hugepages are not counted in NR_ANON_PAGES nor NR_FILE_MAPPED
	 * and not charged by memcg for now.
	 */
	if (unlikely(PageHuge(page)))
		return;
	if (PageAnon(page)) {
		mem_cgroup_uncharge_page(page);
		if (!PageTransHuge(page))
			__dec_zone_page_state(page, NR_ANON_PAGES);
		else
			__dec_zone_page_state(page,
					      NR_ANON_TRANSPARENT_HUGEPAGES);
	} else {
		__dec_zone_page_state(page, NR_FILE_MAPPED);
		mem_cgroup_update_file_mapped(page, -1);
	}
	/*
	 * It would be tidy to reset the PageAnon mapping here,
	 * but that might overwrite a racing page_add_anon_rmap
	 * which increments mapcount after us but sets mapping
	 * before us: so leave the reset to free_hot_cold_page,
	 * and remember that it's only reliable while mapped.
	 * Leaving it set also helps swapoff to reinstate ptes
	 * faster for those pages still in swapcache.
	 */
}