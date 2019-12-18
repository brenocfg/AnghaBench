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
struct stripe_head {int /*<<< orphan*/  state; } ;
struct r5conf {scalar_t__ reshape_progress; int reshape_safe; int /*<<< orphan*/  wait_for_overlap; int /*<<< orphan*/  preread_active_stripes; int /*<<< orphan*/  device_lock; } ;
struct mddev {scalar_t__ reshape_position; int suspend_lo; int suspend_hi; scalar_t__ reshape_backwards; struct r5conf* private; } ;
struct bio {int bi_rw; int bi_sector; int bi_size; int bi_phys_segments; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/ * bi_next; } ;
typedef  int sector_t ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int BIO_FLUSH ; 
 int /*<<< orphan*/  BIO_RW_SYNCIO ; 
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ MaxSector ; 
 int const READ ; 
 int RWA_MASK ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 scalar_t__ STRIPE_SECTORS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int const WRITE ; 
 int /*<<< orphan*/  add_stripe_bio (struct stripe_head*,struct bio*,int,int const) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_rw_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ chunk_aligned_read (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 struct stripe_head* get_active_stripe (struct r5conf*,int,int,int,int /*<<< orphan*/ ) ; 
 int make_discard_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  md_raid5_unplug_device (struct r5conf*) ; 
 int /*<<< orphan*/  md_write_end (struct mddev*) ; 
 int /*<<< orphan*/  md_write_start (struct mddev*,struct bio*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int raid5_compute_sector (struct r5conf*,int,int,int*,int /*<<< orphan*/ *) ; 
 int raid5_dec_bi_active_stripes (struct bio*) ; 
 int /*<<< orphan*/  release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_bio_complete (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  w ; 

__attribute__((used)) static int make_request(struct mddev *mddev, struct bio * bi)
{
	struct r5conf *conf = mddev->private;
	int dd_idx;
	sector_t new_sector;
	sector_t logical_sector, last_sector;
	struct stripe_head *sh;
	const int rw = bio_data_dir(bi);
	int remaining;

	if (unlikely(bi->bi_rw & BIO_FLUSH)) {
		md_flush_request(mddev, bi);
		return 0;
	}

	md_write_start(mddev, bi);

	if (rw == READ &&
	     mddev->reshape_position == MaxSector &&
	     chunk_aligned_read(mddev,bi))
		return 0;

	if (unlikely(bi->bi_rw & BIO_DISCARD)) {
		return make_discard_request(mddev, bi);
	}

	logical_sector = bi->bi_sector & ~((sector_t)STRIPE_SECTORS-1);
	last_sector = bi->bi_sector + (bi->bi_size>>9);
	bi->bi_next = NULL;
	bi->bi_phys_segments = 1;	/* over-loaded to count active stripes */

	for (;logical_sector < last_sector; logical_sector += STRIPE_SECTORS) {
		DEFINE_WAIT(w);
		int previous;

	retry:
		previous = 0;
		prepare_to_wait(&conf->wait_for_overlap, &w, TASK_UNINTERRUPTIBLE);
		if (unlikely(conf->reshape_progress != MaxSector)) {
			/* spinlock is needed as reshape_progress may be
			 * 64bit on a 32bit platform, and so it might be
			 * possible to see a half-updated value
			 * Ofcourse reshape_progress could change after
			 * the lock is dropped, so once we get a reference
			 * to the stripe that we think it is, we will have
			 * to check again.
			 */
			spin_lock_irq(&conf->device_lock);
			if (mddev->reshape_backwards
			    ? logical_sector < conf->reshape_progress
			    : logical_sector >= conf->reshape_progress) {
				previous = 1;
			} else {
				if (mddev->reshape_backwards
				    ? logical_sector < conf->reshape_safe
				    : logical_sector >= conf->reshape_safe) {
					spin_unlock_irq(&conf->device_lock);
					schedule();
					goto retry;
				}
			}
			spin_unlock_irq(&conf->device_lock);
		}

		new_sector = raid5_compute_sector(conf, logical_sector,
						  previous,
						  &dd_idx, NULL);
		pr_debug("raid456: make_request, sector %llu logical %llu\n",
			(unsigned long long)new_sector, 
			(unsigned long long)logical_sector);

		sh = get_active_stripe(conf, new_sector, previous,
				       (bi->bi_rw&RWA_MASK), 0);
		if (sh) {
			if (unlikely(previous)) {
				/* expansion might have moved on while waiting for a
				 * stripe, so we must do the range check again.
				 * Expansion could still move past after this
				 * test, but as we are holding a reference to
				 * 'sh', we know that if that happens,
				 *  STRIPE_EXPANDING will get set and the expansion
				 * won't proceed until we finish with the stripe.
				 */
				int must_retry = 0;
				spin_lock_irq(&conf->device_lock);
				if (mddev->reshape_backwards
				    ? logical_sector >= conf->reshape_progress
				    : logical_sector < conf->reshape_progress)
					/* mismatch, need to try again */
					must_retry = 1;
				spin_unlock_irq(&conf->device_lock);
				if (must_retry) {
					release_stripe(sh);
					schedule();
					goto retry;
				}
			}

			if (rw == WRITE &&
			    logical_sector >= mddev->suspend_lo &&
			    logical_sector < mddev->suspend_hi) {
				release_stripe(sh);
				/* As the suspend_* range is controlled by
				 * userspace, we want an interruptible
				 * wait.
				 */
				flush_signals(current);
				prepare_to_wait(&conf->wait_for_overlap,
						&w, TASK_INTERRUPTIBLE);
				if (logical_sector >= mddev->suspend_lo &&
				    logical_sector < mddev->suspend_hi)
					schedule();
				goto retry;
			}

			if (test_bit(STRIPE_EXPANDING, &sh->state) ||
			    !add_stripe_bio(sh, bi, dd_idx, rw)) {
				/* Stripe is busy expanding or
				 * add failed due to overlap.  Flush everything
				 * and wait a while
				 */
				md_raid5_unplug_device(conf);
				release_stripe(sh);
				schedule();
				goto retry;
			}
			finish_wait(&conf->wait_for_overlap, &w);
			set_bit(STRIPE_HANDLE, &sh->state);
			clear_bit(STRIPE_DELAYED, &sh->state);
			if (bio_rw_flagged(bi, BIO_RW_SYNCIO) &&
			    !test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
				atomic_inc(&conf->preread_active_stripes);
			release_stripe(sh);
		} else {
			/* cannot get stripe for read-ahead, just give-up */
			clear_bit(BIO_UPTODATE, &bi->bi_flags);
			finish_wait(&conf->wait_for_overlap, &w);
			break;
		}
			
	}

	remaining = raid5_dec_bi_active_stripes(bi);
	if (remaining == 0) {

		if ( rw == WRITE )
			md_write_end(mddev);

		trace_block_bio_complete(bdev_get_queue(bi->bi_bdev),
					 bi);
		bio_endio(bi, 0);
	}

	return 0;
}