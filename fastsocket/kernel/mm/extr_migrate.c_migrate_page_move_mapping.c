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
struct page {int dummy; } ;
struct buffer_head {int dummy; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int EAGAIN ; 
 int MIGRATE_ASYNC ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  NR_SHMEM ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  __dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __put_page (struct page*) ; 
 int /*<<< orphan*/  buffer_migrate_lock_buffers (struct buffer_head*,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  page_freeze_refs (struct page*,int) ; 
 int page_has_private (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_unfreeze_refs (struct page*,int) ; 
 scalar_t__ radix_tree_deref_slot (void**) ; 
 void** radix_tree_lookup_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_replace_slot (void**,struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int migrate_page_move_mapping(struct address_space *mapping,
		struct page *newpage, struct page *page,
		struct buffer_head *head, enum migrate_mode mode)
{
	int expected_count;
	void **pslot;

	if (!mapping) {
		/* Anonymous page without mapping */
		if (page_count(page) != 1)
			return -EAGAIN;
		return 0;
	}

	spin_lock_irq(&mapping->tree_lock);

	pslot = radix_tree_lookup_slot(&mapping->page_tree,
 					page_index(page));

	expected_count = 2 + page_has_private(page);
	if (page_count(page) != expected_count ||
			(struct page *)radix_tree_deref_slot(pslot) != page) {
		spin_unlock_irq(&mapping->tree_lock);
		return -EAGAIN;
	}

	if (!page_freeze_refs(page, expected_count)) {
		spin_unlock_irq(&mapping->tree_lock);
		return -EAGAIN;
	}

	/*
	 * In the async migration case of moving a page with buffers, lock the
	 * buffers using trylock before the mapping is moved. If the mapping
	 * was moved, we later failed to lock the buffers and could not move
	 * the mapping back due to an elevated page count, we would have to
	 * block waiting on other references to be dropped.
	 */
	if (mode == MIGRATE_ASYNC && head &&
			!buffer_migrate_lock_buffers(head, mode)) {
		page_unfreeze_refs(page, expected_count);
		spin_unlock_irq(&mapping->tree_lock);
		return -EAGAIN;
	}

	/*
	 * Now we know that no one else is looking at the page.
	 */
	get_page(newpage);	/* add cache reference */
	if (PageSwapCache(page)) {
		SetPageSwapCache(newpage);
		set_page_private(newpage, page_private(page));
	}

	radix_tree_replace_slot(pslot, newpage);

	page_unfreeze_refs(page, expected_count);
	/*
	 * Drop cache reference from old page.
	 * We know this isn't the last reference.
	 */
	__put_page(page);

	/*
	 * If moved to a different zone then also account
	 * the page for that zone. Other VM counters will be
	 * taken care of when we establish references to the
	 * new page and drop references to the old page.
	 *
	 * Note that anonymous pages are accounted for
	 * via NR_FILE_PAGES and NR_ANON_PAGES if they
	 * are mapped to swap space.
	 */
	__dec_zone_page_state(page, NR_FILE_PAGES);
	__inc_zone_page_state(newpage, NR_FILE_PAGES);
	if (!PageSwapCache(page) && PageSwapBacked(page)) {
		__dec_zone_page_state(page, NR_SHMEM);
		__inc_zone_page_state(newpage, NR_SHMEM);
	}
	spin_unlock_irq(&mapping->tree_lock);

	return 0;
}