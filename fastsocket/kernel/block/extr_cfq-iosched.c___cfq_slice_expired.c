#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cfq_queue {int slice_resid; int slice_end; TYPE_3__* cfqg; int /*<<< orphan*/  sort_list; } ;
struct TYPE_4__ {int /*<<< orphan*/ * active; } ;
struct cfq_data {TYPE_2__* active_cic; TYPE_1__ grp_service_tree; struct cfq_queue* active_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  rb_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 scalar_t__ CFQQ_SEEKY (struct cfq_queue*) ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 scalar_t__ cfq_cfqq_coop (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_slice_new (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_wait_request (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_wait_busy (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_wait_request (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_del_cfqq_rr (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_del_timer (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_group_served (struct cfq_data*,TYPE_3__*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,int) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_split_coop (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_resort_rr_list (struct cfq_data*,struct cfq_queue*) ; 
 int jiffies ; 
 int /*<<< orphan*/  put_io_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__cfq_slice_expired(struct cfq_data *cfqd, struct cfq_queue *cfqq,
		    bool timed_out)
{
	cfq_log_cfqq(cfqd, cfqq, "slice expired t=%d", timed_out);

	if (cfq_cfqq_wait_request(cfqq))
		cfq_del_timer(cfqd, cfqq);

	cfq_clear_cfqq_wait_request(cfqq);
	cfq_clear_cfqq_wait_busy(cfqq);

	/*
	 * If this cfqq is shared between multiple processes, check to
	 * make sure that those processes are still issuing I/Os within
	 * the mean seek distance.  If not, it may be time to break the
	 * queues apart again.
	 */
	if (cfq_cfqq_coop(cfqq) && CFQQ_SEEKY(cfqq))
		cfq_mark_cfqq_split_coop(cfqq);

	/*
	 * store what was left of this slice, if the queue idled/timed out
	 */
	if (timed_out && !cfq_cfqq_slice_new(cfqq)) {
		cfqq->slice_resid = cfqq->slice_end - jiffies;
		cfq_log_cfqq(cfqd, cfqq, "resid=%ld", cfqq->slice_resid);
	}

	cfq_group_served(cfqd, cfqq->cfqg, cfqq);

	if (cfq_cfqq_on_rr(cfqq) && RB_EMPTY_ROOT(&cfqq->sort_list))
		cfq_del_cfqq_rr(cfqd, cfqq);

	cfq_resort_rr_list(cfqd, cfqq);

	if (cfqq == cfqd->active_queue)
		cfqd->active_queue = NULL;

	if (&cfqq->cfqg->rb_node == cfqd->grp_service_tree.active)
		cfqd->grp_service_tree.active = NULL;

	if (cfqd->active_cic) {
		put_io_context(cfqd->active_cic->ioc);
		cfqd->active_cic = NULL;
	}
}