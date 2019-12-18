#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r10conf {int /*<<< orphan*/  mddev; TYPE_2__* mirrors; } ;
struct r10bio {int /*<<< orphan*/  state; TYPE_3__* devs; int /*<<< orphan*/  sectors; TYPE_1__* mddev; } ;
struct md_rdev {int /*<<< orphan*/  flags; TYPE_4__* mddev; } ;
struct bio {struct r10bio* bi_private; int /*<<< orphan*/  bi_flags; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_8__ {int /*<<< orphan*/  recovery; } ;
struct TYPE_7__ {void* bio; void* repl_bio; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;
struct TYPE_5__ {struct r10conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  Faulty ; 
 void* IO_MADE_GOOD ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  R10BIO_MadeGood ; 
 int /*<<< orphan*/  R10BIO_Uptodate ; 
 int /*<<< orphan*/  R10BIO_WriteError ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  WriteErrorSeen ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int find_bio_disk (struct r10conf*,struct r10bio*,struct bio*,int*,int*) ; 
 scalar_t__ is_badblock (struct md_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  md_error (TYPE_4__*,struct md_rdev*) ; 
 int /*<<< orphan*/  one_write_done (struct r10bio*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid10_end_write_request(struct bio *bio, int error)
{
	int uptodate = test_bit(BIO_UPTODATE, &bio->bi_flags);
	struct r10bio *r10_bio = bio->bi_private;
	int dev;
	int dec_rdev = 1;
	struct r10conf *conf = r10_bio->mddev->private;
	int slot, repl;
	struct md_rdev *rdev = NULL;

	dev = find_bio_disk(conf, r10_bio, bio, &slot, &repl);

	if (repl)
		rdev = conf->mirrors[dev].replacement;
	if (!rdev) {
		smp_rmb();
		repl = 0;
		rdev = conf->mirrors[dev].rdev;
	}
	/*
	 * this branch is our 'one mirror IO has finished' event handler:
	 */
	if (!uptodate) {
		if (repl)
			/* Never record new bad blocks to replacement,
			 * just fail it.
			 */
			md_error(rdev->mddev, rdev);
		else {
			set_bit(WriteErrorSeen,	&rdev->flags);
			if (!test_and_set_bit(WantReplacement, &rdev->flags))
				set_bit(MD_RECOVERY_NEEDED,
					&rdev->mddev->recovery);
			set_bit(R10BIO_WriteError, &r10_bio->state);
			dec_rdev = 0;
		}
	} else {
		/*
		 * Set R10BIO_Uptodate in our master bio, so that
		 * we will return a good error code for to the higher
		 * levels even if IO on some other mirrored buffer fails.
		 *
		 * The 'master' represents the composite IO operation to
		 * user-side. So if something waits for IO, then it will
		 * wait for the 'master' bio.
		 */
		sector_t first_bad;
		int bad_sectors;

		/*
		 * Do not set R10BIO_Uptodate if the current device is
		 * rebuilding or Faulty. This is because we cannot use
		 * such device for properly reading the data back (we could
		 * potentially use it, if the current write would have felt
		 * before rdev->recovery_offset, but for simplicity we don't
		 * check this here.
		 */
		if (test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags))
			set_bit(R10BIO_Uptodate, &r10_bio->state);

		/* Maybe we can clear some bad blocks. */
		if (is_badblock(rdev,
				r10_bio->devs[slot].addr,
				r10_bio->sectors,
				&first_bad, &bad_sectors)) {
			bio_put(bio);
			if (repl)
				r10_bio->devs[slot].repl_bio = IO_MADE_GOOD;
			else
				r10_bio->devs[slot].bio = IO_MADE_GOOD;
			dec_rdev = 0;
			set_bit(R10BIO_MadeGood, &r10_bio->state);
		}
	}

	/*
	 *
	 * Let's see if all mirrored write operations have finished
	 * already.
	 */
	one_write_done(r10_bio);
	if (dec_rdev)
		rdev_dec_pending(rdev, conf->mddev);
}