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
typedef  int /*<<< orphan*/  start_pfn ;
typedef  int /*<<< orphan*/  end_pfn ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ MIGRATE_ISOLATE ; 
 struct page* __first_valid_page (unsigned long,int) ; 
 scalar_t__ get_pageblock_migratetype (struct page*) ; 
 int pageblock_nr_pages ; 
 int /*<<< orphan*/  unset_migratetype_isolate (struct page*) ; 

int
undo_isolate_page_range(unsigned long start_pfn, unsigned long end_pfn)
{
	unsigned long pfn;
	struct page *page;
	BUG_ON((start_pfn) & (pageblock_nr_pages - 1));
	BUG_ON((end_pfn) & (pageblock_nr_pages - 1));
	for (pfn = start_pfn;
	     pfn < end_pfn;
	     pfn += pageblock_nr_pages) {
		page = __first_valid_page(pfn, pageblock_nr_pages);
		if (!page || get_pageblock_migratetype(page) != MIGRATE_ISOLATE)
			continue;
		unset_migratetype_isolate(page);
	}
	return 0;
}