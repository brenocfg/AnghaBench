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
struct stripe_head {size_t pd_idx; size_t qd_idx; int /*<<< orphan*/  state; struct r5dev* dev; int /*<<< orphan*/  sector; } ;
struct r5dev {scalar_t__ sector; int /*<<< orphan*/  flags; struct bio* written; } ;
struct r5conf {TYPE_1__* mddev; int /*<<< orphan*/  pending_full_writes; } ;
struct bio {scalar_t__ bi_sector; struct bio* bi_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_Discard ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  STRIPE_DEGRADED ; 
 int /*<<< orphan*/  STRIPE_DISCARD ; 
 int /*<<< orphan*/  STRIPE_FULL_WRITE ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  STRIPE_SYNC_REQUESTED ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_endwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_write_end (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct bio* r5_next_bio (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  raid5_dec_bi_active_stripes (struct bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_stripe_clean_event(struct r5conf *conf,
	struct stripe_head *sh, int disks, struct bio **return_bi)
{
	int i;
	struct r5dev *dev;
	int discard_pending = 0;

	for (i = disks; i--; )
		if (sh->dev[i].written) {
			dev = &sh->dev[i];
			if (!test_bit(R5_LOCKED, &dev->flags) &&
			    (test_bit(R5_UPTODATE, &dev->flags) ||
			     test_bit(R5_Discard, &dev->flags))) {
				/* We can return any write requests */
				struct bio *wbi, *wbi2;
				pr_debug("Return write for disc %d\n", i);
				if (test_and_clear_bit(R5_Discard, &dev->flags))
					clear_bit(R5_UPTODATE, &dev->flags);
				wbi = dev->written;
				dev->written = NULL;
				while (wbi && wbi->bi_sector <
					dev->sector + STRIPE_SECTORS) {
					wbi2 = r5_next_bio(wbi, dev->sector);
					if (!raid5_dec_bi_active_stripes(wbi)) {
						md_write_end(conf->mddev);
						wbi->bi_next = *return_bi;
						*return_bi = wbi;
					}
					wbi = wbi2;
				}
				bitmap_endwrite(conf->mddev->bitmap, sh->sector,
						STRIPE_SECTORS,
					 !test_bit(STRIPE_DEGRADED, &sh->state),
						0);
			} else if (test_bit(R5_Discard, &dev->flags))
				discard_pending = 1;
		}
	if (!discard_pending &&
	    test_bit(R5_Discard, &sh->dev[sh->pd_idx].flags)) {
		clear_bit(R5_Discard, &sh->dev[sh->pd_idx].flags);
		clear_bit(R5_UPTODATE, &sh->dev[sh->pd_idx].flags);
		if (sh->qd_idx >= 0) {
			clear_bit(R5_Discard, &sh->dev[sh->qd_idx].flags);
			clear_bit(R5_UPTODATE, &sh->dev[sh->qd_idx].flags);
		}
		/* now that discard is done we can proceed with any sync */
		clear_bit(STRIPE_DISCARD, &sh->state);
		if (test_bit(STRIPE_SYNC_REQUESTED, &sh->state))
			set_bit(STRIPE_HANDLE, &sh->state);

	}

	if (test_and_clear_bit(STRIPE_FULL_WRITE, &sh->state))
		if (atomic_dec_and_test(&conf->pending_full_writes))
			md_wakeup_thread(conf->mddev->thread);
}