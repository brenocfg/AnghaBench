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
struct mem_cgroup_stat {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_CGROUP_STAT_CACHE ; 
 int /*<<< orphan*/  MEM_CGROUP_STAT_RSS ; 
 scalar_t__ mem_cgroup_read_stat (struct mem_cgroup_stat*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 mem_cgroup_local_usage(struct mem_cgroup_stat *stat)
{
	s64 ret;

	ret = mem_cgroup_read_stat(stat, MEM_CGROUP_STAT_CACHE);
	ret += mem_cgroup_read_stat(stat, MEM_CGROUP_STAT_RSS);
	return ret;
}