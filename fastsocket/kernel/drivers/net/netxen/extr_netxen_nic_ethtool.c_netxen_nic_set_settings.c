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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ port_type; } ;
struct netxen_adapter {int capabilities; int /*<<< orphan*/  link_autoneg; int /*<<< orphan*/  link_duplex; int /*<<< orphan*/  link_speed; TYPE_1__ ahw; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
struct ethtool_cmd {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; } ;
struct TYPE_4__ {int (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ NETXEN_NIC_GBE ; 
 int NX_FW_CAPABILITY_GBE_LINK_CFG ; 
 int NX_RCODE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ethtool_cmd_speed (struct ethtool_cmd*) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int nx_fw_cmd_set_gbe_port (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int stub2 (struct net_device*) ; 

__attribute__((used)) static int
netxen_nic_set_settings(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	u32 speed = ethtool_cmd_speed(ecmd);
	int ret;

	if (adapter->ahw.port_type != NETXEN_NIC_GBE)
		return -EOPNOTSUPP;

	if (!(adapter->capabilities & NX_FW_CAPABILITY_GBE_LINK_CFG))
		return -EOPNOTSUPP;

	ret = nx_fw_cmd_set_gbe_port(adapter, speed, ecmd->duplex,
				     ecmd->autoneg);
	if (ret == NX_RCODE_NOT_SUPPORTED)
		return -EOPNOTSUPP;
	else if (ret)
		return -EIO;

	adapter->link_speed = speed;
	adapter->link_duplex = ecmd->duplex;
	adapter->link_autoneg = ecmd->autoneg;

	if (!netif_running(dev))
		return 0;

	dev->netdev_ops->ndo_stop(dev);
	return dev->netdev_ops->ndo_open(dev);
}