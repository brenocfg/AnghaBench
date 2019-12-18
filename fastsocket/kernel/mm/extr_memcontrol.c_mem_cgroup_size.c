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
struct mem_cgroup_stat_cpu {int dummy; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int nr_cpu_ids ; 

__attribute__((used)) static int mem_cgroup_size(void)
{
	int cpustat_size = nr_cpu_ids * sizeof(struct mem_cgroup_stat_cpu);
	return sizeof(struct mem_cgroup) + cpustat_size;
}