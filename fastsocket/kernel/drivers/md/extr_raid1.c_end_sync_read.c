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
struct r1bio {int /*<<< orphan*/  remaining; int /*<<< orphan*/  state; int /*<<< orphan*/  read_disk; } ;
struct bio {int /*<<< orphan*/  bi_flags; struct r1bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  R1BIO_Uptodate ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reschedule_retry (struct r1bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_head_pos (int /*<<< orphan*/ ,struct r1bio*) ; 

__attribute__((used)) static void end_sync_read(struct bio *bio, int error)
{
	struct r1bio *r1_bio = bio->bi_private;

	update_head_pos(r1_bio->read_disk, r1_bio);

	/*
	 * we have read a block, now it needs to be re-written,
	 * or re-read if the read failed.
	 * We don't do much here, just schedule handling by raid1d
	 */
	if (test_bit(BIO_UPTODATE, &bio->bi_flags))
		set_bit(R1BIO_Uptodate, &r1_bio->state);

	if (atomic_dec_and_test(&r1_bio->remaining))
		reschedule_retry(r1_bio);
}