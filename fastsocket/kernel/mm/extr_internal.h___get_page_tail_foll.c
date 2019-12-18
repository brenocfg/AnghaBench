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
struct page {int /*<<< orphan*/  _mapcount; TYPE_1__* first_page; int /*<<< orphan*/  _count; } ;
struct TYPE_2__ {int /*<<< orphan*/  _count; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ page_mapcount (struct page*) ; 

__attribute__((used)) static inline void __get_page_tail_foll(struct page *page,
					bool get_page_head)
{
	/*
	 * If we're getting a tail page, the elevated page->_count is
	 * required only in the head page and we will elevate the head
	 * page->_count and tail page->_mapcount.
	 *
	 * We elevate page_tail->_mapcount for tail pages to force
	 * page_tail->_count to be zero at all times to avoid getting
	 * false positives from get_page_unless_zero() with
	 * speculative page access (like in
	 * page_cache_get_speculative()) on tail pages.
	 */
	VM_BUG_ON(atomic_read(&page->first_page->_count) <= 0);
	VM_BUG_ON(atomic_read(&page->_count) != 0);
	VM_BUG_ON(page_mapcount(page) < 0);
	if (get_page_head)
		atomic_inc(&page->first_page->_count);
	atomic_inc(&page->_mapcount);
}