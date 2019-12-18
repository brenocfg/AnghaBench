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
struct page {int flags; int /*<<< orphan*/  _count; int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int PAGE_FLAGS_CHECK_AT_FREE ; 
 int PAGE_FLAGS_CHECK_AT_PREP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bad_page (struct page*) ; 
 int mem_cgroup_bad_page_check (struct page*) ; 
 int page_mapcount (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int free_pages_check(struct page *page)
{
	if (unlikely(page_mapcount(page) |
		(page->mapping != NULL)  |
		(atomic_read(&page->_count) != 0) |
		(page->flags & PAGE_FLAGS_CHECK_AT_FREE) |
		(mem_cgroup_bad_page_check(page)))) {
		bad_page(page);
		return 1;
	}
	if (page->flags & PAGE_FLAGS_CHECK_AT_PREP)
		page->flags &= ~PAGE_FLAGS_CHECK_AT_PREP;
	return 0;
}