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
typedef  struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  use_hierarchy; } const mem_cgroup ;

/* Variables and functions */
 int css_is_ancestor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool __mem_cgroup_same_or_subtree(const struct mem_cgroup *root_memcg,
				  struct mem_cgroup *memcg)
{
	if (root_memcg == memcg)
		return true;
	if (!root_memcg->use_hierarchy || !memcg)
		return false;
	return css_is_ancestor(&memcg->css, &root_memcg->css);
}