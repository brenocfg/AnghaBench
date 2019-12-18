#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_4__ {scalar_t__ no_desc; scalar_t__ flushed; scalar_t__ aggregated; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;
struct rx_queue {TYPE_2__ lro_mgr; } ;
struct TYPE_6__ {void* lro_no_desc; void* lro_flushed; void* lro_aggregated; } ;
struct mv643xx_eth_private {int rxq_count; TYPE_3__ lro_counters; struct rx_queue* rxq; } ;

/* Variables and functions */

__attribute__((used)) static void mv643xx_eth_grab_lro_stats(struct mv643xx_eth_private *mp)
{
	u32 lro_aggregated = 0;
	u32 lro_flushed = 0;
	u32 lro_no_desc = 0;
	int i;

	for (i = 0; i < mp->rxq_count; i++) {
		struct rx_queue *rxq = mp->rxq + i;

		lro_aggregated += rxq->lro_mgr.stats.aggregated;
		lro_flushed += rxq->lro_mgr.stats.flushed;
		lro_no_desc += rxq->lro_mgr.stats.no_desc;
	}

	mp->lro_counters.lro_aggregated = lro_aggregated;
	mp->lro_counters.lro_flushed = lro_flushed;
	mp->lro_counters.lro_no_desc = lro_no_desc;
}