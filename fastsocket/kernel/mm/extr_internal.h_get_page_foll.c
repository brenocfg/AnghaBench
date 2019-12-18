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
struct page {int /*<<< orphan*/  _count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __get_page_tail_foll (struct page*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void get_page_foll(struct page *page)
{
	if (unlikely(PageTail(page)))
		/*
		 * This is safe only because
		 * __split_huge_page_refcount() can't run under
		 * get_page_foll() because we hold the proper PT lock.
		 */
		__get_page_tail_foll(page, true);
	else {
		/*
		 * Getting a normal page or the head of a compound page
		 * requires to already have an elevated page->_count.
		 */
		VM_BUG_ON(atomic_read(&page->_count) <= 0);
		atomic_inc(&page->_count);
	}
}