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
struct ethtool_cmd {int supported; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  transceiver; } ;
struct enc28j60_net {scalar_t__ full_duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
enc28j60_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct enc28j60_net *priv = netdev_priv(dev);

	cmd->transceiver = XCVR_INTERNAL;
	cmd->supported	= SUPPORTED_10baseT_Half
			| SUPPORTED_10baseT_Full
			| SUPPORTED_TP;
	cmd->speed	= SPEED_10;
	cmd->duplex	= priv->full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	cmd->port	= PORT_TP;
	cmd->autoneg	= AUTONEG_DISABLE;

	return 0;
}