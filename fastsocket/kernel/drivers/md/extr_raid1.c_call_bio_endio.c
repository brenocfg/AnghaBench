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
struct r1conf {int /*<<< orphan*/  device_lock; } ;
struct r1bio {int /*<<< orphan*/  state; TYPE_1__* mddev; struct bio* master_bio; } ;
struct bio {scalar_t__ bi_phys_segments; int /*<<< orphan*/  bi_flags; } ;
struct TYPE_2__ {struct r1conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  R1BIO_Uptodate ; 
 int /*<<< orphan*/  allow_barrier (struct r1conf*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void call_bio_endio(struct r1bio *r1_bio)
{
	struct bio *bio = r1_bio->master_bio;
	int done;
	struct r1conf *conf = r1_bio->mddev->private;

	if (bio->bi_phys_segments) {
		unsigned long flags;
		spin_lock_irqsave(&conf->device_lock, flags);
		bio->bi_phys_segments--;
		done = (bio->bi_phys_segments == 0);
		spin_unlock_irqrestore(&conf->device_lock, flags);
	} else
		done = 1;

	if (!test_bit(R1BIO_Uptodate, &r1_bio->state))
		clear_bit(BIO_UPTODATE, &bio->bi_flags);
	if (done) {
		bio_endio(bio, 0);
		/*
		 * Wake up any possible resync thread that waits for the device
		 * to go idle.
		 */
		allow_barrier(conf);
	}
}