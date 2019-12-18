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
struct task_struct {struct signal_struct* signal; } ;
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct TYPE_5__ {scalar_t__ tv64; } ;
struct signal_struct {int /*<<< orphan*/  oom_score_adj_min; int /*<<< orphan*/  oom_score_adj; int /*<<< orphan*/  oom_adj; int /*<<< orphan*/  threadgroup_fork_lock; int /*<<< orphan*/  pacct; int /*<<< orphan*/  rlim; scalar_t__ sum_sched_runtime; int /*<<< orphan*/  ioac; scalar_t__ cmaxrss; scalar_t__ maxrss; scalar_t__ coublock; scalar_t__ cinblock; scalar_t__ oublock; scalar_t__ inblock; scalar_t__ cmaj_flt; scalar_t__ cmin_flt; scalar_t__ maj_flt; scalar_t__ min_flt; scalar_t__ cnivcsw; scalar_t__ cnvcsw; scalar_t__ nivcsw; scalar_t__ nvcsw; void* prev_stime; void* prev_utime; void* cgtime; void* gtime; void* cstime; void* cutime; void* stime; void* utime; int /*<<< orphan*/ * tty; int /*<<< orphan*/ * tty_old_pgrp; scalar_t__ leader; TYPE_3__ real_timer; TYPE_1__ it_real_incr; int /*<<< orphan*/  posix_timers; int /*<<< orphan*/  shared_pending; struct task_struct* curr_target; scalar_t__ group_stop_count; int /*<<< orphan*/ * group_exit_task; scalar_t__ group_exit_code; scalar_t__ flags; int /*<<< orphan*/  wait_chldexit; int /*<<< orphan*/  live; int /*<<< orphan*/  count; } ;
struct TYPE_8__ {TYPE_2__* signal; int /*<<< orphan*/  group_leader; } ;
struct TYPE_6__ {int /*<<< orphan*/  oom_score_adj_min; int /*<<< orphan*/  oom_score_adj; int /*<<< orphan*/  oom_adj; int /*<<< orphan*/  rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 unsigned long CLONE_THREAD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acct_init_pacct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 void* cputime_zero ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_sigpending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  it_real_fn ; 
 struct signal_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  posix_cpu_timers_init_group (struct signal_struct*) ; 
 int /*<<< orphan*/  sched_autogroup_fork (struct signal_struct*) ; 
 int /*<<< orphan*/  signal_cachep ; 
 int /*<<< orphan*/  task_io_accounting_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskstats_tgid_init (struct signal_struct*) ; 
 int /*<<< orphan*/  tty_audit_fork (struct signal_struct*) ; 

__attribute__((used)) static int copy_signal(unsigned long clone_flags, struct task_struct *tsk)
{
	struct signal_struct *sig;

	if (clone_flags & CLONE_THREAD)
		return 0;

	sig = kmem_cache_alloc(signal_cachep, GFP_KERNEL);
	tsk->signal = sig;
	if (!sig)
		return -ENOMEM;

	atomic_set(&sig->count, 1);
	atomic_set(&sig->live, 1);
	init_waitqueue_head(&sig->wait_chldexit);
	sig->flags = 0;
	sig->group_exit_code = 0;
	sig->group_exit_task = NULL;
	sig->group_stop_count = 0;
	sig->curr_target = tsk;
	init_sigpending(&sig->shared_pending);
	INIT_LIST_HEAD(&sig->posix_timers);

	hrtimer_init(&sig->real_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	sig->it_real_incr.tv64 = 0;
	sig->real_timer.function = it_real_fn;

	sig->leader = 0;	/* session leadership doesn't inherit */
	sig->tty_old_pgrp = NULL;
	sig->tty = NULL;

	sig->utime = sig->stime = sig->cutime = sig->cstime = cputime_zero;
	sig->gtime = cputime_zero;
	sig->cgtime = cputime_zero;
	sig->prev_utime = sig->prev_stime = cputime_zero;
	sig->nvcsw = sig->nivcsw = sig->cnvcsw = sig->cnivcsw = 0;
	sig->min_flt = sig->maj_flt = sig->cmin_flt = sig->cmaj_flt = 0;
	sig->inblock = sig->oublock = sig->cinblock = sig->coublock = 0;
	sig->maxrss = sig->cmaxrss = 0;
	task_io_accounting_init(&sig->ioac);
	sig->sum_sched_runtime = 0;
	taskstats_tgid_init(sig);

	task_lock(current->group_leader);
	memcpy(sig->rlim, current->signal->rlim, sizeof sig->rlim);
	task_unlock(current->group_leader);

	posix_cpu_timers_init_group(sig);

	acct_init_pacct(&sig->pacct);

	tty_audit_fork(sig);
	sched_autogroup_fork(sig);

#ifdef CONFIG_CGROUPS
	init_rwsem(&sig->threadgroup_fork_lock);
#endif

	sig->oom_adj = current->signal->oom_adj;
	sig->oom_score_adj = current->signal->oom_score_adj;
	sig->oom_score_adj_min = current->signal->oom_score_adj_min;

	return 0;
}