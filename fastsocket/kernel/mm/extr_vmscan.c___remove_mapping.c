#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  a_ops; struct inode* host; } ;
struct TYPE_5__ {void (* freepage ) (struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_3__* EXT_AOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_AOP_EXT (struct inode*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  __delete_from_swap_cache (struct page*) ; 
 int /*<<< orphan*/  __remove_from_page_cache (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_cache_page (struct page*) ; 
 int /*<<< orphan*/  page_freeze_refs (struct page*,int) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_unfreeze_refs (struct page*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapcache_free (TYPE_1__,struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __remove_mapping(struct address_space *mapping, struct page *page)
{
	struct inode *inode = mapping->host;

	BUG_ON(!PageLocked(page));
	BUG_ON(mapping != page_mapping(page));

	spin_lock_irq(&mapping->tree_lock);
	/*
	 * The non racy check for a busy page.
	 *
	 * Must be careful with the order of the tests. When someone has
	 * a ref to the page, it may be possible that they dirty it then
	 * drop the reference. So if PageDirty is tested before page_count
	 * here, then the following race may occur:
	 *
	 * get_user_pages(&page);
	 * [user mapping goes away]
	 * write_to(page);
	 *				!PageDirty(page)    [good]
	 * SetPageDirty(page);
	 * put_page(page);
	 *				!page_count(page)   [good, discard it]
	 *
	 * [oops, our write_to data is lost]
	 *
	 * Reversing the order of the tests ensures such a situation cannot
	 * escape unnoticed. The smp_rmb is needed to ensure the page->flags
	 * load is not satisfied before that of page->_count.
	 *
	 * Note that if SetPageDirty is always performed via set_page_dirty,
	 * and thus under tree_lock, then this ordering is not required.
	 */
	if (!page_freeze_refs(page, 2))
		goto cannot_free;
	/* note: atomic_cmpxchg in page_freeze_refs provides the smp_rmb */
	if (unlikely(PageDirty(page))) {
		page_unfreeze_refs(page, 2);
		goto cannot_free;
	}

	if (PageSwapCache(page)) {
		swp_entry_t swap = { .val = page_private(page) };
		__delete_from_swap_cache(page);
		spin_unlock_irq(&mapping->tree_lock);
		swapcache_free(swap, page);
	} else {
		void (*freepage)(struct page *) = NULL;

		if (IS_AOP_EXT(inode))
			freepage = EXT_AOPS(mapping->a_ops)->freepage;

		__remove_from_page_cache(page);
		spin_unlock_irq(&mapping->tree_lock);
		mem_cgroup_uncharge_cache_page(page);

		if (freepage != NULL)
			freepage(page);
	}

	return 1;

cannot_free:
	spin_unlock_irq(&mapping->tree_lock);
	return 0;
}