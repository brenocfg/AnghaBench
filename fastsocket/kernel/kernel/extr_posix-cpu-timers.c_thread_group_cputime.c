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
struct TYPE_2__ {scalar_t__ sum_exec_runtime; } ;
struct task_struct {TYPE_1__ se; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; struct signal_struct* signal; int /*<<< orphan*/  sighand; } ;
struct task_cputime {int /*<<< orphan*/  sum_exec_runtime; void* stime; void* utime; } ;
struct signal_struct {scalar_t__ sum_sched_runtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;
struct sighand_struct {int dummy; } ;

/* Variables and functions */
 struct task_cputime INIT_CPUTIME ; 
 void* cputime_add (void*,int /*<<< orphan*/ ) ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 struct sighand_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void thread_group_cputime(struct task_struct *tsk, struct task_cputime *times)
{
	struct sighand_struct *sighand;
	struct signal_struct *sig;
	struct task_struct *t;

	*times = INIT_CPUTIME;

	rcu_read_lock();
	sighand = rcu_dereference(tsk->sighand);
	if (!sighand)
		goto out;

	sig = tsk->signal;

	t = tsk;
	do {
		times->utime = cputime_add(times->utime, t->utime);
		times->stime = cputime_add(times->stime, t->stime);
		times->sum_exec_runtime += t->se.sum_exec_runtime;

		t = next_thread(t);
	} while (t != tsk);

	times->utime = cputime_add(times->utime, sig->utime);
	times->stime = cputime_add(times->stime, sig->stime);
	times->sum_exec_runtime += sig->sum_sched_runtime;
out:
	rcu_read_unlock();
}