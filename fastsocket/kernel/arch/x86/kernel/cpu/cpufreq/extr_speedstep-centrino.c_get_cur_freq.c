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
 int /*<<< orphan*/  MSR_IA32_PERF_CTL ; 
 int /*<<< orphan*/  MSR_IA32_PERF_STATUS ; 
 unsigned int extract_clock (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  rdmsr_on_cpu (unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int get_cur_freq(unsigned int cpu)
{
	unsigned l, h;
	unsigned clock_freq;

	rdmsr_on_cpu(cpu, MSR_IA32_PERF_STATUS, &l, &h);
	clock_freq = extract_clock(l, cpu, 0);

	if (unlikely(clock_freq == 0)) {
		/*
		 * On some CPUs, we can see transient MSR values (which are
		 * not present in _PSS), while CPU is doing some automatic
		 * P-state transition (like TM2). Get the last freq set 
		 * in PERF_CTL.
		 */
		rdmsr_on_cpu(cpu, MSR_IA32_PERF_CTL, &l, &h);
		clock_freq = extract_clock(l, cpu, 1);
	}
	return clock_freq;
}