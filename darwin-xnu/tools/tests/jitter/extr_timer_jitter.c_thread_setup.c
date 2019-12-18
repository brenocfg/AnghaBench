#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int period; int constraint; int computation; int /*<<< orphan*/  preemptible; } ;
typedef  TYPE_1__ thread_time_constraint_policy_data_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
struct TYPE_5__ {int /*<<< orphan*/  timeshare; } ;
typedef  TYPE_2__ thread_extended_policy_data_t ;
typedef  int my_policy_type_t ;
struct TYPE_6__ {int denom; int numer; } ;

/* Variables and functions */
 int COMPUTATION_NANOS ; 
 int CONSTRAINT_NANOS ; 
#define  MY_POLICY_FIXEDPRI 130 
#define  MY_POLICY_REALTIME 129 
#define  MY_POLICY_TIMESHARE 128 
 int /*<<< orphan*/  THREAD_EXTENDED_POLICY ; 
 int /*<<< orphan*/  THREAD_EXTENDED_POLICY_COUNT ; 
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY ; 
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY_COUNT ; 
 int /*<<< orphan*/  assert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail ; 
 TYPE_3__ g_mti ; 
 int /*<<< orphan*/  mach_thread_self () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int thread_policy_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
thread_setup(my_policy_type_t pol)
{
	int res;

	switch (pol) {
		case MY_POLICY_TIMESHARE:
		{
			return 0;
		}
		case MY_POLICY_REALTIME: 
		{
			thread_time_constraint_policy_data_t pol;

			/* Hard-coded realtime parameters (similar to what Digi uses) */
			pol.period = 100000;
			pol.constraint =  CONSTRAINT_NANOS * g_mti.denom / g_mti.numer;
			pol.computation = COMPUTATION_NANOS * g_mti.denom / g_mti.numer;
			pol.preemptible = 0; /* Ignored by OS */

			res = thread_policy_set(mach_thread_self(), THREAD_TIME_CONSTRAINT_POLICY, (thread_policy_t) &pol, THREAD_TIME_CONSTRAINT_POLICY_COUNT);
			assert(res == 0, fail);
			break;
		}
		case MY_POLICY_FIXEDPRI: 
		{
			thread_extended_policy_data_t pol;
			pol.timeshare = 0;

			res = thread_policy_set(mach_thread_self(), THREAD_EXTENDED_POLICY, (thread_policy_t) &pol, THREAD_EXTENDED_POLICY_COUNT);
			assert(res == 0, fail);
			break;
		}
		default:
		{
			printf("invalid policy type\n");
			return 1;
		}
	}

	return 0;
fail:
	return 1;
}