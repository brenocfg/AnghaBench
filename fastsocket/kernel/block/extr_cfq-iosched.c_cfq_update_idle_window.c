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
struct cfq_queue {int* queued; TYPE_1__* next_rq; } ;
struct cfq_io_context {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; TYPE_2__* ioc; } ;
struct cfq_data {scalar_t__ cfq_slice_idle; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_tasks; } ;
struct TYPE_3__ {int cmd_flags; } ;

/* Variables and functions */
 scalar_t__ CFQQ_SEEKY (struct cfq_queue*) ; 
 int REQ_NOIDLE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_cfqq_deep (struct cfq_queue*) ; 
 int cfq_cfqq_idle_window (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_sync (struct cfq_queue*) ; 
 scalar_t__ cfq_class_idle (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_idle_window (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,int) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_deep (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_idle_window (struct cfq_queue*) ; 
 scalar_t__ sample_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cfq_update_idle_window(struct cfq_data *cfqd, struct cfq_queue *cfqq,
		       struct cfq_io_context *cic)
{
	int old_idle, enable_idle;

	/*
	 * Don't idle for async or idle io prio class
	 */
	if (!cfq_cfqq_sync(cfqq) || cfq_class_idle(cfqq))
		return;

	enable_idle = old_idle = cfq_cfqq_idle_window(cfqq);

	if (cfqq->queued[0] + cfqq->queued[1] >= 4)
		cfq_mark_cfqq_deep(cfqq);

	if (cfqq->next_rq && (cfqq->next_rq->cmd_flags & REQ_NOIDLE))
		enable_idle = 0;
	else if (!atomic_read(&cic->ioc->nr_tasks) || !cfqd->cfq_slice_idle ||
	    (!cfq_cfqq_deep(cfqq) && CFQQ_SEEKY(cfqq)))
		enable_idle = 0;
	else if (sample_valid(cic->ttime_samples)) {
		if (cic->ttime_mean > cfqd->cfq_slice_idle)
			enable_idle = 0;
		else
			enable_idle = 1;
	}

	if (old_idle != enable_idle) {
		cfq_log_cfqq(cfqd, cfqq, "idle=%d", enable_idle);
		if (enable_idle)
			cfq_mark_cfqq_idle_window(cfqq);
		else
			cfq_clear_cfqq_idle_window(cfqq);
	}
}