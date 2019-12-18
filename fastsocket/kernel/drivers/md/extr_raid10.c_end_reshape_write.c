#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r10conf {TYPE_1__* mirrors; } ;
struct r10bio {struct mddev* mddev; } ;
struct mddev {struct r10conf* private; } ;
struct md_rdev {int dummy; } ;
struct bio {struct r10bio* bi_private; int /*<<< orphan*/  bi_flags; } ;
struct TYPE_2__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  end_reshape_request (struct r10bio*) ; 
 int find_bio_disk (struct r10conf*,struct r10bio*,struct bio*,int*,int*) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void end_reshape_write(struct bio *bio, int error)
{
	int uptodate = test_bit(BIO_UPTODATE, &bio->bi_flags);
	struct r10bio *r10_bio = bio->bi_private;
	struct mddev *mddev = r10_bio->mddev;
	struct r10conf *conf = mddev->private;
	int d;
	int slot;
	int repl;
	struct md_rdev *rdev = NULL;

	d = find_bio_disk(conf, r10_bio, bio, &slot, &repl);
	if (repl)
		rdev = conf->mirrors[d].replacement;
	if (!rdev) {
		smp_mb();
		rdev = conf->mirrors[d].rdev;
	}

	if (!uptodate) {
		/* FIXME should record badblock */
		md_error(mddev, rdev);
	}

	rdev_dec_pending(rdev, mddev);
	end_reshape_request(r10_bio);
}