#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int on_rq; } ;
struct task_struct {int sched_reset_on_fork; int policy; scalar_t__ rt_priority; int prio; int /*<<< orphan*/  pi_lock; struct sched_class* sched_class; TYPE_4__ se; TYPE_2__* signal; scalar_t__ mm; } ;
struct sched_param {scalar_t__ sched_priority; } ;
struct sched_class {int /*<<< orphan*/  (* set_curr_task ) (struct rq*) ;int /*<<< orphan*/  (* put_prev_task ) (struct rq*,struct task_struct*) ;} ;
struct rq {struct task_struct* stop; } ;
struct TYPE_9__ {scalar_t__ rt_runtime; } ;
struct TYPE_11__ {TYPE_3__ rt_bandwidth; } ;
struct TYPE_8__ {TYPE_1__* rlim; } ;
struct TYPE_7__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int MAX_RT_PRIO ; 
 int MAX_USER_RT_PRIO ; 
 size_t RLIMIT_RTPRIO ; 
 int SCHED_BATCH ; 
 int SCHED_FIFO ; 
 int SCHED_IDLE ; 
 int SCHED_NORMAL ; 
 int SCHED_RESET_ON_FORK ; 
 int SCHED_RR ; 
 int /*<<< orphan*/  __setscheduler (struct rq*,struct task_struct*,int,unsigned long) ; 
 struct rq* __task_rq_lock (struct task_struct*) ; 
 int /*<<< orphan*/  __task_rq_unlock (struct rq*) ; 
 int /*<<< orphan*/  activate_task (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_class_changed (struct rq*,struct task_struct*,struct sched_class const*,int,int) ; 
 int /*<<< orphan*/  check_same_owner (struct task_struct*) ; 
 int /*<<< orphan*/  deactivate_task (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  lock_task_sighand (struct task_struct*,unsigned long*) ; 
 scalar_t__ rt_bandwidth_enabled () ; 
 int /*<<< orphan*/  rt_mutex_adjust_pi (struct task_struct*) ; 
 int rt_policy (int) ; 
 int security_task_setscheduler (struct task_struct*,int,struct sched_param*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  stub2 (struct rq*) ; 
 int task_current (struct rq*,struct task_struct*) ; 
 TYPE_5__* task_group (struct task_struct*) ; 
 int /*<<< orphan*/  task_group_is_autogroup (TYPE_5__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static int __sched_setscheduler(struct task_struct *p, int policy,
				struct sched_param *param, bool user)
{
	int retval, oldprio, oldpolicy = -1, on_rq, running;
	unsigned long flags;
	const struct sched_class *prev_class;
	struct rq *rq;
	int reset_on_fork;

	/* may grab non-irq protected spin_locks */
	BUG_ON(in_interrupt());
recheck:
	/* double check policy once rq lock held */
	if (policy < 0) {
		reset_on_fork = p->sched_reset_on_fork;
		policy = oldpolicy = p->policy;
	} else {
		reset_on_fork = !!(policy & SCHED_RESET_ON_FORK);
		policy &= ~SCHED_RESET_ON_FORK;

		if (policy != SCHED_FIFO && policy != SCHED_RR &&
				policy != SCHED_NORMAL && policy != SCHED_BATCH &&
				policy != SCHED_IDLE)
			return -EINVAL;
	}

	/*
	 * Valid priorities for SCHED_FIFO and SCHED_RR are
	 * 1..MAX_USER_RT_PRIO-1, valid priority for SCHED_NORMAL,
	 * SCHED_BATCH and SCHED_IDLE is 0.
	 */
	if (param->sched_priority < 0 ||
	    (p->mm && param->sched_priority > MAX_USER_RT_PRIO-1) ||
	    (!p->mm && param->sched_priority > MAX_RT_PRIO-1))
		return -EINVAL;
	if (rt_policy(policy) != (param->sched_priority != 0))
		return -EINVAL;

	/*
	 * Allow unprivileged RT tasks to decrease priority:
	 */
	if (user && !capable(CAP_SYS_NICE)) {
		if (rt_policy(policy)) {
			unsigned long rlim_rtprio;

			if (!lock_task_sighand(p, &flags))
				return -ESRCH;
			rlim_rtprio = p->signal->rlim[RLIMIT_RTPRIO].rlim_cur;
			unlock_task_sighand(p, &flags);

			/* can't set/change the rt policy */
			if (policy != p->policy && !rlim_rtprio)
				return -EPERM;

			/* can't increase priority */
			if (param->sched_priority > p->rt_priority &&
			    param->sched_priority > rlim_rtprio)
				return -EPERM;
		}
		/*
		 * Like positive nice levels, dont allow tasks to
		 * move out of SCHED_IDLE either:
		 */
		if (p->policy == SCHED_IDLE && policy != SCHED_IDLE)
			return -EPERM;

		/* can't change other user's priorities */
		if (!check_same_owner(p))
			return -EPERM;

		/* Normal users shall not reset the sched_reset_on_fork flag */
		if (p->sched_reset_on_fork && !reset_on_fork)
			return -EPERM;
	}

	if (user) {
#ifdef CONFIG_RT_GROUP_SCHED
		/*
		 * Do not allow realtime tasks into groups that have no runtime
		 * assigned.
		 */
		if (rt_bandwidth_enabled() && rt_policy(policy) &&
				task_group(p)->rt_bandwidth.rt_runtime == 0 &&
				!task_group_is_autogroup(task_group(p)))
			return -EPERM;
#endif

		retval = security_task_setscheduler(p, policy, param);
		if (retval)
			return retval;
	}

	/*
	 * make sure no PI-waiters arrive (or leave) while we are
	 * changing the priority of the task:
	 */
	spin_lock_irqsave(&p->pi_lock, flags);
	/*
	 * To be able to change p->policy safely, the apropriate
	 * runqueue lock must be held.
	 */
	rq = __task_rq_lock(p);

	/*
	 * Changing the policy of the stop threads its a very bad idea
	 */
	if (p == rq->stop) {
		__task_rq_unlock(rq);
		spin_unlock_irqrestore(&p->pi_lock, flags);
		return -EINVAL;
	}

	/* recheck policy now with rq lock held */
	if (unlikely(oldpolicy != -1 && oldpolicy != p->policy)) {
		policy = oldpolicy = -1;
		__task_rq_unlock(rq);
		spin_unlock_irqrestore(&p->pi_lock, flags);
		goto recheck;
	}
	on_rq = p->se.on_rq;
	running = task_current(rq, p);
	if (on_rq)
		deactivate_task(rq, p, 0);
	if (running)
		p->sched_class->put_prev_task(rq, p);

	p->sched_reset_on_fork = reset_on_fork;

	oldprio = p->prio;
	prev_class = p->sched_class;
	__setscheduler(rq, p, policy, param->sched_priority);

	if (running)
		p->sched_class->set_curr_task(rq);
	if (on_rq) {
		activate_task(rq, p, 0);

		check_class_changed(rq, p, prev_class, oldprio, running);
	}
	__task_rq_unlock(rq);
	spin_unlock_irqrestore(&p->pi_lock, flags);

	rt_mutex_adjust_pi(p);

	return 0;
}