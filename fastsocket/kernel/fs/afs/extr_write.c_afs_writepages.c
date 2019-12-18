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
struct writeback_control {int encountered_congestion; scalar_t__ nr_to_write; int range_start; int range_end; scalar_t__ nonblocking; scalar_t__ range_cyclic; } ;
struct backing_dev_info {int dummy; } ;
struct address_space {void* writeback_index; struct backing_dev_info* backing_dev_info; } ;
typedef  void* pgoff_t ;

/* Variables and functions */
 int LLONG_MAX ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_writepages_region (struct address_space*,struct writeback_control*,void*,void*,void**) ; 
 scalar_t__ bdi_write_congested (struct backing_dev_info*) ; 

int afs_writepages(struct address_space *mapping,
		   struct writeback_control *wbc)
{
	struct backing_dev_info *bdi = mapping->backing_dev_info;
	pgoff_t start, end, next;
	int ret;

	_enter("");

	if (wbc->nonblocking && bdi_write_congested(bdi)) {
		wbc->encountered_congestion = 1;
		_leave(" = 0 [congest]");
		return 0;
	}

	if (wbc->range_cyclic) {
		start = mapping->writeback_index;
		end = -1;
		ret = afs_writepages_region(mapping, wbc, start, end, &next);
		if (start > 0 && wbc->nr_to_write > 0 && ret == 0 &&
		    !(wbc->nonblocking && wbc->encountered_congestion))
			ret = afs_writepages_region(mapping, wbc, 0, start,
						    &next);
		mapping->writeback_index = next;
	} else if (wbc->range_start == 0 && wbc->range_end == LLONG_MAX) {
		end = (pgoff_t)(LLONG_MAX >> PAGE_CACHE_SHIFT);
		ret = afs_writepages_region(mapping, wbc, 0, end, &next);
		if (wbc->nr_to_write > 0)
			mapping->writeback_index = next;
	} else {
		start = wbc->range_start >> PAGE_CACHE_SHIFT;
		end = wbc->range_end >> PAGE_CACHE_SHIFT;
		ret = afs_writepages_region(mapping, wbc, start, end, &next);
	}

	_leave(" = %d", ret);
	return ret;
}