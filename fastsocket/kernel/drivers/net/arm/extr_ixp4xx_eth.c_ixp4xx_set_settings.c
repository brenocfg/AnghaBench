#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct port {int /*<<< orphan*/  phydev; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 struct port* netdev_priv (struct net_device*) ; 
 int phy_ethtool_sset (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 

__attribute__((used)) static int ixp4xx_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct port *port = netdev_priv(dev);
	return phy_ethtool_sset(port->phydev, cmd);
}