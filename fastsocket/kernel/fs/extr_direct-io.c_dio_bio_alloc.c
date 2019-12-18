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
struct dio_submit {int /*<<< orphan*/  cur_page_fs_offset; int /*<<< orphan*/  logical_offset_in_bio; struct bio* bio; } ;
struct dio {scalar_t__ is_async; } ;
struct block_device {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/  bi_sector; struct block_device* bi_bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dio_bio_end_aio ; 
 int /*<<< orphan*/  dio_bio_end_io ; 

__attribute__((used)) static inline void
dio_bio_alloc(struct dio *dio, struct dio_submit *sdio,
	      struct block_device *bdev,
	      sector_t first_sector, int nr_vecs)
{
	struct bio *bio;

	/*
	 * bio_alloc() is guaranteed to return a bio when called with
	 * __GFP_WAIT and we request a valid number of vectors.
	 */
	bio = bio_alloc(GFP_KERNEL, nr_vecs);

	bio->bi_bdev = bdev;
	bio->bi_sector = first_sector;
	if (dio->is_async)
		bio->bi_end_io = dio_bio_end_aio;
	else
		bio->bi_end_io = dio_bio_end_io;

	sdio->bio = bio;
	sdio->logical_offset_in_bio = sdio->cur_page_fs_offset;
}