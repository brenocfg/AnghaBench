#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  timer_active; } ;
struct task_group {int /*<<< orphan*/  load_weight; TYPE_3__ cfs_bandwidth; } ;
struct seq_file {int dummy; } ;
struct sched_entity {int vruntime; } ;
struct TYPE_5__ {int min_vruntime; } ;
struct rq {int /*<<< orphan*/  lock; TYPE_1__ cfs; } ;
struct TYPE_6__ {int /*<<< orphan*/  weight; } ;
struct cfs_rq {int exec_clock; int min_vruntime; int load_avg; int load_period; struct task_group* tg; int /*<<< orphan*/  load_contribution; int /*<<< orphan*/  throttle_count; int /*<<< orphan*/  throttled; TYPE_2__ load; int /*<<< orphan*/  nr_running; int /*<<< orphan*/  nr_spread_over; scalar_t__ rb_leftmost; } ;
typedef  int s64 ;
struct TYPE_8__ {int vruntime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  SPLIT_NS (int) ; 
 TYPE_4__* __pick_first_entity (struct cfs_rq*) ; 
 struct sched_entity* __pick_last_entity (struct cfs_rq*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct rq* cpu_rq (int) ; 
 int /*<<< orphan*/  print_cfs_group_stats (struct seq_file*,int,struct task_group*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_group_path (struct task_group*) ; 

void print_cfs_rq(struct seq_file *m, int cpu, struct cfs_rq *cfs_rq)
{
	s64 MIN_vruntime = -1, min_vruntime, max_vruntime = -1,
		spread, rq0_min_vruntime, spread0;
	struct rq *rq = cpu_rq(cpu);
	struct sched_entity *last;
	unsigned long flags;

#ifdef CONFIG_FAIR_GROUP_SCHED
	struct task_group *tg = cfs_rq->tg;

	SEQ_printf(m, "\ncfs_rq[%d]:%s\n", cpu, task_group_path(tg));
#else
	SEQ_printf(m, "\ncfs_rq[%d]:\n", cpu);
#endif
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "exec_clock",
			SPLIT_NS(cfs_rq->exec_clock));

	spin_lock_irqsave(&rq->lock, flags);
	if (cfs_rq->rb_leftmost)
		MIN_vruntime = (__pick_first_entity(cfs_rq))->vruntime;
	last = __pick_last_entity(cfs_rq);
	if (last)
		max_vruntime = last->vruntime;
	min_vruntime = cfs_rq->min_vruntime;
	rq0_min_vruntime = cpu_rq(0)->cfs.min_vruntime;
	spin_unlock_irqrestore(&rq->lock, flags);
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "MIN_vruntime",
			SPLIT_NS(MIN_vruntime));
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "min_vruntime",
			SPLIT_NS(min_vruntime));
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "max_vruntime",
			SPLIT_NS(max_vruntime));
	spread = max_vruntime - MIN_vruntime;
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "spread",
			SPLIT_NS(spread));
	spread0 = min_vruntime - rq0_min_vruntime;
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "spread0",
			SPLIT_NS(spread0));
	SEQ_printf(m, "  .%-30s: %d\n", "nr_spread_over",
			cfs_rq->nr_spread_over);
	SEQ_printf(m, "  .%-30s: %ld\n", "nr_running", cfs_rq->nr_running);
	SEQ_printf(m, "  .%-30s: %ld\n", "load", cfs_rq->load.weight);
#ifdef CONFIG_CFS_BANDWIDTH
	SEQ_printf(m, "  .%-30s: %d\n", "tg->cfs_bandwidth.timer_active",
			cfs_rq->tg->cfs_bandwidth.timer_active);
	SEQ_printf(m, "  .%-30s: %d\n", "throttled",
			cfs_rq->throttled);
	SEQ_printf(m, "  .%-30s: %d\n", "throttle_count",
			cfs_rq->throttle_count);
#endif
#ifdef CONFIG_FAIR_GROUP_SCHED
#ifdef CONFIG_SMP
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "load_avg",
		   SPLIT_NS(cfs_rq->load_avg));
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", "load_period",
		   SPLIT_NS(cfs_rq->load_period));
	SEQ_printf(m, "  .%-30s: %ld\n", "load_contrib",
		   cfs_rq->load_contribution);
	SEQ_printf(m, "  .%-30s: %d\n", "load_tg",
		   atomic_read(&tg->load_weight));
#endif

	print_cfs_group_stats(m, cpu, cfs_rq->tg);
#endif
}