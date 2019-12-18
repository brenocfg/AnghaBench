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
union cpu_time_count {int /*<<< orphan*/  sched; int /*<<< orphan*/  cpu; } ;
struct task_struct {int dummy; } ;
struct task_cputime {int /*<<< orphan*/  utime; int /*<<< orphan*/  stime; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
#define  CPUCLOCK_PROF 130 
#define  CPUCLOCK_SCHED 129 
#define  CPUCLOCK_VIRT 128 
 int CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_group_cputime (struct task_struct*,struct task_cputime*) ; 
 int /*<<< orphan*/  thread_group_sched_runtime (struct task_struct*) ; 

__attribute__((used)) static int cpu_clock_sample_group(const clockid_t which_clock,
				  struct task_struct *p,
				  union cpu_time_count *cpu)
{
	struct task_cputime cputime;

	switch (CPUCLOCK_WHICH(which_clock)) {
	default:
		return -EINVAL;
	case CPUCLOCK_PROF:
		thread_group_cputime(p, &cputime);
		cpu->cpu = cputime_add(cputime.utime, cputime.stime);
		break;
	case CPUCLOCK_VIRT:
		thread_group_cputime(p, &cputime);
		cpu->cpu = cputime.utime;
		break;
	case CPUCLOCK_SCHED:
		cpu->sched = thread_group_sched_runtime(p);
		break;
	}
	return 0;
}