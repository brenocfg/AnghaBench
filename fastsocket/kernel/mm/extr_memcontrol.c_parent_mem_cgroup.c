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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct mem_cgroup {TYPE_1__ res; } ;

/* Variables and functions */
 struct mem_cgroup* mem_cgroup_from_res_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res ; 

__attribute__((used)) static struct mem_cgroup *parent_mem_cgroup(struct mem_cgroup *mem)
{
	if (!mem->res.parent)
		return NULL;
	return mem_cgroup_from_res_counter(mem->res.parent, res);
}