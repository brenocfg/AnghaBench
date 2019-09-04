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
 scalar_t__ CTR_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cpu_broadcast_xcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* mt_core_reset_values ; 
 size_t mt_microstackshot_ctr ; 
 int /*<<< orphan*/  mt_microstackshot_start_remote ; 
 int /*<<< orphan*/  mt_xc_sync ; 

int
mt_microstackshot_start_arch(uint64_t period)
{
	mt_core_reset_values[mt_microstackshot_ctr] = CTR_MAX - period;
	cpu_broadcast_xcall(&mt_xc_sync, TRUE, mt_microstackshot_start_remote,
			mt_microstackshot_start_remote /* cannot pass NULL */);
	return 0;
}