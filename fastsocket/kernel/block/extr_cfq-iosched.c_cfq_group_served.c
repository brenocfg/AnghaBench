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
struct cfq_rb_root {int /*<<< orphan*/  min_vdisktime; } ;
struct cfq_queue {unsigned int slice_dispatch; unsigned int allocated_slice; int /*<<< orphan*/  nr_sectors; int /*<<< orphan*/  cfqd; } ;
struct TYPE_2__ {int count; } ;
struct cfq_group {int nr_cfqq; int /*<<< orphan*/  blkg; int /*<<< orphan*/  vdisktime; scalar_t__ saved_workload_slice; int /*<<< orphan*/  saved_serving_prio; int /*<<< orphan*/  saved_workload; TYPE_1__ service_tree_idle; } ;
struct cfq_data {int /*<<< orphan*/  serving_prio; int /*<<< orphan*/  serving_type; scalar_t__ workload_expires; struct cfq_rb_root grp_service_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cfq_blkiocg_set_start_empty_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_timeslice_used (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int cfq_cfqq_slice_usage (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_group_service_tree_add (struct cfq_rb_root*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_group_service_tree_del (struct cfq_rb_root*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_log_cfqg (struct cfq_data*,struct cfq_group*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_log_cfqq (int /*<<< orphan*/ ,struct cfq_queue*,char*,unsigned int,unsigned int,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cfq_scale_slice (unsigned int,struct cfq_group*) ; 
 int cfqg_busy_async_queues (struct cfq_data*,struct cfq_group*) ; 
 scalar_t__ iops_mode (struct cfq_data*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cfq_group_served(struct cfq_data *cfqd, struct cfq_group *cfqg,
				struct cfq_queue *cfqq)
{
	struct cfq_rb_root *st = &cfqd->grp_service_tree;
	unsigned int used_sl, charge;
	int nr_sync = cfqg->nr_cfqq - cfqg_busy_async_queues(cfqd, cfqg)
			- cfqg->service_tree_idle.count;

	BUG_ON(nr_sync < 0);
	used_sl = charge = cfq_cfqq_slice_usage(cfqq);

	if (iops_mode(cfqd))
		charge = cfqq->slice_dispatch;
	else if (!cfq_cfqq_sync(cfqq) && !nr_sync)
		charge = cfqq->allocated_slice;

	/* Can't update vdisktime while group is on service tree */
	cfq_group_service_tree_del(st, cfqg);
	cfqg->vdisktime += cfq_scale_slice(charge, cfqg);
	/* If a new weight was requested, update now, off tree */
	cfq_group_service_tree_add(st, cfqg);

	/* This group is being expired. Save the context */
	if (time_after(cfqd->workload_expires, jiffies)) {
		cfqg->saved_workload_slice = cfqd->workload_expires
						- jiffies;
		cfqg->saved_workload = cfqd->serving_type;
		cfqg->saved_serving_prio = cfqd->serving_prio;
	} else
		cfqg->saved_workload_slice = 0;

	cfq_log_cfqg(cfqd, cfqg, "served: vt=%llu min_vt=%llu", cfqg->vdisktime,
					st->min_vdisktime);
	cfq_log_cfqq(cfqq->cfqd, cfqq, "sl_used=%u disp=%u charge=%u iops=%u"
			" sect=%u", used_sl, cfqq->slice_dispatch, charge,
			iops_mode(cfqd), cfqq->nr_sectors);
	cfq_blkiocg_update_timeslice_used(&cfqg->blkg, used_sl);
	cfq_blkiocg_set_start_empty_time(&cfqg->blkg);
}