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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;
struct ixgbe_adapter {TYPE_2__ hw; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
#define  SIOCSHWTSTAMP 128 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int ixgbe_ptp_hwtstamp_ioctl (struct ixgbe_adapter*,struct ifreq*,int) ; 
 int mdio_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_ioctl(struct net_device *netdev, struct ifreq *req, int cmd)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	switch (cmd) {
#ifdef CONFIG_IXGBE_PTP
	case SIOCSHWTSTAMP:
		return ixgbe_ptp_hwtstamp_ioctl(adapter, req, cmd);
#endif
	default:
		return mdio_mii_ioctl(&adapter->hw.phy.mdio, if_mii(req), cmd);
	}
}