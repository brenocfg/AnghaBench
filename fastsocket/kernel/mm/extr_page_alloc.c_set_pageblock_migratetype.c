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
 int MIGRATE_UNMOVABLE ; 
 int /*<<< orphan*/  PB_migrate ; 
 int /*<<< orphan*/  PB_migrate_end ; 
 int /*<<< orphan*/  page_group_by_mobility_disabled ; 
 int /*<<< orphan*/  set_pageblock_flags_group (struct page*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_pageblock_migratetype(struct page *page, int migratetype)
{

	if (unlikely(page_group_by_mobility_disabled))
		migratetype = MIGRATE_UNMOVABLE;

	set_pageblock_flags_group(page, (unsigned long)migratetype,
					PB_migrate, PB_migrate_end);
}