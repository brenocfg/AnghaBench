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
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  INC_CACHE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_total ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 TYPE_1__ swapper_space ; 
 int /*<<< orphan*/  total_swapcache_pages ; 

void __delete_from_swap_cache(struct page *page)
{
	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(!PageSwapCache(page));
	VM_BUG_ON(PageWriteback(page));

	radix_tree_delete(&swapper_space.page_tree, page_private(page));
	set_page_private(page, 0);
	ClearPageSwapCache(page);
	total_swapcache_pages--;
	__dec_zone_page_state(page, NR_FILE_PAGES);
	INC_CACHE_INFO(del_total);
}