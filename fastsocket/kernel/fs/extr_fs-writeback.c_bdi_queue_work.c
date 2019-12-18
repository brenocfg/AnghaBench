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
struct wb_writeback_work {int /*<<< orphan*/  list; } ;
struct bdi_writeback {scalar_t__ task; } ;
struct backing_dev_info {struct bdi_writeback wb; int /*<<< orphan*/  wb_list; int /*<<< orphan*/  wb_lock; int /*<<< orphan*/  work_list; } ;
struct TYPE_3__ {scalar_t__ task; } ;
struct TYPE_4__ {TYPE_1__ wb; } ;

/* Variables and functions */
 TYPE_2__ default_backing_dev_info ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_writeback_nothread (struct backing_dev_info*,struct wb_writeback_work*) ; 
 int /*<<< orphan*/  trace_writeback_queue (struct backing_dev_info*,struct wb_writeback_work*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void bdi_queue_work(struct backing_dev_info *bdi,
		struct wb_writeback_work *work)
{
	trace_writeback_queue(bdi, work);

	spin_lock(&bdi->wb_lock);
	list_add_tail(&work->list, &bdi->work_list);
	spin_unlock(&bdi->wb_lock);

	/*
	 * If the default thread isn't there, make sure we add it. When
	 * it gets created and wakes up, we'll run this work.
	 */
	if (unlikely(list_empty_careful(&bdi->wb_list))) {
		 trace_writeback_nothread(bdi, work);
		wake_up_process(default_backing_dev_info.wb.task);
	} else {
		struct bdi_writeback *wb = &bdi->wb;

		if (wb->task)
			wake_up_process(wb->task);
	}
}