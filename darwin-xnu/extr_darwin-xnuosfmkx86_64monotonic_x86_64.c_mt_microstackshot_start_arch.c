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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  CPUMASK_ALL ; 
 scalar_t__ CTR_MAX ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__* mt_core_reset_values ; 
 int /*<<< orphan*/  mt_core_supported ; 
 size_t mt_microstackshot_ctr ; 
 int /*<<< orphan*/  mt_microstackshot_start_remote ; 

int
mt_microstackshot_start_arch(uint64_t period)
{
	if (!mt_core_supported) {
		return ENOTSUP;
	}

	mt_core_reset_values[mt_microstackshot_ctr] = CTR_MAX - period;
	mp_cpus_call(CPUMASK_ALL, ASYNC, mt_microstackshot_start_remote,
			NULL);
	return 0;
}