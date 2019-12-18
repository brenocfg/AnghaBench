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
struct mddev {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  flush_pending; } ;
struct md_rdev {struct mddev* mddev; } ;
struct bio {struct md_rdev* bi_private; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  md_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 

__attribute__((used)) static void md_end_flush(struct bio *bio, int err)
{
	struct md_rdev *rdev = bio->bi_private;
	struct mddev *mddev = rdev->mddev;

	rdev_dec_pending(rdev, mddev);

	if (atomic_dec_and_test(&mddev->flush_pending)) {
		/* The pre-request flush has finished */
		queue_work(md_wq, &mddev->flush_work);
	}
	bio_put(bio);
}