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
struct wb_writeback_work {long nr_pages; int range_cyclic; int for_background; int /*<<< orphan*/  sync_mode; } ;
struct TYPE_2__ {scalar_t__ task; } ;
struct backing_dev_info {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  bdi_queue_work (struct backing_dev_info*,struct wb_writeback_work*) ; 
 struct wb_writeback_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_writeback_nowork (struct backing_dev_info*) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void
__bdi_start_writeback(struct backing_dev_info *bdi, long nr_pages,
		bool range_cyclic, bool for_background)
{
	struct wb_writeback_work *work;

	/*
	 * This is WB_SYNC_NONE writeback, so if allocation fails just
	 * wakeup the thread for old dirty data writeback
	 */
	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work) {
		if (bdi->wb.task) {
			trace_writeback_nowork(bdi);
			wake_up_process(bdi->wb.task);
		}
		return;
	}

	work->sync_mode	= WB_SYNC_NONE;
	work->nr_pages	= nr_pages;
	work->range_cyclic = range_cyclic;
	work->for_background = for_background;

	bdi_queue_work(bdi, work);
}