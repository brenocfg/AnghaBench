#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {size_t pd_idx; int qd_idx; int /*<<< orphan*/  state; scalar_t__ bm_seq; int /*<<< orphan*/  sector; int /*<<< orphan*/  stripe_lock; TYPE_1__* dev; } ;
struct r5conf {int chunk_sectors; int raid_disks; int max_degraded; int /*<<< orphan*/  preread_active_stripes; scalar_t__ seq_flush; TYPE_2__* mddev; int /*<<< orphan*/  wait_for_overlap; } ;
struct mddev {scalar_t__ reshape_position; int /*<<< orphan*/  bitmap; struct r5conf* private; } ;
struct bio {int bi_sector; int bi_size; int bi_phys_segments; int /*<<< orphan*/ * bi_next; } ;
typedef  int sector_t ;
struct TYPE_4__ {scalar_t__ bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; struct bio* towrite; scalar_t__ toread; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int DIV_ROUND_UP_SECTOR_T (int,int) ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  R5_OVERWRITE ; 
 int /*<<< orphan*/  R5_Overlap ; 
 int /*<<< orphan*/  STRIPE_BIT_DELAY ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_DISCARD ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  STRIPE_SYNCING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_startwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct stripe_head* get_active_stripe (struct r5conf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_write_end (struct mddev*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int raid5_dec_bi_active_stripes (struct bio*) ; 
 int /*<<< orphan*/  raid5_inc_bi_active_stripes (struct bio*) ; 
 int /*<<< orphan*/  release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  sector_div (int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w ; 

__attribute__((used)) static int make_discard_request(struct mddev *mddev, struct bio *bi)
{
	struct r5conf *conf = mddev->private;
	sector_t logical_sector, last_sector;
	struct stripe_head *sh;
	int remaining;
	int stripe_sectors;

	if (mddev->reshape_position != MaxSector)
		/* Skip discard while reshape is happening */
		return 0;

	logical_sector = bi->bi_sector & ~((sector_t)STRIPE_SECTORS-1);
	last_sector = bi->bi_sector + (bi->bi_size>>9);

	bi->bi_next = NULL;
	bi->bi_phys_segments = 1; /* over-loaded to count active stripes */

	stripe_sectors = conf->chunk_sectors *
		(conf->raid_disks - conf->max_degraded);
	logical_sector = DIV_ROUND_UP_SECTOR_T(logical_sector,
					       stripe_sectors);
	sector_div(last_sector, stripe_sectors);

	logical_sector *= conf->chunk_sectors;
	last_sector *= conf->chunk_sectors;

	for (; logical_sector < last_sector;
	     logical_sector += STRIPE_SECTORS) {
		DEFINE_WAIT(w);
		int d;
	again:
		sh = get_active_stripe(conf, logical_sector, 0, 0, 0);
		prepare_to_wait(&conf->wait_for_overlap, &w,
				TASK_UNINTERRUPTIBLE);
		set_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags);
		if (test_bit(STRIPE_SYNCING, &sh->state)) {
			release_stripe(sh);
			schedule();
			goto again;
		}
		clear_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags);
		spin_lock_irq(&sh->stripe_lock);
		for (d = 0; d < conf->raid_disks; d++) {
			if (d == sh->pd_idx || d == sh->qd_idx)
				continue;
			if (sh->dev[d].towrite || sh->dev[d].toread) {
				set_bit(R5_Overlap, &sh->dev[d].flags);
				spin_unlock_irq(&sh->stripe_lock);
				release_stripe(sh);
				schedule();
				goto again;
			}
		}
		set_bit(STRIPE_DISCARD, &sh->state);
		finish_wait(&conf->wait_for_overlap, &w);
		for (d = 0; d < conf->raid_disks; d++) {
			if (d == sh->pd_idx || d == sh->qd_idx)
				continue;
			sh->dev[d].towrite = bi;
			set_bit(R5_OVERWRITE, &sh->dev[d].flags);
			raid5_inc_bi_active_stripes(bi);
		}
		spin_unlock_irq(&sh->stripe_lock);
		if (conf->mddev->bitmap) {
			for (d = 0;
			     d < conf->raid_disks - conf->max_degraded;
			     d++)
				bitmap_startwrite(mddev->bitmap,
						  sh->sector,
						  STRIPE_SECTORS,
						  0);
			sh->bm_seq = conf->seq_flush + 1;
			set_bit(STRIPE_BIT_DELAY, &sh->state);
		}

		set_bit(STRIPE_HANDLE, &sh->state);
		clear_bit(STRIPE_DELAYED, &sh->state);
		if (!test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			atomic_inc(&conf->preread_active_stripes);
		release_stripe(sh);
	}

	remaining = raid5_dec_bi_active_stripes(bi);
	if (remaining == 0) {
		md_write_end(mddev);
		bio_endio(bi, 0);
	}

	return 0;
}