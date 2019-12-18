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
struct TYPE_2__ {int /*<<< orphan*/  rx_pause_enable; int /*<<< orphan*/  tx_pause_enable; } ;
struct vxgedev {TYPE_1__ config; int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct __vxge_hw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 
 scalar_t__ pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_device_setpause_data (struct __vxge_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxge_ethtool_setpause_data(struct net_device *dev,
					struct ethtool_pauseparam *ep)
{
	struct vxgedev *vdev = (struct vxgedev *)netdev_priv(dev);
	struct __vxge_hw_device  *hldev = (struct __vxge_hw_device  *)
			pci_get_drvdata(vdev->pdev);

	vxge_hw_device_setpause_data(hldev, 0, ep->tx_pause, ep->rx_pause);

	vdev->config.tx_pause_enable = ep->tx_pause;
	vdev->config.rx_pause_enable = ep->rx_pause;

	return 0;
}