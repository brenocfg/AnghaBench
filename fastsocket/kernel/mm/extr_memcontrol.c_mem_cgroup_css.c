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
struct cgroup_subsys_state {int dummy; } ;
struct mem_cgroup {struct cgroup_subsys_state css; } ;

/* Variables and functions */

struct cgroup_subsys_state *mem_cgroup_css(struct mem_cgroup *mem)
{
	return &mem->css;
}