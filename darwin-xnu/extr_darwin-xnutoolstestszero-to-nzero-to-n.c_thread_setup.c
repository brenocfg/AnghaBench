#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int period; int constraint; int computation; int /*<<< orphan*/  preemptible; } ;
typedef  TYPE_1__ thread_time_constraint_policy_data_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
struct TYPE_4__ {int affinity_tag; } ;
typedef  TYPE_2__ thread_affinity_policy_data_t ;
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTATION_NANOS ; 
 int /*<<< orphan*/  CONSTRAINT_NANOS ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
#define  MY_POLICY_FIXEDPRI 130 
#define  MY_POLICY_REALTIME 129 
#define  MY_POLICY_TIMESHARE 128 
 int SCHED_OTHER ; 
 int SCHED_RR ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY_COUNT ; 
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY ; 
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY_COUNT ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ g_do_affinity ; 
 int g_policy ; 
 scalar_t__ g_priority ; 
 int /*<<< orphan*/  mach_assert_zero_t (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_thread_self () ; 
 int /*<<< orphan*/  nanos_to_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_set_fixedpriority_self () ; 
 int /*<<< orphan*/  pthread_setschedparam (int /*<<< orphan*/ ,int,struct sched_param*) ; 
 int /*<<< orphan*/  thread_policy_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thread_setup(uint32_t my_id)
{
	kern_return_t kr;
	errno_t ret;
	thread_time_constraint_policy_data_t pol;

	if (g_priority) {
		int policy = SCHED_OTHER;
		if (g_policy == MY_POLICY_FIXEDPRI)
			policy = SCHED_RR;

		struct sched_param param = {.sched_priority = (int)g_priority};
		if ((ret = pthread_setschedparam(pthread_self(), policy, &param)))
			errc(EX_OSERR, ret, "pthread_setschedparam: %d", my_id);
	}

	switch (g_policy) {
		case MY_POLICY_TIMESHARE:
			break;
		case MY_POLICY_REALTIME:
			/* Hard-coded realtime parameters (similar to what Digi uses) */
			pol.period      = 100000;
			pol.constraint  = (uint32_t) nanos_to_abs(CONSTRAINT_NANOS);
			pol.computation = (uint32_t) nanos_to_abs(COMPUTATION_NANOS);
			pol.preemptible = 0; /* Ignored by OS */

			kr = thread_policy_set(mach_thread_self(), THREAD_TIME_CONSTRAINT_POLICY,
			                       (thread_policy_t) &pol, THREAD_TIME_CONSTRAINT_POLICY_COUNT);
			mach_assert_zero_t(my_id, kr);
			break;
		case MY_POLICY_FIXEDPRI:
			ret = pthread_set_fixedpriority_self();
			if (ret) errc(EX_OSERR, ret, "pthread_set_fixedpriority_self");
			break;
		default:
			errx(EX_USAGE, "invalid policy type %d", g_policy);
	}

	if (g_do_affinity) {
		thread_affinity_policy_data_t affinity;

		affinity.affinity_tag = my_id % 2;

		kr = thread_policy_set(mach_thread_self(), THREAD_AFFINITY_POLICY,
		                       (thread_policy_t)&affinity, THREAD_AFFINITY_POLICY_COUNT);
		mach_assert_zero_t(my_id, kr);
	}

	return 0;
}