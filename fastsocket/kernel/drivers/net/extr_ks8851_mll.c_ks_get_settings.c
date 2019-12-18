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
struct net_device {int dummy; } ;
struct ks_net {int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_get_settings(struct net_device *netdev, struct ethtool_cmd *cmd)
{
	struct ks_net *ks = netdev_priv(netdev);
	return mii_ethtool_gset(&ks->mii, cmd);
}