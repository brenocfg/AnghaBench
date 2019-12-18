#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  a_ops; struct inode* host; } ;
struct TYPE_2__ {void (* freepage ) (struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 TYPE_1__* EXT_AOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_AOP_EXT (struct inode*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  __remove_from_page_cache (struct page*) ; 
 int /*<<< orphan*/  clear_page_mlock (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_cache_page (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
invalidate_complete_page2(struct address_space *mapping, struct page *page)
{
	struct inode *inode = mapping->host;
	void (*freepage)(struct page *);

	if (page->mapping != mapping)
		return 0;

	if (page_has_private(page) && !try_to_release_page(page, GFP_KERNEL))
		return 0;

	spin_lock_irq(&mapping->tree_lock);
	if (PageDirty(page))
		goto failed;

	clear_page_mlock(page);
	BUG_ON(page_has_private(page));
	__remove_from_page_cache(page);
	spin_unlock_irq(&mapping->tree_lock);
	mem_cgroup_uncharge_cache_page(page);

	if (IS_AOP_EXT(inode)) {
		freepage = EXT_AOPS(mapping->a_ops)->freepage;
		if (freepage != NULL)
			freepage(page);
	}

	page_cache_release(page);	/* pagecache ref */
	return 1;
failed:
	spin_unlock_irq(&mapping->tree_lock);
	return 0;
}