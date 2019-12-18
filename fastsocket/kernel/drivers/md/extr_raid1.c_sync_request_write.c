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
struct r1conf {int raid_disks; TYPE_2__* mirrors; } ;
struct r1bio {size_t read_disk; int sectors; int /*<<< orphan*/  state; int /*<<< orphan*/  remaining; struct bio** bios; } ;
struct mddev {int /*<<< orphan*/  recovery; struct r1conf* private; } ;
struct bio {int /*<<< orphan*/ * bi_end_io; int /*<<< orphan*/  bi_rw; } ;
struct TYPE_4__ {TYPE_1__* rdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_REQUESTED ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 int /*<<< orphan*/  R1BIO_MadeGood ; 
 int /*<<< orphan*/  R1BIO_Uptodate ; 
 int /*<<< orphan*/  R1BIO_WriteError ; 
 int /*<<< orphan*/  WRITE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/ * end_sync_read ; 
 int /*<<< orphan*/ * end_sync_write ; 
 int /*<<< orphan*/  fix_sync_read_error (struct r1bio*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  md_done_sync (struct mddev*,int,int) ; 
 int /*<<< orphan*/  md_sync_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ process_checks (struct r1bio*) ; 
 int /*<<< orphan*/  put_buf (struct r1bio*) ; 
 int /*<<< orphan*/  reschedule_retry (struct r1bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sync_request_write(struct mddev *mddev, struct r1bio *r1_bio)
{
	struct r1conf *conf = mddev->private;
	int i;
	int disks = conf->raid_disks * 2;
	struct bio *bio, *wbio;

	bio = r1_bio->bios[r1_bio->read_disk];

	if (!test_bit(R1BIO_Uptodate, &r1_bio->state))
		/* ouch - failed to read all of that. */
		if (!fix_sync_read_error(r1_bio))
			return;

	if (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
		if (process_checks(r1_bio) < 0)
			return;
	/*
	 * schedule writes
	 */
	atomic_set(&r1_bio->remaining, 1);
	for (i = 0; i < disks ; i++) {
		wbio = r1_bio->bios[i];
		if (wbio->bi_end_io == NULL ||
		    (wbio->bi_end_io == end_sync_read &&
		     (i == r1_bio->read_disk ||
		      !test_bit(MD_RECOVERY_SYNC, &mddev->recovery))))
			continue;

		wbio->bi_rw = WRITE;
		wbio->bi_end_io = end_sync_write;
		atomic_inc(&r1_bio->remaining);
		md_sync_acct(conf->mirrors[i].rdev->bdev, bio_sectors(wbio));

		generic_make_request(wbio);
	}

	if (atomic_dec_and_test(&r1_bio->remaining)) {
		/* if we're here, all write(s) have completed, so clean up */
		int s = r1_bio->sectors;
		if (test_bit(R1BIO_MadeGood, &r1_bio->state) ||
		    test_bit(R1BIO_WriteError, &r1_bio->state))
			reschedule_retry(r1_bio);
		else {
			put_buf(r1_bio);
			md_done_sync(mddev, s, 1);
		}
	}
}