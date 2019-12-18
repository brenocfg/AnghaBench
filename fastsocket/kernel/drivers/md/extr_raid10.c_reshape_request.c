#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int chunk_mask; } ;
struct r10conf {void* reshape_progress; int reshape_safe; int offset_diff; int copies; TYPE_1__* mirrors; TYPE_4__ geo; int /*<<< orphan*/  r10buf_pool; scalar_t__ reshape_checkpoint; TYPE_4__ prev; } ;
struct r10bio {int sector; scalar_t__ state; int sectors; size_t read_slot; int /*<<< orphan*/  remaining; TYPE_3__* devs; struct bio* master_bio; struct mddev* mddev; } ;
struct page {int dummy; } ;
struct mddev {int curr_resync_completed; int reshape_position; scalar_t__ flags; scalar_t__ recovery; scalar_t__ reshape_backwards; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  thread; int /*<<< orphan*/  kobj; struct r10conf* private; } ;
struct md_rdev {scalar_t__ flags; scalar_t__ new_data_offset; int /*<<< orphan*/  bdev; scalar_t__ data_offset; } ;
struct bio {int bi_flags; int bi_size; struct bio* bi_next; int /*<<< orphan*/  bi_bdev; scalar_t__ bi_vcnt; TYPE_2__* bi_io_vec; scalar_t__ bi_idx; int /*<<< orphan*/  bi_rw; int /*<<< orphan*/  bi_end_io; struct r10bio* bi_private; scalar_t__ bi_sector; } ;
typedef  int sector_t ;
struct TYPE_9__ {size_t devnum; struct bio* bio; scalar_t__ addr; struct bio* repl_bio; } ;
struct TYPE_8__ {struct page* bv_page; } ;
struct TYPE_7__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int BIO_POOL_MASK ; 
 int BIO_SEG_VALID ; 
 int BIO_UPTODATE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int HZ ; 
 int /*<<< orphan*/  MD_CHANGE_DEVS ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  R10BIO_IsReshape ; 
 int /*<<< orphan*/  R10BIO_Previous ; 
 int /*<<< orphan*/  READ ; 
 int RESYNC_BLOCK_SIZE ; 
 int /*<<< orphan*/  RESYNC_PAGES ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  __raid10_find_phys (TYPE_4__*,struct r10bio*) ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc_mddev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mddev*) ; 
 int /*<<< orphan*/  end_reshape_write ; 
 int /*<<< orphan*/  end_sync_read ; 
 int first_dev_address (int,TYPE_4__*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 int last_dev_address (int,TYPE_4__*) ; 
 int /*<<< orphan*/  md_sync_acct (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 struct r10bio* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* raid10_size (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise_barrier (struct r10conf*,int) ; 
 struct md_rdev* read_balance (struct r10conf*,struct r10bio*,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wait_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sector_t reshape_request(struct mddev *mddev, sector_t sector_nr,
				int *skipped)
{
	/* We simply copy at most one chunk (smallest of old and new)
	 * at a time, possibly less if that exceeds RESYNC_PAGES,
	 * or we hit a bad block or something.
	 * This might mean we pause for normal IO in the middle of
	 * a chunk, but that is not a problem was mddev->reshape_position
	 * can record any location.
	 *
	 * If we will want to write to a location that isn't
	 * yet recorded as 'safe' (i.e. in metadata on disk) then
	 * we need to flush all reshape requests and update the metadata.
	 *
	 * When reshaping forwards (e.g. to more devices), we interpret
	 * 'safe' as the earliest block which might not have been copied
	 * down yet.  We divide this by previous stripe size and multiply
	 * by previous stripe length to get lowest device offset that we
	 * cannot write to yet.
	 * We interpret 'sector_nr' as an address that we want to write to.
	 * From this we use last_device_address() to find where we might
	 * write to, and first_device_address on the  'safe' position.
	 * If this 'next' write position is after the 'safe' position,
	 * we must update the metadata to increase the 'safe' position.
	 *
	 * When reshaping backwards, we round in the opposite direction
	 * and perform the reverse test:  next write position must not be
	 * less than current safe position.
	 *
	 * In all this the minimum difference in data offsets
	 * (conf->offset_diff - always positive) allows a bit of slack,
	 * so next can be after 'safe', but not by more than offset_disk
	 *
	 * We need to prepare all the bios here before we start any IO
	 * to ensure the size we choose is acceptable to all devices.
	 * The means one for each copy for write-out and an extra one for
	 * read-in.
	 * We store the read-in bio in ->master_bio and the others in
	 * ->devs[x].bio and ->devs[x].repl_bio.
	 */
	struct r10conf *conf = mddev->private;
	struct r10bio *r10_bio;
	sector_t next, safe, last;
	int max_sectors;
	int nr_sectors;
	int s;
	struct md_rdev *rdev;
	int need_flush = 0;
	struct bio *blist;
	struct bio *bio, *read_bio;
	int sectors_done = 0;

	if (sector_nr == 0) {
		/* If restarting in the middle, skip the initial sectors */
		if (mddev->reshape_backwards &&
		    conf->reshape_progress < raid10_size(mddev, 0, 0)) {
			sector_nr = (raid10_size(mddev, 0, 0)
				     - conf->reshape_progress);
		} else if (!mddev->reshape_backwards &&
			   conf->reshape_progress > 0)
			sector_nr = conf->reshape_progress;
		if (sector_nr) {
			mddev->curr_resync_completed = sector_nr;
			sysfs_notify(&mddev->kobj, NULL, "sync_completed");
			*skipped = 1;
			return sector_nr;
		}
	}

	/* We don't use sector_nr to track where we are up to
	 * as that doesn't work well for ->reshape_backwards.
	 * So just use ->reshape_progress.
	 */
	if (mddev->reshape_backwards) {
		/* 'next' is the earliest device address that we might
		 * write to for this chunk in the new layout
		 */
		next = first_dev_address(conf->reshape_progress - 1,
					 &conf->geo);

		/* 'safe' is the last device address that we might read from
		 * in the old layout after a restart
		 */
		safe = last_dev_address(conf->reshape_safe - 1,
					&conf->prev);

		if (next + conf->offset_diff < safe)
			need_flush = 1;

		last = conf->reshape_progress - 1;
		sector_nr = last & ~(sector_t)(conf->geo.chunk_mask
					       & conf->prev.chunk_mask);
		if (sector_nr + RESYNC_BLOCK_SIZE/512 < last)
			sector_nr = last + 1 - RESYNC_BLOCK_SIZE/512;
	} else {
		/* 'next' is after the last device address that we
		 * might write to for this chunk in the new layout
		 */
		next = last_dev_address(conf->reshape_progress, &conf->geo);

		/* 'safe' is the earliest device address that we might
		 * read from in the old layout after a restart
		 */
		safe = first_dev_address(conf->reshape_safe, &conf->prev);

		/* Need to update metadata if 'next' might be beyond 'safe'
		 * as that would possibly corrupt data
		 */
		if (next > safe + conf->offset_diff)
			need_flush = 1;

		sector_nr = conf->reshape_progress;
		last  = sector_nr | (conf->geo.chunk_mask
				     & conf->prev.chunk_mask);

		if (sector_nr + RESYNC_BLOCK_SIZE/512 <= last)
			last = sector_nr + RESYNC_BLOCK_SIZE/512 - 1;
	}

	if (need_flush ||
	    time_after(jiffies, conf->reshape_checkpoint + 10*HZ)) {
		/* Need to update reshape_position in metadata */
		wait_barrier(conf);
		mddev->reshape_position = conf->reshape_progress;
		if (mddev->reshape_backwards)
			mddev->curr_resync_completed = raid10_size(mddev, 0, 0)
				- conf->reshape_progress;
		else
			mddev->curr_resync_completed = conf->reshape_progress;
		conf->reshape_checkpoint = jiffies;
		set_bit(MD_CHANGE_DEVS, &mddev->flags);
		md_wakeup_thread(mddev->thread);
		wait_event(mddev->sb_wait, mddev->flags == 0 ||
			   kthread_should_stop());
		conf->reshape_safe = mddev->reshape_position;
		allow_barrier(conf);
	}

read_more:
	/* Now schedule reads for blocks from sector_nr to last */
	r10_bio = mempool_alloc(conf->r10buf_pool, GFP_NOIO);
	raise_barrier(conf, sectors_done != 0);
	atomic_set(&r10_bio->remaining, 0);
	r10_bio->mddev = mddev;
	r10_bio->sector = sector_nr;
	set_bit(R10BIO_IsReshape, &r10_bio->state);
	r10_bio->sectors = last - sector_nr + 1;
	rdev = read_balance(conf, r10_bio, &max_sectors);
	BUG_ON(!test_bit(R10BIO_Previous, &r10_bio->state));

	if (!rdev) {
		/* Cannot read from here, so need to record bad blocks
		 * on all the target devices.
		 */
		// FIXME
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		return sectors_done;
	}

	read_bio = bio_alloc_mddev(GFP_KERNEL, RESYNC_PAGES, mddev);

	read_bio->bi_bdev = rdev->bdev;
	read_bio->bi_sector = (r10_bio->devs[r10_bio->read_slot].addr
			       + rdev->data_offset);
	read_bio->bi_private = r10_bio;
	read_bio->bi_end_io = end_sync_read;
	read_bio->bi_rw = READ;
	read_bio->bi_flags &= ~(BIO_POOL_MASK - 1);
	read_bio->bi_flags |= 1 << BIO_UPTODATE;
	read_bio->bi_vcnt = 0;
	read_bio->bi_idx = 0;
	read_bio->bi_size = 0;
	r10_bio->master_bio = read_bio;
	r10_bio->read_slot = r10_bio->devs[r10_bio->read_slot].devnum;

	/* Now find the locations in the new layout */
	__raid10_find_phys(&conf->geo, r10_bio);

	blist = read_bio;
	read_bio->bi_next = NULL;

	for (s = 0; s < conf->copies*2; s++) {
		struct bio *b;
		int d = r10_bio->devs[s/2].devnum;
		struct md_rdev *rdev2;
		if (s&1) {
			rdev2 = conf->mirrors[d].replacement;
			b = r10_bio->devs[s/2].repl_bio;
		} else {
			rdev2 = conf->mirrors[d].rdev;
			b = r10_bio->devs[s/2].bio;
		}
		if (!rdev2 || test_bit(Faulty, &rdev2->flags))
			continue;
		b->bi_bdev = rdev2->bdev;
		b->bi_sector = r10_bio->devs[s/2].addr + rdev2->new_data_offset;
		b->bi_private = r10_bio;
		b->bi_end_io = end_reshape_write;
		b->bi_rw = WRITE;
		b->bi_flags &= ~(BIO_POOL_MASK - 1);
		b->bi_flags |= 1 << BIO_UPTODATE;
		b->bi_next = blist;
		b->bi_vcnt = 0;
		b->bi_idx = 0;
		b->bi_size = 0;
		blist = b;
	}

	/* Now add as many pages as possible to all of these bios. */

	nr_sectors = 0;
	for (s = 0 ; s < max_sectors; s += PAGE_SIZE >> 9) {
		struct page *page = r10_bio->devs[0].bio->bi_io_vec[s/(PAGE_SIZE>>9)].bv_page;
		int len = (max_sectors - s) << 9;
		if (len > PAGE_SIZE)
			len = PAGE_SIZE;
		for (bio = blist; bio ; bio = bio->bi_next) {
			struct bio *bio2;
			if (bio_add_page(bio, page, len, 0))
				continue;

			/* Didn't fit, must stop */
			for (bio2 = blist;
			     bio2 && bio2 != bio;
			     bio2 = bio2->bi_next) {
				/* Remove last page from this bio */
				bio2->bi_vcnt--;
				bio2->bi_size -= len;
				bio2->bi_flags &= ~(1<<BIO_SEG_VALID);
			}
			goto bio_full;
		}
		sector_nr += len >> 9;
		nr_sectors += len >> 9;
	}
bio_full:
	r10_bio->sectors = nr_sectors;

	/* Now submit the read */
	md_sync_acct(read_bio->bi_bdev, r10_bio->sectors);
	atomic_inc(&r10_bio->remaining);
	read_bio->bi_next = NULL;
	generic_make_request(read_bio);
	sector_nr += nr_sectors;
	sectors_done += nr_sectors;
	if (sector_nr <= last)
		goto read_more;

	/* Now that we have done the whole section we can
	 * update reshape_progress
	 */
	if (mddev->reshape_backwards)
		conf->reshape_progress -= sectors_done;
	else
		conf->reshape_progress += sectors_done;

	return sectors_done;
}