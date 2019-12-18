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
struct ethtool_cmd {scalar_t__ phy_address; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; int /*<<< orphan*/  supported; } ;
struct TYPE_2__ {scalar_t__ address; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  features; } ;
struct emac_instance {int /*<<< orphan*/  link_lock; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct emac_instance* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int emac_ethtool_get_settings(struct net_device *ndev,
				     struct ethtool_cmd *cmd)
{
	struct emac_instance *dev = netdev_priv(ndev);

	cmd->supported = dev->phy.features;
	cmd->port = PORT_MII;
	cmd->phy_address = dev->phy.address;
	cmd->transceiver =
	    dev->phy.address >= 0 ? XCVR_EXTERNAL : XCVR_INTERNAL;

	mutex_lock(&dev->link_lock);
	cmd->advertising = dev->phy.advertising;
	cmd->autoneg = dev->phy.autoneg;
	cmd->speed = dev->phy.speed;
	cmd->duplex = dev->phy.duplex;
	mutex_unlock(&dev->link_lock);

	return 0;
}