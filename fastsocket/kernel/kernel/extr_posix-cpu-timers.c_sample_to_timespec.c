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
union cpu_time_count {int /*<<< orphan*/  cpu; int /*<<< orphan*/  sched; } ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_SCHED ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cputime_to_timespec (int /*<<< orphan*/ ,struct timespec*) ; 
 struct timespec ns_to_timespec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sample_to_timespec(const clockid_t which_clock,
			       union cpu_time_count cpu,
			       struct timespec *tp)
{
	if (CPUCLOCK_WHICH(which_clock) == CPUCLOCK_SCHED)
		*tp = ns_to_timespec(cpu.sched);
	else
		cputime_to_timespec(cpu.cpu, tp);
}