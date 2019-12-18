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
struct address_space {scalar_t__ host; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __mark_inode_dirty (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_page_dirtied (struct page*,struct address_space*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int __set_page_dirty_nobuffers(struct page *page)
{
	if (!TestSetPageDirty(page)) {
		struct address_space *mapping = page_mapping(page);
		struct address_space *mapping2;

		if (!mapping)
			return 1;

		spin_lock_irq(&mapping->tree_lock);
		mapping2 = page_mapping(page);
		if (mapping2) { /* Race with truncate? */
			BUG_ON(mapping2 != mapping);
			WARN_ON_ONCE(!PagePrivate(page) && !PageUptodate(page));
			account_page_dirtied(page, mapping);
			radix_tree_tag_set(&mapping->page_tree,
				page_index(page), PAGECACHE_TAG_DIRTY);
		}
		spin_unlock_irq(&mapping->tree_lock);
		if (mapping->host) {
			/* !PageAnon && !swapper_space */
			__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);
		}
		return 1;
	}
	return 0;
}