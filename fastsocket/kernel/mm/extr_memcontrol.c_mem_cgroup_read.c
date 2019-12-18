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
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;
struct cgroup {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 int MEMFILE_TYPE (int /*<<< orphan*/ ) ; 
 int RES_USAGE ; 
#define  _MEM 129 
#define  _MEMSWAP 128 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_usage (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  res_counter_read_u64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u64 mem_cgroup_read(struct cgroup *cont, struct cftype *cft)
{
	struct mem_cgroup *mem = mem_cgroup_from_cont(cont);
	u64 val;
	int type, name;

	type = MEMFILE_TYPE(cft->private);
	name = MEMFILE_ATTR(cft->private);
	switch (type) {
	case _MEM:
		if (name == RES_USAGE)
			val = mem_cgroup_usage(mem, false);
		else
			val = res_counter_read_u64(&mem->res, name);
		break;
	case _MEMSWAP:
		if (name == RES_USAGE)
			val = mem_cgroup_usage(mem, true);
		else
			val = res_counter_read_u64(&mem->memsw, name);
		break;
	default:
		BUG();
		break;
	}
	return val;
}