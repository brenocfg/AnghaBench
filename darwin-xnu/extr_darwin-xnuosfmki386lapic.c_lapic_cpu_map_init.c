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
 int MAX_CPUS ; 
 int MAX_LAPICIDS ; 
 int* cpu_to_lapic ; 
 int* lapic_to_cpu ; 

void
lapic_cpu_map_init(void)
{
	int	i;

	for (i = 0; i < MAX_CPUS; i++)
		cpu_to_lapic[i] = -1;
	for (i = 0; i < MAX_LAPICIDS; i++)
		lapic_to_cpu[i] = -1;
}