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
struct ethtool_rxnfc {int cmd; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXFH 128 
 int bnx2x_set_rss_flags (struct bnx2x*,struct ethtool_rxnfc*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *info)
{
	struct bnx2x *bp = netdev_priv(dev);

	switch (info->cmd) {
	case ETHTOOL_SRXFH:
		return bnx2x_set_rss_flags(bp, info);
	default:
		DP(BNX2X_MSG_ETHTOOL, "Command parameters not supported\n");
		return -EOPNOTSUPP;
	}
}