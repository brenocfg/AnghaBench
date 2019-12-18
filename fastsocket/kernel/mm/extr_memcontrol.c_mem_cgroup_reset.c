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
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int MEMFILE_ATTR (unsigned int) ; 
 int MEMFILE_TYPE (unsigned int) ; 
#define  RES_FAILCNT 129 
#define  RES_MAX_USAGE 128 
 int _MEM ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 
 int /*<<< orphan*/  res_counter_reset_failcnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_counter_reset_max (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mem_cgroup_reset(struct cgroup *cont, unsigned int event)
{
	struct mem_cgroup *mem;
	int type, name;

	mem = mem_cgroup_from_cont(cont);
	type = MEMFILE_TYPE(event);
	name = MEMFILE_ATTR(event);
	switch (name) {
	case RES_MAX_USAGE:
		if (type == _MEM)
			res_counter_reset_max(&mem->res);
		else
			res_counter_reset_max(&mem->memsw);
		break;
	case RES_FAILCNT:
		if (type == _MEM)
			res_counter_reset_failcnt(&mem->res);
		else
			res_counter_reset_failcnt(&mem->memsw);
		break;
	}

	return 0;
}