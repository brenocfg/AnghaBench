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
struct TYPE_2__ {struct cgroup* cgroup; } ;
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; int /*<<< orphan*/  use_hierarchy; TYPE_1__ css; } ;
struct cgroup {struct cgroup* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_LIMIT ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 
 unsigned long long min (unsigned long long,unsigned long long) ; 
 unsigned long long res_counter_read_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void memcg_get_hierarchical_limit(struct mem_cgroup *memcg,
		unsigned long long *mem_limit, unsigned long long *memsw_limit)
{
	struct cgroup *cgroup;
	unsigned long long min_limit, min_memsw_limit, tmp;

	min_limit = res_counter_read_u64(&memcg->res, RES_LIMIT);
	min_memsw_limit = res_counter_read_u64(&memcg->memsw, RES_LIMIT);
	cgroup = memcg->css.cgroup;
	if (!memcg->use_hierarchy)
		goto out;

	while (cgroup->parent) {
		cgroup = cgroup->parent;
		memcg = mem_cgroup_from_cont(cgroup);
		if (!memcg->use_hierarchy)
			break;
		tmp = res_counter_read_u64(&memcg->res, RES_LIMIT);
		min_limit = min(min_limit, tmp);
		tmp = res_counter_read_u64(&memcg->memsw, RES_LIMIT);
		min_memsw_limit = min(min_memsw_limit, tmp);
	}
out:
	*mem_limit = min_limit;
	*memsw_limit = min_memsw_limit;
	return;
}