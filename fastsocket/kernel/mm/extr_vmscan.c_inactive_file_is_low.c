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
struct mem_cgroup_zone {int /*<<< orphan*/  zone; int /*<<< orphan*/  mem_cgroup; } ;

/* Variables and functions */
 int inactive_file_is_low_global (int /*<<< orphan*/ ) ; 
 int mem_cgroup_inactive_file_is_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scanning_global_lru (struct mem_cgroup_zone*) ; 

__attribute__((used)) static int inactive_file_is_low(struct mem_cgroup_zone *mz)
{
	if (!scanning_global_lru(mz))
		return mem_cgroup_inactive_file_is_low(mz->mem_cgroup,
						       mz->zone);

	return inactive_file_is_low_global(mz->zone);
}