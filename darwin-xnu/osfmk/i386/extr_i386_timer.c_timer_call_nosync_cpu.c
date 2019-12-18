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
 int /*<<< orphan*/  NOSYNC ; 
 int /*<<< orphan*/  cpu_to_cpumask (int) ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*),void*) ; 

void
timer_call_nosync_cpu(int cpu, void (*fn)(void *), void *arg)
{
	/* XXX Needs error checking and retry */
	mp_cpus_call(cpu_to_cpumask(cpu), NOSYNC, fn, arg);
}