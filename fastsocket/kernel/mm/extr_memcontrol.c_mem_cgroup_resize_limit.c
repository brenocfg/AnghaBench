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
struct mem_cgroup {int memsw_is_minimum; int /*<<< orphan*/  res; int /*<<< orphan*/  memsw; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEM_CGROUP_RECLAIM_RETRIES ; 
 int /*<<< orphan*/  MEM_CGROUP_RECLAIM_SHRINK ; 
 int /*<<< orphan*/  RES_LIMIT ; 
 int /*<<< orphan*/  RES_USAGE ; 
 int /*<<< orphan*/  current ; 
 int mem_cgroup_count_children (struct mem_cgroup*) ; 
 int mem_cgroup_reclaim (struct mem_cgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcg_oom_recover (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long long res_counter_read_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int res_counter_set_limit (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  set_limit_mutex ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mem_cgroup_resize_limit(struct mem_cgroup *memcg,
				unsigned long long val)
{
	int retry_count;
	int progress;
	u64 memswlimit, memlimit;
	int ret = 0;
	int children = mem_cgroup_count_children(memcg);
	u64 curusage, oldusage;
	int enlarge;

	/*
	 * For keeping hierarchical_reclaim simple, how long we should retry
	 * is depends on callers. We set our retry-count to be function
	 * of # of children which we should visit in this loop.
	 */
	retry_count = MEM_CGROUP_RECLAIM_RETRIES * children;

	oldusage = res_counter_read_u64(&memcg->res, RES_USAGE);

	enlarge = 0;
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
		memswlimit = res_counter_read_u64(&memcg->memsw, RES_LIMIT);
		if (memswlimit < val) {
			ret = -EINVAL;
			mutex_unlock(&set_limit_mutex);
			break;
		}

		memlimit = res_counter_read_u64(&memcg->res, RES_LIMIT);
		if (memlimit < val)
			enlarge = 1;

		ret = res_counter_set_limit(&memcg->res, val);
		if (!ret) {
			if (memswlimit == val)
				memcg->memsw_is_minimum = true;
			else
				memcg->memsw_is_minimum = false;
		}
		mutex_unlock(&set_limit_mutex);

		if (!ret)
			break;

		progress = mem_cgroup_reclaim(memcg, GFP_KERNEL,
					      MEM_CGROUP_RECLAIM_SHRINK);
		curusage = res_counter_read_u64(&memcg->res, RES_USAGE);
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