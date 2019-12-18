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
struct stripe_head {int /*<<< orphan*/  state; } ;
struct r5conf {int quiesce; scalar_t__ max_degraded; int raid_disks; TYPE_1__* disks; scalar_t__ fullsync; int /*<<< orphan*/  wait_for_overlap; } ;
struct mddev {scalar_t__ dev_sectors; scalar_t__ curr_resync; scalar_t__ degraded; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  recovery; struct r5conf* private; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int /*<<< orphan*/ * rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_REQUESTED ; 
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  STRIPE_SYNC_REQUESTED ; 
 int /*<<< orphan*/  bitmap_close_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_cond_end_sync (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_end_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  bitmap_start_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  end_reshape (struct r5conf*) ; 
 struct stripe_head* get_active_stripe (struct r5conf*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  release_stripe (struct stripe_head*) ; 
 scalar_t__ reshape_request (struct mddev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unplug_slaves (struct mddev*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline sector_t sync_request(struct mddev *mddev, sector_t sector_nr, int *skipped, int go_faster)
{
	struct r5conf *conf = mddev->private;
	struct stripe_head *sh;
	sector_t max_sector = mddev->dev_sectors;
	sector_t sync_blocks;
	int still_degraded = 0;
	int i;

	if (sector_nr >= max_sector) {
		/* just being told to finish up .. nothing much to do */
		unplug_slaves(mddev);

		if (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery)) {
			end_reshape(conf);
			return 0;
		}

		if (mddev->curr_resync < max_sector) /* aborted */
			bitmap_end_sync(mddev->bitmap, mddev->curr_resync,
					&sync_blocks, 1);
		else /* completed sync */
			conf->fullsync = 0;
		bitmap_close_sync(mddev->bitmap);

		return 0;
	}

	/* Allow raid5_quiesce to complete */
	wait_event(conf->wait_for_overlap, conf->quiesce != 2);

	if (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		return reshape_request(mddev, sector_nr, skipped);

	/* No need to check resync_max as we never do more than one
	 * stripe, and as resync_max will always be on a chunk boundary,
	 * if the check in md_do_sync didn't fire, there is no chance
	 * of overstepping resync_max here
	 */

	/* if there is too many failed drives and we are trying
	 * to resync, then assert that we are finished, because there is
	 * nothing we can do.
	 */
	if (mddev->degraded >= conf->max_degraded &&
	    test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) {
		sector_t rv = mddev->dev_sectors - sector_nr;
		*skipped = 1;
		return rv;
	}
	if (!test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery) &&
	    !conf->fullsync &&
	    !bitmap_start_sync(mddev->bitmap, sector_nr, &sync_blocks, 1) &&
	    sync_blocks >= STRIPE_SECTORS) {
		/* we can skip this block, and probably more */
		sync_blocks /= STRIPE_SECTORS;
		*skipped = 1;
		return sync_blocks * STRIPE_SECTORS; /* keep things rounded to whole stripes */
	}

	bitmap_cond_end_sync(mddev->bitmap, sector_nr);

	sh = get_active_stripe(conf, sector_nr, 0, 1, 0);
	if (sh == NULL) {
		sh = get_active_stripe(conf, sector_nr, 0, 0, 0);
		/* make sure we don't swamp the stripe cache if someone else
		 * is trying to get access
		 */
		schedule_timeout_uninterruptible(1);
	}
	/* Need to check if array will still be degraded after recovery/resync
	 * We don't need to check the 'failed' flag as when that gets set,
	 * recovery aborts.
	 */
	for (i = 0; i < conf->raid_disks; i++)
		if (conf->disks[i].rdev == NULL)
			still_degraded = 1;

	bitmap_start_sync(mddev->bitmap, sector_nr, &sync_blocks, still_degraded);

	set_bit(STRIPE_SYNC_REQUESTED, &sh->state);

	handle_stripe(sh);
	release_stripe(sh);

	return STRIPE_SECTORS;
}