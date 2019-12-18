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
struct mem_cgroup {int /*<<< orphan*/  res; } ;
struct cgroup {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 int MEMFILE_TYPE (int /*<<< orphan*/ ) ; 
#define  RES_LIMIT 129 
#define  RES_SOFT_LIMIT 128 
 int _MEM ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_is_root (struct mem_cgroup*) ; 
 int mem_cgroup_resize_limit (struct mem_cgroup*,unsigned long long) ; 
 int mem_cgroup_resize_memsw_limit (struct mem_cgroup*,unsigned long long) ; 
 int res_counter_memparse_write_strategy (char const*,unsigned long long*) ; 
 int res_counter_set_soft_limit (int /*<<< orphan*/ *,unsigned long long) ; 

__attribute__((used)) static int mem_cgroup_write(struct cgroup *cont, struct cftype *cft,
			    const char *buffer)
{
	struct mem_cgroup *memcg = mem_cgroup_from_cont(cont);
	int type, name;
	unsigned long long val;
	int ret;

	type = MEMFILE_TYPE(cft->private);
	name = MEMFILE_ATTR(cft->private);
	switch (name) {
	case RES_LIMIT:
		if (mem_cgroup_is_root(memcg)) { /* Can't set limit on root */
			ret = -EINVAL;
			break;
		}
		/* This function does all necessary parse...reuse it */
		ret = res_counter_memparse_write_strategy(buffer, &val);
		if (ret)
			break;
		if (type == _MEM)
			ret = mem_cgroup_resize_limit(memcg, val);
		else
			ret = mem_cgroup_resize_memsw_limit(memcg, val);
		break;
	case RES_SOFT_LIMIT:
		ret = res_counter_memparse_write_strategy(buffer, &val);
		if (ret)
			break;
		/*
		 * For memsw, soft limits are hard to implement in terms
		 * of semantics, for now, we support soft limits for
		 * control without swap
		 */
		if (type == _MEM)
			ret = res_counter_set_soft_limit(&memcg->res, val);
		else
			ret = -EINVAL;
		break;
	default:
		ret = -EINVAL; /* should be BUG() ? */
		break;
	}
	return ret;
}