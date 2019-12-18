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
struct zone_reclaim_stat {int dummy; } ;
struct page_cgroup {int /*<<< orphan*/  mem_cgroup; } ;
struct page {int dummy; } ;
struct mem_cgroup_per_zone {struct zone_reclaim_stat reclaim_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageCgroupUsed (struct page_cgroup*) ; 
 struct page_cgroup* lookup_page_cgroup (struct page*) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup_per_zone* page_cgroup_zoneinfo (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

struct zone_reclaim_stat *
mem_cgroup_get_reclaim_stat_from_page(struct page *page)
{
	struct page_cgroup *pc;
	struct mem_cgroup_per_zone *mz;

	if (mem_cgroup_disabled())
		return NULL;

	pc = lookup_page_cgroup(page);
	if (!PageCgroupUsed(pc))
		return NULL;
	/* Ensure pc->mem_cgroup is visible after reading PCG_USED. */
	smp_rmb();
	mz = page_cgroup_zoneinfo(pc->mem_cgroup, page);
	if (!mz)
		return NULL;

	return &mz->reclaim_stat;
}