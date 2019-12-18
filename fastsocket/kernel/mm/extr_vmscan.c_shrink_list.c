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
struct scan_control {int dummy; } ;
struct mem_cgroup_zone {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 scalar_t__ inactive_list_is_low (struct mem_cgroup_zone*,int) ; 
 scalar_t__ is_active_lru (int) ; 
 int is_file_lru (int) ; 
 int /*<<< orphan*/  shrink_active_list (unsigned long,struct mem_cgroup_zone*,struct scan_control*,int,int) ; 
 unsigned long shrink_inactive_list (unsigned long,struct mem_cgroup_zone*,struct scan_control*,int,int) ; 

__attribute__((used)) static unsigned long shrink_list(enum lru_list lru, unsigned long nr_to_scan,
				 struct mem_cgroup_zone *mz,
				 struct scan_control *sc, int priority)
{
	int file = is_file_lru(lru);

	if (is_active_lru(lru)) {
		if (inactive_list_is_low(mz, file))
			shrink_active_list(nr_to_scan, mz, sc, priority, file);
		return 0;
	}

	return shrink_inactive_list(nr_to_scan, mz, sc, priority, file);
}