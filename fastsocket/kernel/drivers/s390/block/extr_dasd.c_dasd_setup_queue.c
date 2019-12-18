#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_block {int s2b_shift; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  bp_block; TYPE_2__* base; } ;
struct TYPE_4__ {int features; TYPE_1__* discipline; } ;
struct TYPE_3__ {int max_blocks; } ;

/* Variables and functions */
 int DASD_FEATURE_USERAW ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_max_segments (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dasd_setup_queue(struct dasd_block *block)
{
	int max;

	if (block->base->features & DASD_FEATURE_USERAW) {
		/*
		 * the max_blocks value for raw_track access is 256
		 * it is higher than the native ECKD value because we
		 * only need one ccw per track
		 * so the max_hw_sectors are
		 * 2048 x 512B = 1024kB = 16 tracks
		 */
		max = 2048;
	} else {
		max = block->base->discipline->max_blocks << block->s2b_shift;
	}
	blk_queue_logical_block_size(block->request_queue,
				     block->bp_block);
	blk_queue_max_hw_sectors(block->request_queue, max);
	blk_queue_max_segments(block->request_queue, -1L);
	/* with page sized segments we can translate each segement into
	 * one idaw/tidaw
	 */
	blk_queue_max_segment_size(block->request_queue, PAGE_SIZE);
	blk_queue_segment_boundary(block->request_queue, PAGE_SIZE - 1);
}