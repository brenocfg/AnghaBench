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
struct writeback_control {int encountered_congestion; int range_start; int range_end; scalar_t__ nr_to_write; scalar_t__ range_cyclic; scalar_t__ nonblocking; } ;
struct pagevec {int dummy; } ;
struct backing_dev_info {int dummy; } ;
struct address_space {int writeback_index; struct backing_dev_info* backing_dev_info; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int LLONG_MAX ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 scalar_t__ PAGEVEC_SIZE ; 
 int PAGE_CACHE_SHIFT ; 
 scalar_t__ bdi_write_congested (struct backing_dev_info*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int gfs2_write_jdata_pagevec (struct address_space*,struct writeback_control*,struct pagevec*,int,int) ; 
 scalar_t__ min (int,int) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 int pagevec_lookup_tag (struct pagevec*,struct address_space*,int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 

__attribute__((used)) static int gfs2_write_cache_jdata(struct address_space *mapping,
				  struct writeback_control *wbc)
{
	struct backing_dev_info *bdi = mapping->backing_dev_info;
	int ret = 0;
	int done = 0;
	struct pagevec pvec;
	int nr_pages;
	pgoff_t index;
	pgoff_t end;
	int scanned = 0;
	int range_whole = 0;

	if (wbc->nonblocking && bdi_write_congested(bdi)) {
		wbc->encountered_congestion = 1;
		return 0;
	}

	pagevec_init(&pvec, 0);
	if (wbc->range_cyclic) {
		index = mapping->writeback_index; /* Start from prev offset */
		end = -1;
	} else {
		index = wbc->range_start >> PAGE_CACHE_SHIFT;
		end = wbc->range_end >> PAGE_CACHE_SHIFT;
		if (wbc->range_start == 0 && wbc->range_end == LLONG_MAX)
			range_whole = 1;
		scanned = 1;
	}

retry:
	 while (!done && (index <= end) &&
		(nr_pages = pagevec_lookup_tag(&pvec, mapping, &index,
					       PAGECACHE_TAG_DIRTY,
					       min(end - index, (pgoff_t)PAGEVEC_SIZE-1) + 1))) {
		scanned = 1;
		ret = gfs2_write_jdata_pagevec(mapping, wbc, &pvec, nr_pages, end);
		if (ret)
			done = 1;
		if (ret > 0)
			ret = 0;

		pagevec_release(&pvec);
		cond_resched();
	}

	if (!scanned && !done) {
		/*
		 * We hit the last page and there is more work to be done: wrap
		 * back to the start of the file
		 */
		scanned = 1;
		index = 0;
		goto retry;
	}

	if (wbc->range_cyclic || (range_whole && wbc->nr_to_write > 0))
		mapping->writeback_index = index;
	return ret;
}