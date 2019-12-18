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
struct net_device {int dummy; } ;
struct myri10ge_priv {TYPE_4__* ss; } ;
struct ethtool_ringparam {scalar_t__ tx_max_pending; scalar_t__ tx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_max_pending; scalar_t__ rx_pending; scalar_t__ rx_mini_max_pending; scalar_t__ rx_mini_pending; } ;
struct TYPE_7__ {scalar_t__ mask; } ;
struct TYPE_6__ {scalar_t__ mask; } ;
struct TYPE_5__ {scalar_t__ mask; } ;
struct TYPE_8__ {TYPE_3__ tx; TYPE_2__ rx_big; TYPE_1__ rx_small; } ;

/* Variables and functions */
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
myri10ge_get_ringparam(struct net_device *netdev,
		       struct ethtool_ringparam *ring)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	ring->rx_mini_max_pending = mgp->ss[0].rx_small.mask + 1;
	ring->rx_max_pending = mgp->ss[0].rx_big.mask + 1;
	ring->rx_jumbo_max_pending = 0;
	ring->tx_max_pending = mgp->ss[0].tx.mask + 1;
	ring->rx_mini_pending = ring->rx_mini_max_pending;
	ring->rx_pending = ring->rx_max_pending;
	ring->rx_jumbo_pending = ring->rx_jumbo_max_pending;
	ring->tx_pending = ring->tx_max_pending;
}