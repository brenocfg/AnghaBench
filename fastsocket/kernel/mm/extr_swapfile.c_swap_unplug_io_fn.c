#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ swp_entry_t ;
struct page {int dummy; } ;
struct block_device {TYPE_2__* bd_inode; } ;
struct backing_dev_info {int dummy; } ;
struct TYPE_9__ {struct block_device* bdev; } ;
struct TYPE_7__ {TYPE_1__* i_mapping; } ;
struct TYPE_6__ {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  blk_run_backing_dev (struct backing_dev_info*,struct page*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 TYPE_5__** swap_info ; 
 int /*<<< orphan*/  swap_unplug_sem ; 
 size_t swp_type (TYPE_3__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void swap_unplug_io_fn(struct backing_dev_info *unused_bdi, struct page *page)
{
	swp_entry_t entry;

	down_read(&swap_unplug_sem);
	entry.val = page_private(page);
	if (PageSwapCache(page)) {
		struct block_device *bdev = swap_info[swp_type(entry)]->bdev;
		struct backing_dev_info *bdi;

		/*
		 * If the page is removed from swapcache from under us (with a
		 * racy try_to_unuse/swapoff) we need an additional reference
		 * count to avoid reading garbage from page_private(page) above.
		 * If the WARN_ON triggers during a swapoff it maybe the race
		 * condition and it's harmless. However if it triggers without
		 * swapoff it signals a problem.
		 */
		WARN_ON(page_count(page) <= 1);

		bdi = bdev->bd_inode->i_mapping->backing_dev_info;
		blk_run_backing_dev(bdi, page);
	}
	up_read(&swap_unplug_sem);
}