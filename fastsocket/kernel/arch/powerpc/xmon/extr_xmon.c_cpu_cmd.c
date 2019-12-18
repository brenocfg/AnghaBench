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

/* Variables and functions */
 unsigned long NR_CPUS ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ cpu_isset (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_in_xmon ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  scanhex (unsigned long*) ; 
 unsigned long smp_processor_id () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 unsigned long xmon_owner ; 
 scalar_t__ xmon_taken ; 

__attribute__((used)) static int cpu_cmd(void)
{
#ifdef CONFIG_SMP
	unsigned long cpu;
	int timeout;
	int count;

	if (!scanhex(&cpu)) {
		/* print cpus waiting or in xmon */
		printf("cpus stopped:");
		count = 0;
		for (cpu = 0; cpu < NR_CPUS; ++cpu) {
			if (cpu_isset(cpu, cpus_in_xmon)) {
				if (count == 0)
					printf(" %x", cpu);
				++count;
			} else {
				if (count > 1)
					printf("-%x", cpu - 1);
				count = 0;
			}
		}
		if (count > 1)
			printf("-%x", NR_CPUS - 1);
		printf("\n");
		return 0;
	}
	/* try to switch to cpu specified */
	if (!cpu_isset(cpu, cpus_in_xmon)) {
		printf("cpu 0x%x isn't in xmon\n", cpu);
		return 0;
	}
	xmon_taken = 0;
	mb();
	xmon_owner = cpu;
	timeout = 10000000;
	while (!xmon_taken) {
		if (--timeout == 0) {
			if (test_and_set_bit(0, &xmon_taken))
				break;
			/* take control back */
			mb();
			xmon_owner = smp_processor_id();
			printf("cpu %u didn't take control\n", cpu);
			return 0;
		}
		barrier();
	}
	return 1;
#else
	return 0;
#endif /* CONFIG_SMP */
}