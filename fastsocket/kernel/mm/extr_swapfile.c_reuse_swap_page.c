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

/* Variables and functions */
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  delete_from_swap_cache (struct page*) ; 
 int page_mapcount (struct page*) ; 
 scalar_t__ page_swapcount (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int reuse_swap_page(struct page *page)
{
	int count;

	VM_BUG_ON(!PageLocked(page));
	if (unlikely(PageKsm(page)))
		return 0;
	count = page_mapcount(page);
	if (count <= 1 && PageSwapCache(page)) {
		count += page_swapcount(page);
		if (count == 1 && !PageWriteback(page)) {
			delete_from_swap_cache(page);
			SetPageDirty(page);
		}
	}
	return count <= 1;
}