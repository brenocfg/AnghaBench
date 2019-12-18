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
struct address_space {int /*<<< orphan*/  page_tree; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int radix_tree_gang_lookup_tag (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int pohmelfs_inode_has_dirty_pages(struct address_space *mapping, pgoff_t index)
{
	int ret;
	struct page *page;

	rcu_read_lock();
	ret = radix_tree_gang_lookup_tag(&mapping->page_tree,
				(void **)&page, index, 1, PAGECACHE_TAG_DIRTY);
	rcu_read_unlock();
	return ret;
}