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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int max; int /*<<< orphan*/ * swap_map; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 scalar_t__ SWAP_MAP_BAD ; 
 int page_cluster ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ swap_count (int /*<<< orphan*/ ) ; 
 struct swap_info_struct** swap_info ; 
 int /*<<< orphan*/  swap_lock ; 
 int swp_offset (int /*<<< orphan*/ ) ; 
 size_t swp_type (int /*<<< orphan*/ ) ; 

int valid_swaphandles(swp_entry_t entry, unsigned long *offset)
{
	struct swap_info_struct *si;
	int our_page_cluster = page_cluster;
	pgoff_t target, toff;
	pgoff_t base, end;
	int nr_pages = 0;

	if (!our_page_cluster)	/* no readahead */
		return 0;

	si = swap_info[swp_type(entry)];
	target = swp_offset(entry);
	base = (target >> our_page_cluster) << our_page_cluster;
	end = base + (1 << our_page_cluster);
	if (!base)		/* first page is swap header */
		base++;

	spin_lock(&swap_lock);
	if (end > si->max)	/* don't go beyond end of map */
		end = si->max;

	/* Count contiguous allocated slots above our target */
	for (toff = target; ++toff < end; nr_pages++) {
		/* Don't read in free or bad pages */
		if (!si->swap_map[toff])
			break;
		if (swap_count(si->swap_map[toff]) == SWAP_MAP_BAD)
			break;
	}
	/* Count contiguous allocated slots below our target */
	for (toff = target; --toff >= base; nr_pages++) {
		/* Don't read in free or bad pages */
		if (!si->swap_map[toff])
			break;
		if (swap_count(si->swap_map[toff]) == SWAP_MAP_BAD)
			break;
	}
	spin_unlock(&swap_lock);

	/*
	 * Indicate starting offset, and return number of pages to get:
	 * if only 1, say 0, since there's then no readahead to be done.
	 */
	*offset = ++toff;
	return nr_pages? ++nr_pages: 0;
}