#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int core_id; int proc_id; } ;

/* Variables and functions */
#define  CPUINFO_LVL_CORE 131 
#define  CPUINFO_LVL_NODE 130 
#define  CPUINFO_LVL_PROC 129 
#define  CPUINFO_LVL_ROOT 128 
 int EINVAL ; 
 TYPE_1__ cpu_data (int) ; 
 int cpu_to_node (int) ; 

__attribute__((used)) static int cpuinfo_id(int cpu, int level)
{
	int id;

	switch (level) {
	case CPUINFO_LVL_ROOT:
		id = 0;
		break;
	case CPUINFO_LVL_NODE:
		id = cpu_to_node(cpu);
		break;
	case CPUINFO_LVL_CORE:
		id = cpu_data(cpu).core_id;
		break;
	case CPUINFO_LVL_PROC:
		id = cpu_data(cpu).proc_id;
		break;
	default:
		id = -EINVAL;
	}
	return id;
}