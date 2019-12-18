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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 size_t get_cpu_num () ; 
 int sched_setaffinity (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

int bind_process_cpu(int cpu)
{
	cpu_set_t cmask;
	size_t n;
	int ret;

	n = get_cpu_num();

	if (cpu < 0 || cpu >= (int)n) {
		errno = EINVAL;
		return -1;
	}

	CPU_ZERO(&cmask);
	CPU_SET(cpu, &cmask);

	ret = sched_setaffinity(0, n, &cmask);

	CPU_ZERO(&cmask);

	return ret;
}