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
struct zonelist {int /*<<< orphan*/ * _zonerefs; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_INTERLEAVE_HIT ; 
 struct page* __alloc_pages (int /*<<< orphan*/ ,unsigned int,struct zonelist*) ; 
 int /*<<< orphan*/  inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 struct zonelist* node_zonelist (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ page_zone (struct page*) ; 
 scalar_t__ zonelist_zone (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *alloc_page_interleave(gfp_t gfp, unsigned order,
					unsigned nid)
{
	struct zonelist *zl;
	struct page *page;

	zl = node_zonelist(nid, gfp);
	page = __alloc_pages(gfp, order, zl);
	if (page && page_zone(page) == zonelist_zone(&zl->_zonerefs[0]))
		inc_zone_page_state(page, NUMA_INTERLEAVE_HIT);
	return page;
}