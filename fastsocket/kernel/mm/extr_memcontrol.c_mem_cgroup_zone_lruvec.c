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
struct lruvec {int dummy; } ;
struct zone {struct lruvec lruvec; } ;
struct mem_cgroup_per_zone {struct lruvec lruvec; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup_per_zone* mem_cgroup_zoneinfo (struct mem_cgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_idx (struct zone*) ; 
 int /*<<< orphan*/  zone_to_nid (struct zone*) ; 

struct lruvec *mem_cgroup_zone_lruvec(struct zone *zone,
				      struct mem_cgroup *memcg)
{
	struct mem_cgroup_per_zone *mz;

	if (mem_cgroup_disabled())
		return &zone->lruvec;

	mz = mem_cgroup_zoneinfo(memcg, zone_to_nid(zone), zone_idx(zone));
	return &mz->lruvec;
}