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
struct pagevec {struct page** pages; } ;
struct page {scalar_t__ index; } ;
struct address_space {int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EIO ; 
 int /*<<< orphan*/  AS_ENOSPC ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 scalar_t__ PAGEVEC_SIZE ; 
 scalar_t__ TestClearPageError (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 int pagevec_lookup_tag (struct pagevec*,struct address_space*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int wait_on_page_writeback_range(struct address_space *mapping,
				pgoff_t start, pgoff_t end)
{
	struct pagevec pvec;
	int nr_pages;
	int ret = 0;
	pgoff_t index;

	if (end < start)
		return 0;

	pagevec_init(&pvec, 0);
	index = start;
	while ((index <= end) &&
			(nr_pages = pagevec_lookup_tag(&pvec, mapping, &index,
			PAGECACHE_TAG_WRITEBACK,
			min(end - index, (pgoff_t)PAGEVEC_SIZE-1) + 1)) != 0) {
		unsigned i;

		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];

			/* until radix tree lookup accepts end_index */
			if (page->index > end)
				continue;

			wait_on_page_writeback(page);
			if (TestClearPageError(page))
				ret = -EIO;
		}
		pagevec_release(&pvec);
		cond_resched();
	}

	/* Check for outstanding write errors */
	if (test_and_clear_bit(AS_ENOSPC, &mapping->flags))
		ret = -ENOSPC;
	if (test_and_clear_bit(AS_EIO, &mapping->flags))
		ret = -EIO;

	return ret;
}