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
struct mem_cgroup_stat {struct mem_cgroup_stat_cpu* cpustat; } ;
struct mem_cgroup {struct mem_cgroup_stat stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_CGROUP_STAT_SWAPOUT ; 
 int /*<<< orphan*/  __mem_cgroup_stat_add_safe (struct mem_cgroup_stat_cpu*,int /*<<< orphan*/ ,int) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static void mem_cgroup_swap_statistics(struct mem_cgroup *mem,
					 bool charge)
{
	int val = (charge) ? 1 : -1;
	struct mem_cgroup_stat *stat = &mem->stat;
	struct mem_cgroup_stat_cpu *cpustat;
	int cpu = get_cpu();

	cpustat = &stat->cpustat[cpu];
	__mem_cgroup_stat_add_safe(cpustat, MEM_CGROUP_STAT_SWAPOUT, val);
	put_cpu();
}