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
struct r1conf {TYPE_1__* mirrors; } ;
struct r1bio {long sectors; size_t read_disk; int /*<<< orphan*/  state; int /*<<< orphan*/  remaining; scalar_t__ sector; struct mddev* mddev; } ;
struct mddev {int /*<<< orphan*/  recovery; int /*<<< orphan*/  bitmap; struct r1conf* private; } ;
struct bio {struct r1bio* bi_private; int /*<<< orphan*/  bi_flags; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {TYPE_2__* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  R1BIO_MadeGood ; 
 int /*<<< orphan*/  R1BIO_WriteError ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  WriteErrorSeen ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_end_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int find_bio_disk (struct r1bio*,struct bio*) ; 
 scalar_t__ is_badblock (TYPE_2__*,scalar_t__,long,scalar_t__*,int*) ; 
 int /*<<< orphan*/  md_done_sync (struct mddev*,int,int) ; 
 int /*<<< orphan*/  put_buf (struct r1bio*) ; 
 int /*<<< orphan*/  reschedule_retry (struct r1bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void end_sync_write(struct bio *bio, int error)
{
	int uptodate = test_bit(BIO_UPTODATE, &bio->bi_flags);
	struct r1bio *r1_bio = bio->bi_private;
	struct mddev *mddev = r1_bio->mddev;
	struct r1conf *conf = mddev->private;
	int mirror=0;
	sector_t first_bad;
	int bad_sectors;

	mirror = find_bio_disk(r1_bio, bio);

	if (!uptodate) {
		sector_t sync_blocks = 0;
		sector_t s = r1_bio->sector;
		long sectors_to_go = r1_bio->sectors;
		/* make sure these bits doesn't get cleared. */
		do {
			bitmap_end_sync(mddev->bitmap, s,
					&sync_blocks, 1);
			s += sync_blocks;
			sectors_to_go -= sync_blocks;
		} while (sectors_to_go > 0);
		set_bit(WriteErrorSeen,
			&conf->mirrors[mirror].rdev->flags);
		if (!test_and_set_bit(WantReplacement,
				      &conf->mirrors[mirror].rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				mddev->recovery);
		set_bit(R1BIO_WriteError, &r1_bio->state);
	} else if (is_badblock(conf->mirrors[mirror].rdev,
			       r1_bio->sector,
			       r1_bio->sectors,
			       &first_bad, &bad_sectors) &&
		   !is_badblock(conf->mirrors[r1_bio->read_disk].rdev,
				r1_bio->sector,
				r1_bio->sectors,
				&first_bad, &bad_sectors)
		)
		set_bit(R1BIO_MadeGood, &r1_bio->state);

	if (atomic_dec_and_test(&r1_bio->remaining)) {
		int s = r1_bio->sectors;
		if (test_bit(R1BIO_MadeGood, &r1_bio->state) ||
		    test_bit(R1BIO_WriteError, &r1_bio->state))
			reschedule_retry(r1_bio);
		else {
			put_buf(r1_bio);
			md_done_sync(mddev, s, uptodate);
		}
	}
}