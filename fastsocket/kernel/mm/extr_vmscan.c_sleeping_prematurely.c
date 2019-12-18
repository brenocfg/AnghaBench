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
struct TYPE_3__ {int nr_zones; struct zone* node_zones; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  high_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 
 scalar_t__ zone_is_all_unreclaimable (struct zone*) ; 
 int /*<<< orphan*/  zone_watermark_ok_safe (struct zone*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sleeping_prematurely(pg_data_t *pgdat, int order, long remaining)
{
	int i;

	/* If a direct reclaimer woke kswapd within HZ/10, it's premature */
	if (remaining)
		return 1;

	/* If after HZ/10, a zone is below the high mark, it's premature */
	for (i = 0; i < pgdat->nr_zones; i++) {
		struct zone *zone = pgdat->node_zones + i;

		if (!populated_zone(zone))
			continue;

		if (zone_is_all_unreclaimable(zone))
			continue;

		if (!zone_watermark_ok_safe(zone, order, high_wmark_pages(zone),
								0, 0))
			return 1;
	}

	return 0;
}