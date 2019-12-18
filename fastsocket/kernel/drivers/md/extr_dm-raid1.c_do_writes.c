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
struct bio_list {int head; } ;
struct mirror_set {int log_failure; int leg_failure; int /*<<< orphan*/  lock; struct bio_list failures; int /*<<< orphan*/  rh; struct bio_list writes; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct bio {int bi_rw; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_2__ {scalar_t__ (* is_remote_recovering ) (struct dm_dirty_log*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int BIO_FLUSH ; 
#define  DM_RH_CLEAN 131 
#define  DM_RH_DIRTY 130 
#define  DM_RH_NOSYNC 129 
#define  DM_RH_RECOVERING 128 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  delayed_wake (struct mirror_set*) ; 
 int /*<<< orphan*/  dm_rh_bio_to_region (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  dm_rh_delay (int /*<<< orphan*/ ,struct bio*) ; 
 struct dm_dirty_log* dm_rh_dirty_log (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_rh_flush (int /*<<< orphan*/ ) ; 
 int dm_rh_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_rh_inc_pending (int /*<<< orphan*/ ,struct bio_list*) ; 
 int /*<<< orphan*/  do_write (struct mirror_set*,struct bio*) ; 
 scalar_t__ errors_handled (struct mirror_set*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  get_default_mirror (struct mirror_set*) ; 
 int /*<<< orphan*/  map_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dm_dirty_log*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wakeup_mirrord (struct mirror_set*) ; 

__attribute__((used)) static void do_writes(struct mirror_set *ms, struct bio_list *writes)
{
	int state;
	struct bio *bio;
	struct bio_list sync, nosync, recover, *this_list = NULL;
	struct bio_list requeue;
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	region_t region;

	if (!writes->head)
		return;

	/*
	 * Classify each write.
	 */
	bio_list_init(&sync);
	bio_list_init(&nosync);
	bio_list_init(&recover);
	bio_list_init(&requeue);

	while ((bio = bio_list_pop(writes))) {
		if ((bio->bi_rw & BIO_FLUSH) ||
		    (bio->bi_rw & BIO_DISCARD)) {
			bio_list_add(&sync, bio);
			continue;
		}

		region = dm_rh_bio_to_region(ms->rh, bio);

		if (log->type->is_remote_recovering &&
		    log->type->is_remote_recovering(log, region)) {
			bio_list_add(&requeue, bio);
			continue;
		}

		state = dm_rh_get_state(ms->rh, region, 1);
		switch (state) {
		case DM_RH_CLEAN:
		case DM_RH_DIRTY:
			this_list = &sync;
			break;

		case DM_RH_NOSYNC:
			this_list = &nosync;
			break;

		case DM_RH_RECOVERING:
			this_list = &recover;
			break;
		}

		bio_list_add(this_list, bio);
	}

	/*
	 * Add bios that are delayed due to remote recovery
	 * back on to the write queue
	 */
	if (unlikely(requeue.head)) {
		spin_lock_irq(&ms->lock);
		bio_list_merge(&ms->writes, &requeue);
		spin_unlock_irq(&ms->lock);
		delayed_wake(ms);
	}

	/*
	 * Increment the pending counts for any regions that will
	 * be written to (writes to recover regions are going to
	 * be delayed).
	 */
	dm_rh_inc_pending(ms->rh, &sync);
	dm_rh_inc_pending(ms->rh, &nosync);

	/*
	 * If the flush fails on a previous call and succeeds here,
	 * we must not reset the log_failure variable.  We need
	 * userspace interaction to do that.
	 */
	ms->log_failure = dm_rh_flush(ms->rh) ? 1 : ms->log_failure;

	/*
	 * Dispatch io.
	 */
	if (unlikely(ms->log_failure) && errors_handled(ms)) {
		spin_lock_irq(&ms->lock);
		bio_list_merge(&ms->failures, &sync);
		spin_unlock_irq(&ms->lock);
		wakeup_mirrord(ms);
	} else
		while ((bio = bio_list_pop(&sync)))
			do_write(ms, bio);

	while ((bio = bio_list_pop(&recover)))
		dm_rh_delay(ms->rh, bio);

	while ((bio = bio_list_pop(&nosync))) {
		if (unlikely(ms->leg_failure) && errors_handled(ms)) {
			spin_lock_irq(&ms->lock);
			bio_list_add(&ms->failures, bio);
			spin_unlock_irq(&ms->lock);
			wakeup_mirrord(ms);
		} else {
			map_bio(get_default_mirror(ms), bio);
			generic_make_request(bio);
		}
	}
}