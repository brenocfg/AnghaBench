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
typedef  int u32 ;

/* Variables and functions */
 int MHZ (int) ; 
 void* find_node_by_devtype (void*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  setprop_val (void*,char*,int) ; 
 int timebase_period_ns ; 

void dt_fixup_cpu_clocks(u32 cpu, u32 tb, u32 bus)
{
	void *devp = NULL;

	printf("CPU clock-frequency <- 0x%x (%dMHz)\n\r", cpu, MHZ(cpu));
	printf("CPU timebase-frequency <- 0x%x (%dMHz)\n\r", tb, MHZ(tb));
	if (bus > 0)
		printf("CPU bus-frequency <- 0x%x (%dMHz)\n\r", bus, MHZ(bus));

	while ((devp = find_node_by_devtype(devp, "cpu"))) {
		setprop_val(devp, "clock-frequency", cpu);
		setprop_val(devp, "timebase-frequency", tb);
		if (bus > 0)
			setprop_val(devp, "bus-frequency", bus);
	}

	timebase_period_ns = 1000000000 / tb;
}