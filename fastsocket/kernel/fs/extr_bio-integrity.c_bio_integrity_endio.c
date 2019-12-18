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
struct bio_integrity_payload {int /*<<< orphan*/  bip_work; int /*<<< orphan*/  bip_end_io; struct bio* bip_bio; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct bio_integrity_payload* bi_integrity; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int) ; 
 int /*<<< orphan*/  bio_integrity_verify_fn ; 
 int /*<<< orphan*/  kintegrityd_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bio_integrity_endio(struct bio *bio, int error)
{
	struct bio_integrity_payload *bip = bio->bi_integrity;

	BUG_ON(bip->bip_bio != bio);

	/* In case of an I/O error there is no point in verifying the
	 * integrity metadata.  Restore original bio end_io handler
	 * and run it.
	 */
	if (error) {
		bio->bi_end_io = bip->bip_end_io;
		bio_endio(bio, error);

		return;
	}

	INIT_WORK(&bip->bip_work, bio_integrity_verify_fn);
	queue_work(kintegrityd_wq, &bip->bip_work);
}