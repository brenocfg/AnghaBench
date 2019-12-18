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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long res_counter_soft_limit_excess (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned long mem_cgroup_get_excess(struct mem_cgroup *mem)
{
	return res_counter_soft_limit_excess(&mem->res) >> PAGE_SHIFT;
}