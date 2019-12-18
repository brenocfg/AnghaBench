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
struct wb_writeback_work {scalar_t__ done; int /*<<< orphan*/  sync_mode; } ;
struct bdi_writeback {struct backing_dev_info* bdi; } ;
struct backing_dev_info {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_writeback_running ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 struct wb_writeback_work* get_next_work_item (struct backing_dev_info*,struct bdi_writeback*) ; 
 int /*<<< orphan*/  kfree (struct wb_writeback_work*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_background_writeout (long) ; 
 int /*<<< orphan*/  trace_writeback_exec (struct backing_dev_info*,struct wb_writeback_work*) ; 
 scalar_t__ wb_check_old_data_flush (struct bdi_writeback*) ; 
 scalar_t__ wb_writeback (struct bdi_writeback*,struct wb_writeback_work*) ; 

long wb_do_writeback(struct bdi_writeback *wb, int force_wait)
{
	struct backing_dev_info *bdi = wb->bdi;
	struct wb_writeback_work *work;
	long wrote = 0;

	set_bit(BDI_writeback_running, &wb->bdi->state);
	while ((work = get_next_work_item(bdi, wb)) != NULL) {
		/*
		 * Override sync mode, in case we must wait for completion
		 * because this thread is exiting now.
		 */
		if (force_wait)
			work->sync_mode = WB_SYNC_ALL;

		trace_writeback_exec(bdi, work);

		wrote += wb_writeback(wb, work);

		/*
		 * Notify the caller of completion if this is a synchronous
		 * work item, otherwise just free it.
		 */
		if (work->done)
			complete(work->done);
		else
			kfree(work);
	}
	trace_mm_background_writeout(wrote);

	/*
	 * Check for periodic writeback, kupdated() style
	 */
	wrote += wb_check_old_data_flush(wb);
	clear_bit(BDI_writeback_running, &wb->bdi->state);

	return wrote;
}