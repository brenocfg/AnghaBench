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
 int EBUSY ; 
 struct page* __first_valid_page (unsigned long,int) ; 
 int pageblock_nr_pages ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 scalar_t__ set_migratetype_isolate (struct page*) ; 
 int /*<<< orphan*/  unset_migratetype_isolate (int /*<<< orphan*/ ) ; 

int
start_isolate_page_range(unsigned long start_pfn, unsigned long end_pfn)
{
	unsigned long pfn;
	unsigned long undo_pfn;
	struct page *page;

	BUG_ON((start_pfn) & (pageblock_nr_pages - 1));
	BUG_ON((end_pfn) & (pageblock_nr_pages - 1));

	for (pfn = start_pfn;
	     pfn < end_pfn;
	     pfn += pageblock_nr_pages) {
		page = __first_valid_page(pfn, pageblock_nr_pages);
		if (page && set_migratetype_isolate(page)) {
			undo_pfn = pfn;
			goto undo;
		}
	}
	return 0;
undo:
	for (pfn = start_pfn;
	     pfn < undo_pfn;
	     pfn += pageblock_nr_pages)
		unset_migratetype_isolate(pfn_to_page(pfn));

	return -EBUSY;
}