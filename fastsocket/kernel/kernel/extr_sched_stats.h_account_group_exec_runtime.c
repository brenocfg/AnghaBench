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
struct TYPE_2__ {unsigned long long sum_exec_runtime; } ;
struct thread_group_cputimer {int /*<<< orphan*/  lock; TYPE_1__ cputime; int /*<<< orphan*/  running; } ;
struct task_struct {struct signal_struct* signal; } ;
struct signal_struct {struct thread_group_cputimer cputimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void account_group_exec_runtime(struct task_struct *tsk,
					      unsigned long long ns)
{
	struct thread_group_cputimer *cputimer;
	struct signal_struct *sig;

	sig = tsk->signal;
	/* see __exit_signal()->task_rq_unlock_wait() */
	barrier();
	if (unlikely(!sig))
		return;

	cputimer = &sig->cputimer;

	if (!cputimer->running)
		return;

	spin_lock(&cputimer->lock);
	cputimer->cputime.sum_exec_runtime += ns;
	spin_unlock(&cputimer->lock);
}