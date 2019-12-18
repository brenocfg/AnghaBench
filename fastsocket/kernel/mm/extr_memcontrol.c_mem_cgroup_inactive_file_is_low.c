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
struct zone {int dummy; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_ACTIVE_FILE ; 
 int /*<<< orphan*/  LRU_INACTIVE_FILE ; 
 unsigned long mem_cgroup_zone_nr_pages (struct mem_cgroup*,struct zone*,int /*<<< orphan*/ ) ; 

int mem_cgroup_inactive_file_is_low(struct mem_cgroup *memcg, struct zone *zone)
{
	unsigned long active;
	unsigned long inactive;

	inactive = mem_cgroup_zone_nr_pages(memcg, zone, LRU_INACTIVE_FILE);
	active = mem_cgroup_zone_nr_pages(memcg, zone, LRU_ACTIVE_FILE);

	return (active > inactive);
}