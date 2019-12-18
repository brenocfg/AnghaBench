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
struct mem_cgroup_zone {int /*<<< orphan*/  mem_cgroup; int /*<<< orphan*/  zone; } ;
struct lruvec {int /*<<< orphan*/ * lists; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  isolate_mode_t ;

/* Variables and functions */
 scalar_t__ LRU_ACTIVE ; 
 int LRU_BASE ; 
 scalar_t__ LRU_FILE ; 
 unsigned long isolate_lru_pages (unsigned long,int /*<<< orphan*/ *,struct list_head*,unsigned long*,int,int /*<<< orphan*/ ,int) ; 
 struct lruvec* mem_cgroup_zone_lruvec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long isolate_pages(unsigned long nr, struct mem_cgroup_zone *mz,
				   struct list_head *dst,
				   unsigned long *scanned, int order,
				   isolate_mode_t mode, int active, int file)
{
	struct lruvec *lruvec;
	int lru = LRU_BASE;

	lruvec = mem_cgroup_zone_lruvec(mz->zone, mz->mem_cgroup);
	if (active)
		lru += LRU_ACTIVE;
	if (file)
		lru += LRU_FILE;
	return isolate_lru_pages(nr, &lruvec->lists[lru], dst,
				 scanned, order, mode, file);
}