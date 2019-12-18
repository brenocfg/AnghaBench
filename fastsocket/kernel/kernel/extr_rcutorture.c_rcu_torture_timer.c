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
struct rcu_torture {scalar_t__ rtort_mbtest; int rtort_pipe_count; } ;
struct TYPE_2__ {int (* readlock ) () ;int (* completed ) () ;int /*<<< orphan*/  (* readunlock ) (int) ;int /*<<< orphan*/  (* read_delay ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;
typedef  int /*<<< orphan*/  DEFINE_RCU_RANDOM ;

/* Variables and functions */
 int RCU_TORTURE_PIPE_LEN ; 
 int /*<<< orphan*/ * __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  n_rcu_torture_mberror ; 
 int /*<<< orphan*/  n_rcu_torture_timers ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct rcu_torture* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_torture_batch ; 
 int /*<<< orphan*/  rcu_torture_count ; 
 int /*<<< orphan*/  rcu_torture_current ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int stub5 () ; 
 int /*<<< orphan*/  stub6 (int) ; 

__attribute__((used)) static void rcu_torture_timer(unsigned long unused)
{
	int idx;
	int completed;
	static DEFINE_RCU_RANDOM(rand);
	static DEFINE_SPINLOCK(rand_lock);
	struct rcu_torture *p;
	int pipe_count;

	idx = cur_ops->readlock();
	completed = cur_ops->completed();
	p = rcu_dereference(rcu_torture_current);
	if (p == NULL) {
		/* Leave because rcu_torture_writer is not yet underway */
		cur_ops->readunlock(idx);
		return;
	}
	if (p->rtort_mbtest == 0)
		atomic_inc(&n_rcu_torture_mberror);
	spin_lock(&rand_lock);
	cur_ops->read_delay(&rand);
	n_rcu_torture_timers++;
	spin_unlock(&rand_lock);
	preempt_disable();
	pipe_count = p->rtort_pipe_count;
	if (pipe_count > RCU_TORTURE_PIPE_LEN) {
		/* Should not happen, but... */
		pipe_count = RCU_TORTURE_PIPE_LEN;
	}
	++__get_cpu_var(rcu_torture_count)[pipe_count];
	completed = cur_ops->completed() - completed;
	if (completed > RCU_TORTURE_PIPE_LEN) {
		/* Should not happen, but... */
		completed = RCU_TORTURE_PIPE_LEN;
	}
	++__get_cpu_var(rcu_torture_batch)[completed];
	preempt_enable();
	cur_ops->readunlock(idx);
}