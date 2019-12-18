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
struct throtl_grp {int /*<<< orphan*/  blkg; int /*<<< orphan*/ * io_disp; int /*<<< orphan*/ * bytes_disp; } ;
struct bio {int bi_rw; scalar_t__ bi_size; } ;

/* Variables and functions */
 int REQ_SYNC ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  blkiocg_update_dispatch_stats (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

__attribute__((used)) static void throtl_charge_bio(struct throtl_grp *tg, struct bio *bio)
{
	bool rw = bio_data_dir(bio);
	bool sync = bio->bi_rw & REQ_SYNC;

	/* Charge the bio to the group */
	tg->bytes_disp[rw] += bio->bi_size;
	tg->io_disp[rw]++;

	blkiocg_update_dispatch_stats(&tg->blkg, bio->bi_size, rw, sync);
}