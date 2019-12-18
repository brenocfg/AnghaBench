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
struct zone_reclaim_stat {int /*<<< orphan*/ * recent_rotated; int /*<<< orphan*/ * recent_scanned; } ;
struct zone {struct zone_reclaim_stat reclaim_stat; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct zone_reclaim_stat* mem_cgroup_get_reclaim_stat_from_page (struct page*) ; 

__attribute__((used)) static void update_page_reclaim_stat(struct zone *zone, struct page *page,
				     int file, int rotated)
{
	struct zone_reclaim_stat *reclaim_stat = &zone->reclaim_stat;
	struct zone_reclaim_stat *memcg_reclaim_stat;

	memcg_reclaim_stat = mem_cgroup_get_reclaim_stat_from_page(page);

	reclaim_stat->recent_scanned[file]++;
	if (rotated)
		reclaim_stat->recent_rotated[file]++;

	if (!memcg_reclaim_stat)
		return;

	memcg_reclaim_stat->recent_scanned[file]++;
	if (rotated)
		memcg_reclaim_stat->recent_rotated[file]++;
}