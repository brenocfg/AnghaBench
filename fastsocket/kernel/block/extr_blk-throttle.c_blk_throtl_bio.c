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
struct throtl_grp {scalar_t__* nr_queued; int /*<<< orphan*/ * iops; int /*<<< orphan*/ * io_disp; int /*<<< orphan*/ * bps; int /*<<< orphan*/ * bytes_disp; int /*<<< orphan*/  blkg; } ;
struct throtl_data {int dummy; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; struct throtl_data* td; } ;
struct blkio_cgroup {int dummy; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_size; } ;

/* Variables and functions */
 int BIO_RW_THROTTLED ; 
 int READ ; 
 int REQ_SYNC ; 
 size_t WRITE ; 
 int bio_data_dir (struct bio*) ; 
 scalar_t__ bio_rw_flagged (struct bio*,int) ; 
 int /*<<< orphan*/  blkiocg_update_dispatch_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct blkio_cgroup* task_blkio_cgroup (int /*<<< orphan*/ ) ; 
 scalar_t__ tg_may_dispatch (struct throtl_data*,struct throtl_grp*,struct bio*,int /*<<< orphan*/ *) ; 
 scalar_t__ tg_no_rule_group (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  tg_update_disptime (struct throtl_data*,struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_add_bio_tg (struct throtl_data*,struct throtl_grp*,struct bio*) ; 
 int /*<<< orphan*/  throtl_charge_bio (struct throtl_grp*,struct bio*) ; 
 struct throtl_grp* throtl_find_tg (struct throtl_data*,struct blkio_cgroup*) ; 
 struct throtl_grp* throtl_get_tg (struct throtl_data*) ; 
 int /*<<< orphan*/  throtl_log_tg (struct throtl_data*,struct throtl_grp*,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  throtl_schedule_next_dispatch (struct throtl_data*) ; 
 int /*<<< orphan*/  throtl_tg_fill_dev_details (struct throtl_data*,struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_trim_slice (struct throtl_data*,struct throtl_grp*,int) ; 
 scalar_t__ unlikely (int) ; 

bool blk_throtl_bio(struct request_queue *q, struct bio *bio)
{
	struct throtl_data *td = q->td;
	struct throtl_grp *tg;
	bool rw = bio_data_dir(bio), update_disptime = true;
	struct blkio_cgroup *blkcg;
	bool throttled = false;

	if (bio_rw_flagged(bio, BIO_RW_THROTTLED)) {
		bio->bi_rw &= ~(1 << BIO_RW_THROTTLED);
		goto out;
	}

	/*
	 * A throtl_grp pointer retrieved under rcu can be used to access
	 * basic fields like stats and io rates. If a group has no rules,
	 * just update the dispatch stats in lockless manner and return.
	 */

	rcu_read_lock();
	blkcg = task_blkio_cgroup(current);
	tg = throtl_find_tg(td, blkcg);
	if (tg) {
		throtl_tg_fill_dev_details(td, tg);

		if (tg_no_rule_group(tg, rw)) {
			blkiocg_update_dispatch_stats(&tg->blkg, bio->bi_size,
					rw, bio->bi_rw & REQ_SYNC);
			rcu_read_unlock();
			goto out;
		}
	}
	rcu_read_unlock();

	/*
	 * Either group has not been allocated yet or it is not an unlimited
	 * IO group
	 */
	spin_lock_irq(q->queue_lock);
	tg = throtl_get_tg(td);
	if (unlikely(!tg))
		goto out_unlock;

	if (tg->nr_queued[rw]) {
		/*
		 * There is already another bio queued in same dir. No
		 * need to update dispatch time.
		 */
		update_disptime = false;
		goto queue_bio;

	}

	/* Bio is with-in rate limit of group */
	if (tg_may_dispatch(td, tg, bio, NULL)) {
		throtl_charge_bio(tg, bio);

		/*
		 * We need to trim slice even when bios are not being queued
		 * otherwise it might happen that a bio is not queued for
		 * a long time and slice keeps on extending and trim is not
		 * called for a long time. Now if limits are reduced suddenly
		 * we take into account all the IO dispatched so far at new
		 * low rate and * newly queued IO gets a really long dispatch
		 * time.
		 *
		 * So keep on trimming slice even if bio is not queued.
		 */
		throtl_trim_slice(td, tg, rw);
		goto out_unlock;
	}

queue_bio:
	throtl_log_tg(td, tg, "[%c] bio. bdisp=%u sz=%u bps=%llu"
			" iodisp=%u iops=%u queued=%d/%d",
			rw == READ ? 'R' : 'W',
			tg->bytes_disp[rw], bio->bi_size, tg->bps[rw],
			tg->io_disp[rw], tg->iops[rw],
			tg->nr_queued[READ], tg->nr_queued[WRITE]);

	throtl_add_bio_tg(q->td, tg, bio);
	throttled = true;

	if (update_disptime) {
		tg_update_disptime(td, tg);
		throtl_schedule_next_dispatch(td);
	}

out_unlock:
	spin_unlock_irq(q->queue_lock);
out:
	return throttled;
}