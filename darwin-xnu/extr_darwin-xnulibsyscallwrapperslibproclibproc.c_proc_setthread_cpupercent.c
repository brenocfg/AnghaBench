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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  RLIMIT_THREAD_CPULIMITS ; 
 int /*<<< orphan*/  errno ; 
 int proc_rlimit_control (int,int /*<<< orphan*/ ,void*) ; 

int
proc_setthread_cpupercent(uint8_t percentage, uint32_t ms_refill)
{
	uint32_t arg = 0;

	/* Pack percentage and refill into a 32-bit number to match existing kernel implementation */
	if ((percentage >= 100) || (ms_refill & ~0xffffffU)) {
		errno = EINVAL;
		return -1;
	}

	arg = ((ms_refill << 8) | percentage);

	return (proc_rlimit_control(-1, RLIMIT_THREAD_CPULIMITS, (void *)(uintptr_t)arg));
}