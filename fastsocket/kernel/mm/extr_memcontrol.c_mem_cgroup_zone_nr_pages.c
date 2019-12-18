#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zone {TYPE_1__* zone_pgdat; } ;
struct mem_cgroup_per_zone {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;
struct TYPE_2__ {int node_id; } ;

/* Variables and functions */
 unsigned long MEM_CGROUP_ZSTAT (struct mem_cgroup_per_zone*,int) ; 
 struct mem_cgroup_per_zone* mem_cgroup_zoneinfo (struct mem_cgroup*,int,int) ; 
 int zone_idx (struct zone*) ; 

unsigned long mem_cgroup_zone_nr_pages(struct mem_cgroup *memcg,
				       struct zone *zone,
				       enum lru_list lru)
{
	int nid = zone->zone_pgdat->node_id;
	int zid = zone_idx(zone);
	struct mem_cgroup_per_zone *mz = mem_cgroup_zoneinfo(memcg, nid, zid);

	return MEM_CGROUP_ZSTAT(mz, lru);
}