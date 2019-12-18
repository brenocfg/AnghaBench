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
struct r5conf {int /*<<< orphan*/  wait_for_stripe; int /*<<< orphan*/  active_aligned_reads; int /*<<< orphan*/  mddev; } ;
struct mddev {struct r5conf* private; } ;
struct md_rdev {struct mddev* mddev; } ;
struct bio {int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/ * bi_next; int /*<<< orphan*/  bi_flags; struct bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  add_bio_to_retry (struct bio*,struct r5conf*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_bio_complete (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid5_align_endio(struct bio *bi, int error)
{
	struct bio* raid_bi  = bi->bi_private;
	struct mddev *mddev;
	struct r5conf *conf;
	int uptodate = test_bit(BIO_UPTODATE, &bi->bi_flags);
	struct md_rdev *rdev;

	bio_put(bi);

	rdev = (void*)raid_bi->bi_next;
	raid_bi->bi_next = NULL;
	mddev = rdev->mddev;
	conf = mddev->private;

	rdev_dec_pending(rdev, conf->mddev);

	if (!error && uptodate) {
		trace_block_bio_complete(bdev_get_queue(raid_bi->bi_bdev),
					 raid_bi);
		bio_endio(raid_bi, 0);
		if (atomic_dec_and_test(&conf->active_aligned_reads))
			wake_up(&conf->wait_for_stripe);
		return;
	}


	pr_debug("raid5_align_endio : io error...handing IO for a retry\n");

	add_bio_to_retry(raid_bi, conf);
}