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
typedef  int /*<<< orphan*/  u16 ;
struct request_queue {int dummy; } ;
struct gendisk {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
 int /*<<< orphan*/  BLK_BOUNCE_ANY ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_VIRT ; 
 struct request_queue* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (struct request_queue*,scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (struct request_queue*,scalar_t__) ; 
 int /*<<< orphan*/  blkif_io_lock ; 
 int /*<<< orphan*/  do_blkif_request ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 

__attribute__((used)) static int xlvbd_init_blk_queue(struct gendisk *gd, u16 sector_size)
{
	struct request_queue *rq;

	rq = blk_init_queue(do_blkif_request, &blkif_io_lock);
	if (rq == NULL)
		return -1;

	queue_flag_set_unlocked(QUEUE_FLAG_VIRT, rq);

	/* Hard sector size and max sectors impersonate the equiv. hardware. */
	blk_queue_logical_block_size(rq, sector_size);
	blk_queue_max_hw_sectors(rq, 512);

	/* Each segment in a request is up to an aligned page in size. */
	blk_queue_segment_boundary(rq, PAGE_SIZE - 1);
	blk_queue_max_segment_size(rq, PAGE_SIZE);

	/* Ensure a merged request will fit in a single I/O ring slot. */
	blk_queue_max_segments(rq, BLKIF_MAX_SEGMENTS_PER_REQUEST);

	/* Make sure buffer addresses are sector-aligned. */
	blk_queue_dma_alignment(rq, 511);

	/* Make sure we don't use bounce buffers. */
	blk_queue_bounce_limit(rq, BLK_BOUNCE_ANY);

	gd->queue = rq;

	return 0;
}