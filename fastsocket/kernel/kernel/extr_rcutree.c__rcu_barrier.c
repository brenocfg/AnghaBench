#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rcu_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_adopt_orphan_cbs (struct rcu_state*) ; 
 int /*<<< orphan*/  rcu_barrier_completion ; 
 int /*<<< orphan*/  rcu_barrier_cpu_count ; 
 int /*<<< orphan*/  rcu_barrier_func ; 
 int /*<<< orphan*/  rcu_barrier_mutex ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rcu_barrier(struct rcu_state *rsp,
			 void (*call_rcu_func)(struct rcu_head *head,
					       void (*func)(struct rcu_head *head)))
{
	BUG_ON(in_interrupt());
	/* Take mutex to serialize concurrent rcu_barrier() requests. */
	mutex_lock(&rcu_barrier_mutex);
	init_completion(&rcu_barrier_completion);
	/*
	 * Initialize rcu_barrier_cpu_count to 1, then invoke
	 * rcu_barrier_func() on each CPU, so that each CPU also has
	 * incremented rcu_barrier_cpu_count.  Only then is it safe to
	 * decrement rcu_barrier_cpu_count -- otherwise the first CPU
	 * might complete its grace period before all of the other CPUs
	 * did their increment, causing this function to return too
	 * early.
	 */
	atomic_set(&rcu_barrier_cpu_count, 1);
	preempt_disable(); /* stop CPU_DYING from filling orphan_cbs_list */
	rcu_adopt_orphan_cbs(rsp);
	on_each_cpu(rcu_barrier_func, (void *)call_rcu_func, 1);
	preempt_enable(); /* CPU_DYING can again fill orphan_cbs_list */
	if (atomic_dec_and_test(&rcu_barrier_cpu_count))
		complete(&rcu_barrier_completion);
	wait_for_completion(&rcu_barrier_completion);
	mutex_unlock(&rcu_barrier_mutex);
}