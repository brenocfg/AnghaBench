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
struct mem_cgroup {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_cgroup_free (struct mem_cgroup*) ; 
 scalar_t__ atomic_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_cgroup_put (struct mem_cgroup*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 

__attribute__((used)) static void __mem_cgroup_put(struct mem_cgroup *mem, int count)
{
	if (atomic_sub_and_test(count, &mem->refcnt)) {
		struct mem_cgroup *parent = parent_mem_cgroup(mem);
		__mem_cgroup_free(mem);
		if (parent)
			mem_cgroup_put(parent);
	}
}