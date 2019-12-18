#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device_stats {scalar_t__ rx_fifo_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; scalar_t__ tx_errors; scalar_t__ rx_errors; } ;
struct TYPE_8__ {TYPE_3__* bna_stats; } ;
struct bnad {TYPE_4__ stats; int /*<<< orphan*/  bna; } ;
struct bfi_enet_stats_mac {scalar_t__ rx_alignment_error; scalar_t__ rx_fcs_error; scalar_t__ rx_frame_length_error; int /*<<< orphan*/  tx_total_collision; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  rx_drop; scalar_t__ tx_undersize; scalar_t__ tx_fcs_error; scalar_t__ rx_undersize; scalar_t__ rx_code_error; } ;
struct TYPE_6__ {TYPE_1__* rxf_stats; struct bfi_enet_stats_mac mac_stats; } ;
struct TYPE_7__ {TYPE_2__ hw_stats; } ;
struct TYPE_5__ {scalar_t__ frame_drops; } ;

/* Variables and functions */
 int bna_rx_rid_mask (int /*<<< orphan*/ *) ; 

void
bnad_netdev_hwstats_fill(struct bnad *bnad, struct net_device_stats *stats)
{
	struct bfi_enet_stats_mac *mac_stats;
	u32 bmap;
	int i;

	mac_stats = &bnad->stats.bna_stats->hw_stats.mac_stats;
	stats->rx_errors =
		mac_stats->rx_fcs_error + mac_stats->rx_alignment_error +
		mac_stats->rx_frame_length_error + mac_stats->rx_code_error +
		mac_stats->rx_undersize;
	stats->tx_errors = mac_stats->tx_fcs_error +
					mac_stats->tx_undersize;
	stats->rx_dropped = mac_stats->rx_drop;
	stats->tx_dropped = mac_stats->tx_drop;
	stats->multicast = mac_stats->rx_multicast;
	stats->collisions = mac_stats->tx_total_collision;

	stats->rx_length_errors = mac_stats->rx_frame_length_error;

	/* receive ring buffer overflow  ?? */

	stats->rx_crc_errors = mac_stats->rx_fcs_error;
	stats->rx_frame_errors = mac_stats->rx_alignment_error;
	/* recv'r fifo overrun */
	bmap = bna_rx_rid_mask(&bnad->bna);
	stats->rx_fifo_errors = 0;
	for (i = 0; bmap; i++) {
		if (bmap & 1) {
			stats->rx_fifo_errors +=
				bnad->stats.bna_stats->
					hw_stats.rxf_stats[i].frame_drops;
			break;
		}
		bmap >>= 1;
	}
}