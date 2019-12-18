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
struct task_struct {int /*<<< orphan*/  cpus_allowed; } ;
struct rq {int dummy; } ;
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct task_struct* find_process_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_task_getscheduler (struct task_struct*) ; 
 struct rq* task_rq_lock (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,unsigned long*) ; 

long sched_getaffinity(pid_t pid, struct cpumask *mask)
{
	struct task_struct *p;
	unsigned long flags;
	struct rq *rq;
	int retval;

	get_online_cpus();
	rcu_read_lock();

	retval = -ESRCH;
	p = find_process_by_pid(pid);
	if (!p)
		goto out_unlock;

	retval = security_task_getscheduler(p);
	if (retval)
		goto out_unlock;

	rq = task_rq_lock(p, &flags);
	cpumask_and(mask, &p->cpus_allowed, cpu_online_mask);
	task_rq_unlock(rq, &flags);

out_unlock:
	rcu_read_unlock();
	put_online_cpus();

	return retval;
}