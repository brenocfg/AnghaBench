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
struct vmxnet3_adapter {TYPE_4__* tx_queue; TYPE_2__* rx_queue; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {TYPE_3__ tx_ring; } ;
struct TYPE_6__ {TYPE_1__* rx_ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_RX_RING_MAX_SIZE ; 
 int /*<<< orphan*/  VMXNET3_TX_RING_MAX_SIZE ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
vmxnet3_get_ringparam(struct net_device *netdev,
		      struct ethtool_ringparam *param)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	param->rx_max_pending = VMXNET3_RX_RING_MAX_SIZE;
	param->tx_max_pending = VMXNET3_TX_RING_MAX_SIZE;
	param->rx_mini_max_pending = 0;
	param->rx_jumbo_max_pending = 0;

	param->rx_pending = adapter->rx_queue[0].rx_ring[0].size;
	param->tx_pending = adapter->tx_queue[0].tx_ring.size;
	param->rx_mini_pending = 0;
	param->rx_jumbo_pending = 0;
}