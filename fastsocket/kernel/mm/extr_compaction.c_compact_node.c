#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zone {int dummy; } ;
struct compact_control {int order; int sync; int /*<<< orphan*/  migratepages; int /*<<< orphan*/  freepages; struct zone* zone; int /*<<< orphan*/  nr_migratepages; int /*<<< orphan*/  nr_freepages; } ;
struct TYPE_3__ {struct zone* node_zones; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_NR_ZONES ; 
 TYPE_1__* NODE_DATA (int) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __reset_isolation_suitable (struct zone*) ; 
 int /*<<< orphan*/  compact_zone (struct zone*,struct compact_control*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_add_drain_all () ; 
 int /*<<< orphan*/  node_online (int) ; 
 int nr_node_ids ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 

__attribute__((used)) static int compact_node(int nid)
{
	int zoneid;
	pg_data_t *pgdat;
	struct zone *zone;

	if (nid < 0 || nid >= nr_node_ids || !node_online(nid))
		return -EINVAL;
	pgdat = NODE_DATA(nid);

	/* Flush pending updates to the LRU lists */
	lru_add_drain_all();

	for (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) {
		struct compact_control cc = {
			.nr_freepages = 0,
			.nr_migratepages = 0,
			.order = -1,
			.sync = true,
		};

		zone = &pgdat->node_zones[zoneid];
		if (!populated_zone(zone))
			continue;

		cc.zone = zone;
		INIT_LIST_HEAD(&cc.freepages);
		INIT_LIST_HEAD(&cc.migratepages);

		__reset_isolation_suitable(zone);
		compact_zone(zone, &cc);

		VM_BUG_ON(!list_empty(&cc.freepages));
		VM_BUG_ON(!list_empty(&cc.migratepages));
	}

	return 0;
}