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
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int NR_LRU_BASE ; 
 unsigned long mem_cgroup_zone_nr_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scanning_global_lru (struct mem_cgroup_zone*) ; 
 unsigned long zone_page_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long zone_nr_lru_pages(struct mem_cgroup_zone *mz,
				       enum lru_list lru)
{
	if (!scanning_global_lru(mz))
		return mem_cgroup_zone_nr_pages(mz->mem_cgroup, mz->zone, lru);

	return zone_page_state(mz->zone, NR_LRU_BASE + lru);
}