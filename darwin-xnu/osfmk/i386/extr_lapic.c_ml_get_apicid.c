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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ MAX_CPUS ; 
 scalar_t__* cpu_to_lapic ; 

uint32_t
ml_get_apicid(uint32_t cpu)
{
	if(cpu >= (uint32_t)MAX_CPUS)
		return 0xFFFFFFFF;	/* Return -1 if cpu too big */
	
	/* Return the apic ID (or -1 if not configured) */
	return (uint32_t)cpu_to_lapic[cpu];

}