#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zone {TYPE_1__* zone_pgdat; } ;
struct TYPE_2__ {int kswapd_max_order; int /*<<< orphan*/  kswapd_wait; int /*<<< orphan*/  node_id; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpuset_zone_allowed_hardwall (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  low_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 
 int /*<<< orphan*/  trace_mm_vmscan_wakeup_kswapd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zone_idx (struct zone*) ; 
 scalar_t__ zone_watermark_ok_safe (struct zone*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wakeup_kswapd(struct zone *zone, int order)
{
	pg_data_t *pgdat;

	if (!populated_zone(zone))
		return;

	if (!cpuset_zone_allowed_hardwall(zone, GFP_KERNEL))
		return;
	pgdat = zone->zone_pgdat;
	if (pgdat->kswapd_max_order < order)
		pgdat->kswapd_max_order = order;
	if (!waitqueue_active(&pgdat->kswapd_wait))
		return;
	if (zone_watermark_ok_safe(zone, order, low_wmark_pages(zone), 0, 0))
		return;

	trace_mm_vmscan_wakeup_kswapd(pgdat->node_id, zone_idx(zone), order);
	wake_up_interruptible(&pgdat->kswapd_wait);
}