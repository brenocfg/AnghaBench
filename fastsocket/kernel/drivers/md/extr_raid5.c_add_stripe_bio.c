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
struct stripe_head {int /*<<< orphan*/  lock; int /*<<< orphan*/  stripe_lock; TYPE_2__* dev; int /*<<< orphan*/  state; scalar_t__ bm_seq; scalar_t__ sector; struct r5conf* raid_conf; } ;
struct r5conf {scalar_t__ seq_flush; TYPE_1__* mddev; } ;
struct bio {scalar_t__ bi_sector; int bi_size; struct bio* bi_next; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {scalar_t__ sector; int /*<<< orphan*/  flags; struct bio* towrite; struct bio* toread; } ;
struct TYPE_3__ {scalar_t__ bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  R5_OVERWRITE ; 
 int /*<<< orphan*/  R5_Overlap ; 
 int /*<<< orphan*/  STRIPE_BIT_DELAY ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  bitmap_startwrite (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,unsigned long long,...) ; 
 struct bio* r5_next_bio (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  raid5_inc_bi_active_stripes (struct bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_stripe_bio(struct stripe_head *sh, struct bio *bi, int dd_idx, int forwrite)
{
	struct bio **bip;
	struct r5conf *conf = sh->raid_conf;
	int firstwrite=0;

	pr_debug("adding bi b#%llu to stripe s#%llu\n",
		(unsigned long long)bi->bi_sector,
		(unsigned long long)sh->sector);

	/*
	 * If several bio share a stripe. The bio bi_phys_segments acts as a
	 * reference count to avoid race. The reference count should already be
	 * increased before this function is called (for example, in
	 * make_request()), so other bio sharing this stripe will not free the
	 * stripe. If a stripe is owned by one stripe, the stripe lock will
	 * protect it.
	 */
	spin_lock(&sh->lock);
	spin_lock_irq(&sh->stripe_lock);
	if (forwrite) {
		bip = &sh->dev[dd_idx].towrite;
		if (*bip == NULL)
			firstwrite = 1;
	} else
		bip = &sh->dev[dd_idx].toread;
	while (*bip && (*bip)->bi_sector < bi->bi_sector) {
		if ((*bip)->bi_sector + ((*bip)->bi_size >> 9) > bi->bi_sector)
			goto overlap;
		bip = & (*bip)->bi_next;
	}
	if (*bip && (*bip)->bi_sector < bi->bi_sector + ((bi->bi_size)>>9))
		goto overlap;

	BUG_ON(*bip && bi->bi_next && (*bip) != bi->bi_next);
	if (*bip)
		bi->bi_next = *bip;
	*bip = bi;
	raid5_inc_bi_active_stripes(bi);

	if (forwrite) {
		/* check if page is covered */
		sector_t sector = sh->dev[dd_idx].sector;
		for (bi=sh->dev[dd_idx].towrite;
		     sector < sh->dev[dd_idx].sector + STRIPE_SECTORS &&
			     bi && bi->bi_sector <= sector;
		     bi = r5_next_bio(bi, sh->dev[dd_idx].sector)) {
			if (bi->bi_sector + (bi->bi_size>>9) >= sector)
				sector = bi->bi_sector + (bi->bi_size>>9);
		}
		if (sector >= sh->dev[dd_idx].sector + STRIPE_SECTORS)
			set_bit(R5_OVERWRITE, &sh->dev[dd_idx].flags);
	}

	pr_debug("added bi b#%llu to stripe s#%llu, disk %d.\n",
		(unsigned long long)(*bip)->bi_sector,
		(unsigned long long)sh->sector, dd_idx);
	spin_unlock_irq(&sh->stripe_lock);
	spin_unlock(&sh->lock);

	if (conf->mddev->bitmap && firstwrite) {
		bitmap_startwrite(conf->mddev->bitmap, sh->sector,
				  STRIPE_SECTORS, 0);
		sh->bm_seq = conf->seq_flush+1;
		set_bit(STRIPE_BIT_DELAY, &sh->state);
	}
	return 1;

 overlap:
	set_bit(R5_Overlap, &sh->dev[dd_idx].flags);
	spin_unlock_irq(&sh->stripe_lock);
	spin_unlock(&sh->lock);
	return 0;
}