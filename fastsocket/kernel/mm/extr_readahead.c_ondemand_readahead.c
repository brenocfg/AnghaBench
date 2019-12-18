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
struct file_ra_state {unsigned long start; unsigned long size; unsigned long async_size; unsigned long prev_pos; int /*<<< orphan*/  ra_pages; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  page_tree; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 unsigned long PAGE_CACHE_SHIFT ; 
 unsigned long __do_page_cache_readahead (struct address_space*,struct file*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long get_init_ra_size (unsigned long,unsigned long) ; 
 void* get_next_ra_size (struct file_ra_state*,unsigned long) ; 
 unsigned long max_sane_readahead (int /*<<< orphan*/ ) ; 
 unsigned long ra_submit (struct file_ra_state*,struct address_space*,struct file*) ; 
 unsigned long radix_tree_next_hole (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ try_context_readahead (struct address_space*,struct file_ra_state*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long
ondemand_readahead(struct address_space *mapping,
		   struct file_ra_state *ra, struct file *filp,
		   bool hit_readahead_marker, pgoff_t offset,
		   unsigned long req_size)
{
	unsigned long max = max_sane_readahead(ra->ra_pages);

	/*
	 * start of file
	 */
	if (!offset)
		goto initial_readahead;

	/*
	 * It's the expected callback offset, assume sequential access.
	 * Ramp up sizes, and push forward the readahead window.
	 */
	if ((offset == (ra->start + ra->size - ra->async_size) ||
	     offset == (ra->start + ra->size))) {
		ra->start += ra->size;
		ra->size = get_next_ra_size(ra, max);
		ra->async_size = ra->size;
		goto readit;
	}

	/*
	 * Hit a marked page without valid readahead state.
	 * E.g. interleaved reads.
	 * Query the pagecache for async_size, which normally equals to
	 * readahead size. Ramp it up and use it as the new readahead size.
	 */
	if (hit_readahead_marker) {
		pgoff_t start;

		rcu_read_lock();
		start = radix_tree_next_hole(&mapping->page_tree, offset+1,max);
		rcu_read_unlock();

		if (!start || start - offset > max)
			return 0;

		ra->start = start;
		ra->size = start - offset;	/* old async_size */
		ra->size += req_size;
		ra->size = get_next_ra_size(ra, max);
		ra->async_size = ra->size;
		goto readit;
	}

	/*
	 * oversize read
	 */
	if (req_size > max)
		goto initial_readahead;

	/*
	 * sequential cache miss
	 */
	if (offset - (ra->prev_pos >> PAGE_CACHE_SHIFT) <= 1UL)
		goto initial_readahead;

	/*
	 * Query the page cache and look for the traces(cached history pages)
	 * that a sequential stream would leave behind.
	 */
	if (try_context_readahead(mapping, ra, offset, req_size, max))
		goto readit;

	/*
	 * standalone, small random read
	 * Read as is, and do not pollute the readahead state.
	 */
	return __do_page_cache_readahead(mapping, filp, offset, req_size, 0);

initial_readahead:
	ra->start = offset;
	ra->size = get_init_ra_size(req_size, max);
	ra->async_size = ra->size > req_size ? ra->size - req_size : ra->size;

readit:
	/*
	 * Will this read hit the readahead marker made by itself?
	 * If so, trigger the readahead marker hit now, and merge
	 * the resulted next readahead window into the current one.
	 */
	if (offset == ra->start && ra->size == ra->async_size) {
		ra->async_size = get_next_ra_size(ra, max);
		ra->size += ra->async_size;
	}

	return ra_submit(ra, mapping, filp);
}