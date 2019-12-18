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
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* EXT_AOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_AOP_EXT (struct inode*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  __remove_from_page_cache (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_cache_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void remove_from_page_cache(struct page *page)
{
	struct address_space *mapping = page->mapping;
	void (*freepage)(struct page *) = NULL;
	struct inode *inode = mapping->host;

	BUG_ON(!PageLocked(page));

	if (IS_AOP_EXT(inode))
		freepage = EXT_AOPS(mapping->a_ops)->freepage;

	spin_lock_irq(&mapping->tree_lock);
	__remove_from_page_cache(page);
	spin_unlock_irq(&mapping->tree_lock);
	mem_cgroup_uncharge_cache_page(page);

	if (freepage)
		freepage(page);
}