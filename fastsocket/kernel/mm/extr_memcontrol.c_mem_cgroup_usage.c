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
typedef  int u64 ;
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_CGROUP_STAT_CACHE ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_RSS ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_SWAPOUT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  RES_USAGE ; 
 int mem_cgroup_get_recursive_idx_stat (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_is_root (struct mem_cgroup*) ; 
 int res_counter_read_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 mem_cgroup_usage(struct mem_cgroup *mem, bool swap)
{
	u64 val;

	if (!mem_cgroup_is_root(mem)) {
		if (!swap)
			return res_counter_read_u64(&mem->res, RES_USAGE);
		else
			return res_counter_read_u64(&mem->memsw, RES_USAGE);
	}

	val = mem_cgroup_get_recursive_idx_stat(mem, MEM_CGROUP_STAT_CACHE);
	val += mem_cgroup_get_recursive_idx_stat(mem, MEM_CGROUP_STAT_RSS);

	if (swap)
		val += mem_cgroup_get_recursive_idx_stat(mem,
				MEM_CGROUP_STAT_SWAPOUT);

	return val << PAGE_SHIFT;
}