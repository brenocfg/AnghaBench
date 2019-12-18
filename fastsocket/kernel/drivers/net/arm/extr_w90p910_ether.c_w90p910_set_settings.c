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
struct w90p910_ether {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int w90p910_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	return mii_ethtool_sset(&ether->mii, cmd);
}