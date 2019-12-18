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
struct task_struct {scalar_t__ policy; int /*<<< orphan*/  pushable_tasks; scalar_t__ oncpu; int /*<<< orphan*/  sched_info; TYPE_2__* sched_class; int /*<<< orphan*/  prio; scalar_t__ sched_reset_on_fork; int /*<<< orphan*/  static_prio; int /*<<< orphan*/  normal_prio; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int /*<<< orphan*/  normal_prio; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* task_fork ) (struct task_struct*) ;} ;
struct TYPE_4__ {int preempt_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PRIO ; 
 int /*<<< orphan*/  NICE_TO_PRIO (int /*<<< orphan*/ ) ; 
 scalar_t__ PRIO_TO_NICE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCHED_FIFO ; 
 scalar_t__ SCHED_NORMAL ; 
 scalar_t__ SCHED_RR ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __sched_fork (struct task_struct*) ; 
 TYPE_3__* current ; 
 TYPE_2__ fair_sched_class ; 
 int get_cpu () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plist_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  rt_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_info_on () ; 
 int /*<<< orphan*/  set_load_weight (struct task_struct*) ; 
 int /*<<< orphan*/  set_task_cpu (struct task_struct*,int) ; 
 int /*<<< orphan*/  stub1 (struct task_struct*) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

void sched_fork(struct task_struct *p, int clone_flags)
{
	int cpu = get_cpu();

	__sched_fork(p);
	/*
	 * We mark the process as running here. This guarantees that
	 * nobody will actually run it, and a signal or other external
	 * event cannot wake it up and insert it on the runqueue either.
	 */
	p->state = TASK_RUNNING;

	/*
	 * Revert to default priority/policy on fork if requested.
	 */
	if (unlikely(p->sched_reset_on_fork)) {
		if (p->policy == SCHED_FIFO || p->policy == SCHED_RR) {
			p->policy = SCHED_NORMAL;
			p->normal_prio = p->static_prio;
		}

		if (PRIO_TO_NICE(p->static_prio) < 0) {
			p->static_prio = NICE_TO_PRIO(0);
			p->normal_prio = p->static_prio;
			set_load_weight(p);
		}

		/*
		 * We don't need the reset flag anymore after the fork. It has
		 * fulfilled its duty:
		 */
		p->sched_reset_on_fork = 0;
	}

	/*
	 * Make sure we do not leak PI boosting priority to the child.
	 */
	p->prio = current->normal_prio;

	if (!rt_prio(p->prio))
		p->sched_class = &fair_sched_class;

	if (p->sched_class->task_fork)
		p->sched_class->task_fork(p);

	set_task_cpu(p, cpu);

#if defined(CONFIG_SCHEDSTATS) || defined(CONFIG_TASK_DELAY_ACCT)
	if (likely(sched_info_on()))
		memset(&p->sched_info, 0, sizeof(p->sched_info));
#endif
#if defined(CONFIG_SMP) && defined(__ARCH_WANT_UNLOCKED_CTXSW)
	p->oncpu = 0;
#endif
#ifdef CONFIG_PREEMPT
	/* Want to start with kernel preemption disabled. */
	task_thread_info(p)->preempt_count = 1;
#endif
	plist_node_init(&p->pushable_tasks, MAX_PRIO);

	put_cpu();
}