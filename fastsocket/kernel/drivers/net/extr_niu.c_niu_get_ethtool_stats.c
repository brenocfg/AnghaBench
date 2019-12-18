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
typedef  int /*<<< orphan*/  u64 ;
struct tx_ring_info {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_channel; } ;
struct rx_ring_info {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_channel; } ;
struct niu_xmac_stats {int dummy; } ;
struct niu_bmac_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bmac; int /*<<< orphan*/  xmac; } ;
struct niu {int flags; int num_rx_rings; int num_tx_rings; struct tx_ring_info* tx_rings; struct rx_ring_info* rx_rings; TYPE_1__ mac_stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  niu_sync_mac_stats (struct niu*) ; 
 int /*<<< orphan*/  niu_sync_rx_discard_stats (struct niu*,struct rx_ring_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_get_ethtool_stats(struct net_device *dev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct niu *np = netdev_priv(dev);
	int i;

	niu_sync_mac_stats(np);
	if (np->flags & NIU_FLAGS_XMAC) {
		memcpy(data, &np->mac_stats.xmac,
		       sizeof(struct niu_xmac_stats));
		data += (sizeof(struct niu_xmac_stats) / sizeof(u64));
	} else {
		memcpy(data, &np->mac_stats.bmac,
		       sizeof(struct niu_bmac_stats));
		data += (sizeof(struct niu_bmac_stats) / sizeof(u64));
	}
	for (i = 0; i < np->num_rx_rings; i++) {
		struct rx_ring_info *rp = &np->rx_rings[i];

		niu_sync_rx_discard_stats(np, rp, 0);

		data[0] = rp->rx_channel;
		data[1] = rp->rx_packets;
		data[2] = rp->rx_bytes;
		data[3] = rp->rx_dropped;
		data[4] = rp->rx_errors;
		data += 5;
	}
	for (i = 0; i < np->num_tx_rings; i++) {
		struct tx_ring_info *rp = &np->tx_rings[i];

		data[0] = rp->tx_channel;
		data[1] = rp->tx_packets;
		data[2] = rp->tx_bytes;
		data[3] = rp->tx_errors;
		data += 4;
	}
}