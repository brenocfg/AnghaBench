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
struct mem_cgroup {int dummy; } ;
struct cgroup {int dummy; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_swappiness (struct mem_cgroup*) ; 
 struct mem_cgroup* mem_cgroup_from_cont (struct cgroup*) ; 

__attribute__((used)) static u64 mem_cgroup_swappiness_read(struct cgroup *cgrp, struct cftype *cft)
{
	struct mem_cgroup *memcg = mem_cgroup_from_cont(cgrp);

	return get_swappiness(memcg);
}