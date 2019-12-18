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
struct throtl_grp {int* bps; int* iops; int /*<<< orphan*/ * slice_end; int /*<<< orphan*/ * bio_lists; scalar_t__* nr_queued; } ;
struct throtl_data {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int bio_data_dir (struct bio*) ; 
 struct bio* bio_list_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 unsigned long max (unsigned long,unsigned long) ; 
 scalar_t__ tg_with_in_bps_limit (struct throtl_data*,struct throtl_grp*,struct bio*,unsigned long*) ; 
 scalar_t__ tg_with_in_iops_limit (struct throtl_data*,struct throtl_grp*,struct bio*,unsigned long*) ; 
 int /*<<< orphan*/  throtl_extend_slice (struct throtl_data*,struct throtl_grp*,int,scalar_t__) ; 
 scalar_t__ throtl_slice ; 
 scalar_t__ throtl_slice_used (struct throtl_data*,struct throtl_grp*,int) ; 
 int /*<<< orphan*/  throtl_start_new_slice (struct throtl_data*,struct throtl_grp*,int) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool tg_may_dispatch(struct throtl_data *td, struct throtl_grp *tg,
				struct bio *bio, unsigned long *wait)
{
	bool rw = bio_data_dir(bio);
	unsigned long bps_wait = 0, iops_wait = 0, max_wait = 0;

	/*
 	 * Currently whole state machine of group depends on first bio
	 * queued in the group bio list. So one should not be calling
	 * this function with a different bio if there are other bios
	 * queued.
	 */
	BUG_ON(tg->nr_queued[rw] && bio != bio_list_peek(&tg->bio_lists[rw]));

	/* If tg->bps = -1, then BW is unlimited */
	if (tg->bps[rw] == -1 && tg->iops[rw] == -1) {
		if (wait)
			*wait = 0;
		return 1;
	}

	/*
	 * If previous slice expired, start a new one otherwise renew/extend
	 * existing slice to make sure it is at least throtl_slice interval
	 * long since now.
	 */
	if (throtl_slice_used(td, tg, rw))
		throtl_start_new_slice(td, tg, rw);
	else {
		if (time_before(tg->slice_end[rw], jiffies + throtl_slice))
			throtl_extend_slice(td, tg, rw, jiffies + throtl_slice);
	}

	if (tg_with_in_bps_limit(td, tg, bio, &bps_wait)
	    && tg_with_in_iops_limit(td, tg, bio, &iops_wait)) {
		if (wait)
			*wait = 0;
		return 1;
	}

	max_wait = max(bps_wait, iops_wait);

	if (wait)
		*wait = max_wait;

	if (time_before(tg->slice_end[rw], jiffies + max_wait))
		throtl_extend_slice(td, tg, rw, jiffies + max_wait);

	return 0;
}