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
struct buffer_head {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 struct buffer_head* __find_get_block_slow (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

void unmap_underlying_metadata(struct block_device *bdev, sector_t block)
{
	struct buffer_head *old_bh;

	might_sleep();

	old_bh = __find_get_block_slow(bdev, block);
	if (old_bh) {
		clear_buffer_dirty(old_bh);
		wait_on_buffer(old_bh);
		clear_buffer_req(old_bh);
		__brelse(old_bh);
	}
}