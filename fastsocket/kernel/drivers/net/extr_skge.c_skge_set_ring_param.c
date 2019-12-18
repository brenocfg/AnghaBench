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
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct skge_port {TYPE_2__ tx_ring; TYPE_1__ rx_ring; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_RX_RING_SIZE ; 
 scalar_t__ MAX_TX_RING_SIZE ; 
 scalar_t__ TX_LOW_WATER ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skge_down (struct net_device*) ; 
 int skge_up (struct net_device*) ; 

__attribute__((used)) static int skge_set_ring_param(struct net_device *dev,
			       struct ethtool_ringparam *p)
{
	struct skge_port *skge = netdev_priv(dev);
	int err = 0;

	if (p->rx_pending == 0 || p->rx_pending > MAX_RX_RING_SIZE ||
	    p->tx_pending < TX_LOW_WATER || p->tx_pending > MAX_TX_RING_SIZE)
		return -EINVAL;

	skge->rx_ring.count = p->rx_pending;
	skge->tx_ring.count = p->tx_pending;

	if (netif_running(dev)) {
		skge_down(dev);
		err = skge_up(dev);
		if (err)
			dev_close(dev);
	}

	return err;
}