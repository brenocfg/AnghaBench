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
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int /*<<< orphan*/  ClearPageUnevictable (struct page*) ; 
 int PageActive (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __lru_cache_add (struct page*,int) ; 

void lru_cache_add_lru(struct page *page, enum lru_list lru)
{
	if (PageActive(page)) {
		VM_BUG_ON(PageUnevictable(page));
		ClearPageActive(page);
	} else if (PageUnevictable(page)) {
		VM_BUG_ON(PageActive(page));
		ClearPageUnevictable(page);
	}

	VM_BUG_ON(PageLRU(page) || PageActive(page) || PageUnevictable(page));
	__lru_cache_add(page, lru);
}