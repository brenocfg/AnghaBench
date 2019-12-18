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
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cpu_time_add(const clockid_t which_clock,
				union cpu_time_count *acc,
			        union cpu_time_count val)
{
	if (CPUCLOCK_WHICH(which_clock) == CPUCLOCK_SCHED) {
		acc->sched += val.sched;
	}  else {
		acc->cpu = cputime_add(acc->cpu, val.cpu);
	}
}