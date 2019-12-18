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
struct request_queue {int /*<<< orphan*/  make_request_fn; } ;
struct block_device {int /*<<< orphan*/ * bd_disk; } ;
struct bio {int /*<<< orphan*/  bi_sector; int /*<<< orphan*/ * bi_private; struct block_device* bi_bdev; int /*<<< orphan*/  bi_end_io; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  WRITE_FLUSH ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_end_flush ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  submit_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int __blkdev_issue_flush(struct block_device *bdev, gfp_t gfp_mask,
		sector_t *error_sector)
{
	DECLARE_COMPLETION_ONSTACK(wait);
	struct request_queue *q;
	struct bio *bio;
	int ret = 0;

	if (bdev->bd_disk == NULL)
		return -ENXIO;

	q = bdev_get_queue(bdev);
	if (!q)
		return -ENXIO;

	/*
	 * some block devices may not have their queue correctly set up here
	 * (e.g. loop device without a backing file) and so issuing a flush
	 * here will panic. Ensure there is a request function before issuing
	 * the flush.
	 */
	if (!q->make_request_fn)
		return -ENXIO;

	bio = bio_alloc(gfp_mask, 0);
	bio->bi_end_io = bio_end_flush;
	bio->bi_bdev = bdev;
	bio->bi_private = &wait;

	bio_get(bio);
	submit_bio(WRITE_FLUSH, bio);
	wait_for_completion(&wait);

	/*
	 * The driver must store the error location in ->bi_sector, if
	 * it supports it. For non-stacked drivers, this should be
	 * copied from blk_rq_pos(rq).
	 */
	if (error_sector)
               *error_sector = bio->bi_sector;

	if (!bio_flagged(bio, BIO_UPTODATE))
		ret = -EIO;

	bio_put(bio);
	return ret;
}