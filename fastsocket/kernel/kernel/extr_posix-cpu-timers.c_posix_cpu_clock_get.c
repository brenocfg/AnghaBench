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
typedef  union cpu_time_count {int dummy; } cpu_time_count ;
struct timespec {int dummy; } ;
struct task_struct {scalar_t__ signal; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/  const) ; 
 scalar_t__ CPUCLOCK_PID (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int cpu_clock_sample (int /*<<< orphan*/  const,struct task_struct*,union cpu_time_count*) ; 
 int cpu_clock_sample_group (int /*<<< orphan*/  const,struct task_struct*,union cpu_time_count*) ; 
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (scalar_t__ const) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ same_thread_group (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  sample_to_timespec (int /*<<< orphan*/  const,union cpu_time_count,struct timespec*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 

__attribute__((used)) static int posix_cpu_clock_get(const clockid_t which_clock, struct timespec *tp)
{
	const pid_t pid = CPUCLOCK_PID(which_clock);
	int error = -EINVAL;
	union cpu_time_count rtn;

	if (pid == 0) {
		/*
		 * Special case constant value for our own clocks.
		 * We don't have to do any lookup to find ourselves.
		 */
		if (CPUCLOCK_PERTHREAD(which_clock)) {
			/*
			 * Sampling just ourselves we can do with no locking.
			 */
			error = cpu_clock_sample(which_clock,
						 current, &rtn);
		} else {
			read_lock(&tasklist_lock);
			error = cpu_clock_sample_group(which_clock,
						       current, &rtn);
			read_unlock(&tasklist_lock);
		}
	} else {
		/*
		 * Find the given PID, and validate that the caller
		 * should be able to see it.
		 */
		struct task_struct *p;
		rcu_read_lock();
		p = find_task_by_vpid(pid);
		if (p) {
			if (CPUCLOCK_PERTHREAD(which_clock)) {
				if (same_thread_group(p, current)) {
					error = cpu_clock_sample(which_clock,
								 p, &rtn);
				}
			} else {
				read_lock(&tasklist_lock);
				if (thread_group_leader(p) && p->signal) {
					error =
					    cpu_clock_sample_group(which_clock,
							           p, &rtn);
				}
				read_unlock(&tasklist_lock);
			}
		}
		rcu_read_unlock();
	}

	if (error)
		return error;
	sample_to_timespec(which_clock, rtn, tp);
	return 0;
}