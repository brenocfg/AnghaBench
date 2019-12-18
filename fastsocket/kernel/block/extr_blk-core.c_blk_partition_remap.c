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
struct hd_struct {scalar_t__ start_sect; } ;
struct block_device {int /*<<< orphan*/  bd_dev; struct block_device* bd_contains; struct hd_struct* bd_part; } ;
struct bio {scalar_t__ bi_sector; struct block_device* bi_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  trace_block_remap (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void blk_partition_remap(struct bio *bio)
{
	struct block_device *bdev = bio->bi_bdev;

	if (bio_sectors(bio) && bdev != bdev->bd_contains) {
		struct hd_struct *p = bdev->bd_part;

		bio->bi_sector += p->start_sect;
		bio->bi_bdev = bdev->bd_contains;

		trace_block_remap(bdev_get_queue(bio->bi_bdev), bio,
				    bdev->bd_dev,
				    bio->bi_sector - p->start_sect);
	}
}