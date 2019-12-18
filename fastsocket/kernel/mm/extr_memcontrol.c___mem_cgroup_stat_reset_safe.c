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
struct mem_cgroup_stat_cpu {scalar_t__* count; } ;
typedef  enum mem_cgroup_stat_index { ____Placeholder_mem_cgroup_stat_index } mem_cgroup_stat_index ;

/* Variables and functions */

__attribute__((used)) static inline void
__mem_cgroup_stat_reset_safe(struct mem_cgroup_stat_cpu *stat,
				enum mem_cgroup_stat_index idx)
{
	stat->count[idx] = 0;
}