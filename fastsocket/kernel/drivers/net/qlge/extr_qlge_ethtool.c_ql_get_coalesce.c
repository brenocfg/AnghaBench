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
struct ql_adapter {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 struct ql_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ql_get_coalesce(struct net_device *dev, struct ethtool_coalesce *c)
{
	struct ql_adapter *qdev = netdev_priv(dev);

	c->rx_coalesce_usecs = qdev->rx_coalesce_usecs;
	c->tx_coalesce_usecs = qdev->tx_coalesce_usecs;

	/* This chip coalesces as follows:
	 * If a packet arrives, hold off interrupts until
	 * cqicb->int_delay expires, but if no other packets arrive don't
	 * wait longer than cqicb->pkt_int_delay. But ethtool doesn't use a
	 * timer to coalesce on a frame basis.  So, we have to take ethtool's
	 * max_coalesced_frames value and convert it to a delay in microseconds.
	 * We do this by using a basic thoughput of 1,000,000 frames per
	 * second @ (1024 bytes).  This means one frame per usec. So it's a
	 * simple one to one ratio.
	 */
	c->rx_max_coalesced_frames = qdev->rx_max_coalesced_frames;
	c->tx_max_coalesced_frames = qdev->tx_max_coalesced_frames;

	return 0;
}