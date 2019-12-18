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
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct skge_port {TYPE_2__ tx_ring; TYPE_1__ rx_ring; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RX_RING_SIZE ; 
 int /*<<< orphan*/  MAX_TX_RING_SIZE ; 
 struct skge_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void skge_get_ring_param(struct net_device *dev,
				struct ethtool_ringparam *p)
{
	struct skge_port *skge = netdev_priv(dev);

	p->rx_max_pending = MAX_RX_RING_SIZE;
	p->tx_max_pending = MAX_TX_RING_SIZE;
	p->rx_mini_max_pending = 0;
	p->rx_jumbo_max_pending = 0;

	p->rx_pending = skge->rx_ring.count;
	p->tx_pending = skge->tx_ring.count;
	p->rx_mini_pending = 0;
	p->rx_jumbo_pending = 0;
}