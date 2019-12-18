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
typedef  unsigned long long u64 ;
struct mem_cgroup {int memsw_is_minimum; int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEM_CGROUP_RECLAIM_NOSWAP ; 
 int MEM_CGROUP_RECLAIM_RETRIES ; 
 int MEM_CGROUP_RECLAIM_SHRINK ; 
 int /*<<< orphan*/  RES_LIMIT ; 
 int /*<<< orphan*/  RES_USAGE ; 
 int /*<<< orphan*/  current ; 
 int mem_cgroup_count_children (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_reclaim (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcg_oom_recover (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long long res_counter_read_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int res_counter_set_limit (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  set_limit_mutex ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mem_cgroup_resize_memsw_limit(struct mem_cgroup *memcg,
					unsigned long long val)
{
	int retry_count;
	u64 memlimit, memswlimit, oldusage, curusage;
	int children = mem_cgroup_count_children(memcg);
	int ret = -EBUSY;
	int enlarge = 0;

	/* see mem_cgroup_resize_res_limit */
 	retry_count = children * MEM_CGROUP_RECLAIM_RETRIES;
	oldusage = res_counter_read_u64(&memcg->memsw, RES_USAGE);
	while (retry_count) {
		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}
		/*
		 * Rather than hide all in some function, I do this in
		 * open coded manner. You see what this really does.
		 * We have to guarantee mem->res.limit < mem->memsw.limit.
		 */
		mutex_lock(&set_limit_mutex);
		memlimit = res_counter_read_u64(&memcg->res, RES_LIMIT);
		if (memlimit > val) {
			ret = -EINVAL;
			mutex_unlock(&set_limit_mutex);
			break;
		}
		memswlimit = res_counter_read_u64(&memcg->memsw, RES_LIMIT);
		if (memswlimit < val)
			enlarge = 1;
		ret = res_counter_set_limit(&memcg->memsw, val);
		if (!ret) {
			if (memlimit == val)
				memcg->memsw_is_minimum = true;
			else
				memcg->memsw_is_minimum = false;
		}
		mutex_unlock(&set_limit_mutex);

		if (!ret)
			break;

		mem_cgroup_reclaim(memcg, GFP_KERNEL,
				   MEM_CGROUP_RECLAIM_NOSWAP |
				   MEM_CGROUP_RECLAIM_SHRINK);
		curusage = res_counter_read_u64(&memcg->memsw, RES_USAGE);
		/* Usage is reduced ? */
		if (curusage >= oldusage)
			retry_count--;
		else
			oldusage = curusage;
	}
	if (!ret && enlarge)
		memcg_oom_recover(memcg);
	return ret;
}