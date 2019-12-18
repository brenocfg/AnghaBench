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
struct page {scalar_t__ index; struct address_space* mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 struct page* find_get_page (struct address_space*,scalar_t__) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  radix_tree_exception (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct page *find_lock_page(struct address_space *mapping, pgoff_t offset)
{
	struct page *page;

repeat:
	page = find_get_page(mapping, offset);
	if (page && !radix_tree_exception(page)) {
		lock_page(page);
		/* Has the page been truncated? */
		if (unlikely(page->mapping != mapping)) {
			unlock_page(page);
			page_cache_release(page);
			goto repeat;
		}
		VM_BUG_ON(page->index != offset);
	}
	return page;
}