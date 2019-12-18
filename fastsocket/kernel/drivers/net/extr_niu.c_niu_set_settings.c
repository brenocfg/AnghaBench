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
struct niu_link_config {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; } ;
struct niu {struct niu_link_config link_config; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 struct niu* netdev_priv (struct net_device*) ; 
 int niu_init_link (struct niu*) ; 

__attribute__((used)) static int niu_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct niu *np = netdev_priv(dev);
	struct niu_link_config *lp = &np->link_config;

	lp->advertising = cmd->advertising;
	lp->speed = cmd->speed;
	lp->duplex = cmd->duplex;
	lp->autoneg = cmd->autoneg;
	return niu_init_link(np);
}