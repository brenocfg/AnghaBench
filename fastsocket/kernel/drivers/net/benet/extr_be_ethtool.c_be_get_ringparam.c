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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct be_adapter {TYPE_4__* tx_obj; TYPE_2__* rx_obj; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_3__ q; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_1__ q; } ;

/* Variables and functions */
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void be_get_ringparam(struct net_device *netdev,
			     struct ethtool_ringparam *ring)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = ring->rx_pending = adapter->rx_obj[0].q.len;
	ring->tx_max_pending = ring->tx_pending = adapter->tx_obj[0].q.len;
}