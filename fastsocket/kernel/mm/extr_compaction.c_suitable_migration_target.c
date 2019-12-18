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
struct page {int dummy; } ;

/* Variables and functions */
 int MIGRATE_ISOLATE ; 
 int MIGRATE_MOVABLE ; 
 int MIGRATE_RESERVE ; 
 scalar_t__ PageBuddy (struct page*) ; 
 int get_pageblock_migratetype (struct page*) ; 
 scalar_t__ page_order (struct page*) ; 
 scalar_t__ pageblock_order ; 

__attribute__((used)) static bool suitable_migration_target(struct page *page)
{

	int migratetype = get_pageblock_migratetype(page);

	/* Don't interfere with memory hot-remove or the min_free_kbytes blocks */
	if (migratetype == MIGRATE_ISOLATE || migratetype == MIGRATE_RESERVE)
		return false;

	/* If the page is a large free page, then allow migration */
	if (PageBuddy(page) && page_order(page) >= pageblock_order)
		return true;

	/* If the block is MIGRATE_MOVABLE, allow migration */
	if (migratetype == MIGRATE_MOVABLE)
		return true;

	/* Otherwise skip the block */
	return false;
}