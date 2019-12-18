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
typedef  int /*<<< orphan*/  u64 ;
struct cpuset {int /*<<< orphan*/  fmeter; } ;
struct cgroup {int dummy; } ;
struct cftype {int private; } ;
typedef  int cpuset_filetype_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FILE_CPU_EXCLUSIVE 136 
#define  FILE_MEMORY_MIGRATE 135 
#define  FILE_MEMORY_PRESSURE 134 
#define  FILE_MEMORY_PRESSURE_ENABLED 133 
#define  FILE_MEM_EXCLUSIVE 132 
#define  FILE_MEM_HARDWALL 131 
#define  FILE_SCHED_LOAD_BALANCE 130 
#define  FILE_SPREAD_PAGE 129 
#define  FILE_SPREAD_SLAB 128 
 struct cpuset* cgroup_cs (struct cgroup*) ; 
 int /*<<< orphan*/  cpuset_memory_pressure_enabled ; 
 int /*<<< orphan*/  fmeter_getrate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_cpu_exclusive (struct cpuset*) ; 
 int /*<<< orphan*/  is_mem_exclusive (struct cpuset*) ; 
 int /*<<< orphan*/  is_mem_hardwall (struct cpuset*) ; 
 int /*<<< orphan*/  is_memory_migrate (struct cpuset*) ; 
 int /*<<< orphan*/  is_sched_load_balance (struct cpuset*) ; 
 int /*<<< orphan*/  is_spread_page (struct cpuset*) ; 
 int /*<<< orphan*/  is_spread_slab (struct cpuset*) ; 

__attribute__((used)) static u64 cpuset_read_u64(struct cgroup *cont, struct cftype *cft)
{
	struct cpuset *cs = cgroup_cs(cont);
	cpuset_filetype_t type = cft->private;
	switch (type) {
	case FILE_CPU_EXCLUSIVE:
		return is_cpu_exclusive(cs);
	case FILE_MEM_EXCLUSIVE:
		return is_mem_exclusive(cs);
	case FILE_MEM_HARDWALL:
		return is_mem_hardwall(cs);
	case FILE_SCHED_LOAD_BALANCE:
		return is_sched_load_balance(cs);
	case FILE_MEMORY_MIGRATE:
		return is_memory_migrate(cs);
	case FILE_MEMORY_PRESSURE_ENABLED:
		return cpuset_memory_pressure_enabled;
	case FILE_MEMORY_PRESSURE:
		return fmeter_getrate(&cs->fmeter);
	case FILE_SPREAD_PAGE:
		return is_spread_page(cs);
	case FILE_SPREAD_SLAB:
		return is_spread_slab(cs);
	default:
		BUG();
	}

	/* Unreachable but makes gcc happy */
	return 0;
}