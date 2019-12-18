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
struct page {int /*<<< orphan*/  flags; struct address_space* mapping; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PG_dirty ; 
 int TestClearPageDirty (struct page*) ; 
 int clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int __nilfs_clear_page_dirty(struct page *page)
{
	struct address_space *mapping = page->mapping;

	if (mapping) {
		spin_lock_irq(&mapping->tree_lock);
		if (test_bit(PG_dirty, &page->flags)) {
			radix_tree_tag_clear(&mapping->page_tree,
					     page_index(page),
					     PAGECACHE_TAG_DIRTY);
			spin_unlock_irq(&mapping->tree_lock);
			return clear_page_dirty_for_io(page);
		}
		spin_unlock_irq(&mapping->tree_lock);
		return 0;
	}
	return TestClearPageDirty(page);
}