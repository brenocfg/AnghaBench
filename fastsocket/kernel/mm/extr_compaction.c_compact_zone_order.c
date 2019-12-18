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
struct compact_control {int order; int sync; int contended; int /*<<< orphan*/  migratepages; int /*<<< orphan*/  freepages; struct zone* zone; int /*<<< orphan*/  migratetype; int /*<<< orphan*/  nr_migratepages; int /*<<< orphan*/  nr_freepages; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  allocflags_to_migratetype (int /*<<< orphan*/ ) ; 
 unsigned long compact_zone (struct zone*,struct compact_control*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

unsigned long compact_zone_order(struct zone *zone,
				 int order, gfp_t gfp_mask,
				 bool sync, bool *contended)
{
	unsigned long ret;
	struct compact_control cc = {
		.nr_freepages = 0,
		.nr_migratepages = 0,
		.order = order,
		.migratetype = allocflags_to_migratetype(gfp_mask),
		.zone = zone,
		.sync = sync,
	};
	INIT_LIST_HEAD(&cc.freepages);
	INIT_LIST_HEAD(&cc.migratepages);

	ret = compact_zone(zone, &cc);

	VM_BUG_ON(!list_empty(&cc.freepages));
	VM_BUG_ON(!list_empty(&cc.migratepages));

	*contended = cc.contended;
	return ret;
}