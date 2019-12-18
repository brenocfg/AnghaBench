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
 int BAD_APICID ; 
 int* cpu_2_logical_apicid ; 
 int logical_smp_processor_id () ; 
 int nr_cpu_ids ; 

__attribute__((used)) static int es7000_cpu_to_logical_apicid(int cpu)
{
#ifdef CONFIG_SMP
	if (cpu >= nr_cpu_ids)
		return BAD_APICID;
	return cpu_2_logical_apicid[cpu];
#else
	return logical_smp_processor_id();
#endif
}