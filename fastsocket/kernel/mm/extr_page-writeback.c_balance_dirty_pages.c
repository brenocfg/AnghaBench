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
struct writeback_control {unsigned long nr_to_write; int range_cyclic; int /*<<< orphan*/ * older_than_this; int /*<<< orphan*/  sync_mode; } ;
struct backing_dev_info {int dirty_exceeded; int /*<<< orphan*/  wb; } ;
struct address_space {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_RECLAIMABLE ; 
 int /*<<< orphan*/  BDI_WRITEBACK ; 
 int HZ ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_start_background_writeback (struct backing_dev_info*) ; 
 long bdi_stat (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 int bdi_stat_error (struct backing_dev_info*) ; 
 long bdi_stat_sum (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dirty_limits (unsigned long*,unsigned long*,unsigned long*,struct backing_dev_info*) ; 
 unsigned long global_page_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_schedule_timeout (unsigned long) ; 
 scalar_t__ laptop_mode ; 
 int /*<<< orphan*/  trace_mm_balancedirty_writeout (unsigned long) ; 
 int /*<<< orphan*/  trace_wbc_balance_dirty_start (struct writeback_control*,struct backing_dev_info*) ; 
 int /*<<< orphan*/  trace_wbc_balance_dirty_wait (struct writeback_control*,struct backing_dev_info*) ; 
 int /*<<< orphan*/  trace_wbc_balance_dirty_written (struct writeback_control*,struct backing_dev_info*) ; 
 scalar_t__ writeback_in_progress (struct backing_dev_info*) ; 
 int /*<<< orphan*/  writeback_inodes_wb (int /*<<< orphan*/ *,struct writeback_control*) ; 

__attribute__((used)) static void balance_dirty_pages(struct address_space *mapping,
				unsigned long write_chunk)
{
	long nr_reclaimable, bdi_nr_reclaimable;
	long nr_writeback, bdi_nr_writeback;
	unsigned long background_thresh;
	unsigned long dirty_thresh;
	unsigned long bdi_thresh;
	unsigned long pages_written = 0;
	unsigned long pause = 1;

	struct backing_dev_info *bdi = mapping->backing_dev_info;

	for (;;) {
		struct writeback_control wbc = {
			.sync_mode	= WB_SYNC_NONE,
			.older_than_this = NULL,
			.nr_to_write	= write_chunk,
			.range_cyclic	= 1,
		};

		get_dirty_limits(&background_thresh, &dirty_thresh,
				&bdi_thresh, bdi);

		nr_reclaimable = global_page_state(NR_FILE_DIRTY) +
					global_page_state(NR_UNSTABLE_NFS);
		nr_writeback = global_page_state(NR_WRITEBACK);

		bdi_nr_reclaimable = bdi_stat(bdi, BDI_RECLAIMABLE);
		bdi_nr_writeback = bdi_stat(bdi, BDI_WRITEBACK);

		if (bdi_nr_reclaimable + bdi_nr_writeback <= bdi_thresh)
			break;

		/*
		 * Throttle it only when the background writeback cannot
		 * catch-up. This avoids (excessively) small writeouts
		 * when the bdi limits are ramping up.
		 */
		if (nr_reclaimable + nr_writeback <
				(background_thresh + dirty_thresh) / 2)
			break;

		if (!bdi->dirty_exceeded)
			bdi->dirty_exceeded = 1;

		/* Note: nr_reclaimable denotes nr_dirty + nr_unstable.
		 * Unstable writes are a feature of certain networked
		 * filesystems (i.e. NFS) in which data may have been
		 * written to the server's write cache, but has not yet
		 * been flushed to permanent storage.
		 * Only move pages to writeback if this bdi is over its
		 * threshold otherwise wait until the disk writes catch
		 * up.
		 */
		trace_wbc_balance_dirty_start(&wbc, bdi);
		if (bdi_nr_reclaimable > bdi_thresh) {
			writeback_inodes_wb(&bdi->wb, &wbc);
			pages_written += write_chunk - wbc.nr_to_write;
			trace_wbc_balance_dirty_written(&wbc, bdi);
			get_dirty_limits(&background_thresh, &dirty_thresh,
				       &bdi_thresh, bdi);
		}

		/*
		 * In order to avoid the stacked BDI deadlock we need
		 * to ensure we accurately count the 'dirty' pages when
		 * the threshold is low.
		 *
		 * Otherwise it would be possible to get thresh+n pages
		 * reported dirty, even though there are thresh-m pages
		 * actually dirty; with m+n sitting in the percpu
		 * deltas.
		 */
		if (bdi_thresh < 2*bdi_stat_error(bdi)) {
			bdi_nr_reclaimable = bdi_stat_sum(bdi, BDI_RECLAIMABLE);
			bdi_nr_writeback = bdi_stat_sum(bdi, BDI_WRITEBACK);
		} else if (bdi_nr_reclaimable) {
			bdi_nr_reclaimable = bdi_stat(bdi, BDI_RECLAIMABLE);
			bdi_nr_writeback = bdi_stat(bdi, BDI_WRITEBACK);
		}

		if (bdi_nr_reclaimable + bdi_nr_writeback <= bdi_thresh)
			break;
		if (pages_written >= write_chunk)
			break;		/* We've done our duty */

		trace_wbc_balance_dirty_wait(&wbc, bdi);
		__set_current_state(TASK_KILLABLE);
		io_schedule_timeout(pause);

		/*
		 * Increase the delay for each loop, up to our previous
		 * default of taking a 100ms nap.
		 */
		pause <<= 1;
		if (pause > HZ / 10)
			pause = HZ / 10;

		if (fatal_signal_pending(current))
			break;
	}

	if(pages_written) trace_mm_balancedirty_writeout(pages_written);
	if (bdi_nr_reclaimable + bdi_nr_writeback < bdi_thresh &&
			bdi->dirty_exceeded)
		bdi->dirty_exceeded = 0;

	if (writeback_in_progress(bdi))
		return;

	/*
	 * In laptop mode, we wait until hitting the higher threshold before
	 * starting background writeout, and then write out all the way down
	 * to the lower threshold.  So slow writers cause minimal disk activity.
	 *
	 * In normal mode, we start background writeout at the lower
	 * background_thresh, to keep the amount of dirty memory low.
	 */
	if ((laptop_mode && pages_written) ||
	    (!laptop_mode && ((global_page_state(NR_FILE_DIRTY)
			       + global_page_state(NR_UNSTABLE_NFS))
					  > background_thresh)))
		bdi_start_background_writeback(bdi);
}