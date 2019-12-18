#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stmmac_extra_stats {int /*<<< orphan*/  tx_deferred; int /*<<< orphan*/  tx_heartbeat; int /*<<< orphan*/  tx_losscarrier; int /*<<< orphan*/  tx_carrier; int /*<<< orphan*/  tx_underflow; } ;
struct net_device_stats {int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_fifo_errors; } ;
struct TYPE_3__ {int error_summary; int underflow_error; int no_carrier; int loss_carrier; int heartbeat_fail; int deferred; scalar_t__ collision_count; scalar_t__ late_collision; scalar_t__ excessive_collisions; scalar_t__ excessive_deferral; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct dma_desc {TYPE_2__ des01; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mac100_get_tx_frame_status(void *data, struct stmmac_extra_stats *x,
				      struct dma_desc *p, unsigned long ioaddr)
{
	int ret = 0;
	struct net_device_stats *stats = (struct net_device_stats *)data;

	if (unlikely(p->des01.tx.error_summary)) {
		if (unlikely(p->des01.tx.underflow_error)) {
			x->tx_underflow++;
			stats->tx_fifo_errors++;
		}
		if (unlikely(p->des01.tx.no_carrier)) {
			x->tx_carrier++;
			stats->tx_carrier_errors++;
		}
		if (unlikely(p->des01.tx.loss_carrier)) {
			x->tx_losscarrier++;
			stats->tx_carrier_errors++;
		}
		if (unlikely((p->des01.tx.excessive_deferral) ||
			     (p->des01.tx.excessive_collisions) ||
			     (p->des01.tx.late_collision)))
			stats->collisions += p->des01.tx.collision_count;
		ret = -1;
	}
	if (unlikely(p->des01.tx.heartbeat_fail)) {
		x->tx_heartbeat++;
		stats->tx_heartbeat_errors++;
		ret = -1;
	}
	if (unlikely(p->des01.tx.deferred))
		x->tx_deferred++;

	return ret;
}