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
struct net_device {int dummy; } ;
struct nes_vnic {TYPE_1__* nesdev; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; scalar_t__ autoneg; } ;
struct TYPE_2__ {scalar_t__ disable_rx_flow_control; scalar_t__ disable_tx_flow_control; } ;

/* Variables and functions */
 struct nes_vnic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nes_netdev_get_pauseparam(struct net_device *netdev,
		struct ethtool_pauseparam *et_pauseparam)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);

	et_pauseparam->autoneg = 0;
	et_pauseparam->rx_pause = (nesvnic->nesdev->disable_rx_flow_control == 0) ? 1:0;
	et_pauseparam->tx_pause = (nesvnic->nesdev->disable_tx_flow_control == 0) ? 1:0;
}