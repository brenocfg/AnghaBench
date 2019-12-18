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
union cpu_time_count {int /*<<< orphan*/  cpu; scalar_t__ sched; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_SCHED ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cputime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline union cpu_time_count cpu_time_sub(const clockid_t which_clock,
						union cpu_time_count a,
						union cpu_time_count b)
{
	if (CPUCLOCK_WHICH(which_clock) == CPUCLOCK_SCHED) {
		a.sched -= b.sched;
	}  else {
		a.cpu = cputime_sub(a.cpu, b.cpu);
	}
	return a;
}