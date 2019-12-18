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
struct mapped_device {int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  wq; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 int /*<<< orphan*/  DMF_NOFLUSH_SUSPENDING ; 
 int /*<<< orphan*/  DMF_SUSPENDED ; 
 unsigned int DM_SUSPEND_LOCKFS_FLAG ; 
 unsigned int DM_SUSPEND_NOFLUSH_FLAG ; 
 int EINVAL ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_queue_flush (struct mapped_device*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_postsuspend_targets (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_presuspend_targets (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int dm_wait_for_completion (struct mapped_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int lock_fs (struct mapped_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_fs (struct mapped_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_suspend(struct mapped_device *md, unsigned suspend_flags)
{
	struct dm_table *map = NULL;
	int r = 0;
	int do_lockfs = suspend_flags & DM_SUSPEND_LOCKFS_FLAG ? 1 : 0;
	int noflush = suspend_flags & DM_SUSPEND_NOFLUSH_FLAG ? 1 : 0;

	mutex_lock(&md->suspend_lock);

	if (dm_suspended_md(md)) {
		r = -EINVAL;
		goto out_unlock;
	}

	map = dm_get_live_table(md);

	/*
	 * DMF_NOFLUSH_SUSPENDING must be set before presuspend.
	 * This flag is cleared before dm_suspend returns.
	 */
	if (noflush)
		set_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);

	/* This does not get reverted if there's an error later. */
	dm_table_presuspend_targets(map);

	/*
	 * Flush I/O to the device.
	 * Any I/O submitted after lock_fs() may not be flushed.
	 * noflush takes precedence over do_lockfs.
	 * (lock_fs() flushes I/Os and waits for them to complete.)
	 */
	if (!noflush && do_lockfs) {
		r = lock_fs(md);
		if (r)
			goto out;
	}

	/*
	 * Here we must make sure that no processes are submitting requests
	 * to target drivers i.e. no one may be executing
	 * __split_and_process_bio. This is called from dm_request and
	 * dm_wq_work.
	 *
	 * To get all processes out of __split_and_process_bio in dm_request,
	 * we take the write lock. To prevent any process from reentering
	 * __split_and_process_bio from dm_request and quiesce the thread
	 * (dm_wq_work), we set BMF_BLOCK_IO_FOR_SUSPEND and call
	 * flush_workqueue(md->wq).
	 */
	down_write(&md->io_lock);
	set_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	up_write(&md->io_lock);

	/*
	 * Stop md->queue before flushing md->wq in case request-based
	 * dm defers requests to md->wq from md->queue.
	 */
	if (dm_request_based(md))
		stop_queue(md->queue);

	flush_workqueue(md->wq);

	/*
	 * At this point no more requests are entering target request routines.
	 * We call dm_wait_for_completion to wait for all existing requests
	 * to finish.
	 */
	r = dm_wait_for_completion(md, TASK_INTERRUPTIBLE);

	down_write(&md->io_lock);
	if (noflush)
		clear_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);
	up_write(&md->io_lock);

	/* were we interrupted ? */
	if (r < 0) {
		dm_queue_flush(md);

		if (dm_request_based(md))
			start_queue(md->queue);

		unlock_fs(md);
		goto out; /* pushback list is already flushed, so skip flush */
	}

	/*
	 * If dm_wait_for_completion returned 0, the device is completely
	 * quiescent now. There is no request-processing activity. All new
	 * requests are being added to md->deferred list.
	 */

	set_bit(DMF_SUSPENDED, &md->flags);

	dm_table_postsuspend_targets(map);

out:
	dm_table_put(map);

out_unlock:
	mutex_unlock(&md->suspend_lock);
	return r;
}