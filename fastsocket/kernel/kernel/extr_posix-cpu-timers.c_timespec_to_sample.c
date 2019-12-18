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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_SCHED ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/  const) ; 
 unsigned long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  timespec_to_cputime (struct timespec const*) ; 

__attribute__((used)) static inline union cpu_time_count
timespec_to_sample(const clockid_t which_clock, const struct timespec *tp)
{
	union cpu_time_count ret;
	ret.sched = 0;		/* high half always zero when .cpu used */
	if (CPUCLOCK_WHICH(which_clock) == CPUCLOCK_SCHED) {
		ret.sched = (unsigned long long)tp->tv_sec * NSEC_PER_SEC + tp->tv_nsec;
	} else {
		ret.cpu = timespec_to_cputime(tp);
	}
	return ret;
}