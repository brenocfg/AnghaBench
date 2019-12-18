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
struct mddev {int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  pending_writes; } ;
struct md_rdev {struct mddev* mddev; } ;
struct bio {int /*<<< orphan*/  bi_flags; struct md_rdev* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void super_written(struct bio *bio, int error)
{
	struct md_rdev *rdev = bio->bi_private;
	struct mddev *mddev = rdev->mddev;

	if (error || !test_bit(BIO_UPTODATE, &bio->bi_flags)) {
		printk("md: super_written gets error=%d, uptodate=%d\n",
		       error, test_bit(BIO_UPTODATE, &bio->bi_flags));
		WARN_ON(test_bit(BIO_UPTODATE, &bio->bi_flags));
		md_error(mddev, rdev);
	}

	if (atomic_dec_and_test(&mddev->pending_writes))
		wake_up(&mddev->sb_wait);
	bio_put(bio);
}