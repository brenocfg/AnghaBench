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
struct skge_port {scalar_t__ flow_control; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int autoneg; } ;

/* Variables and functions */
 scalar_t__ FLOW_MODE_LOC_SEND ; 
 scalar_t__ FLOW_MODE_SYMMETRIC ; 
 scalar_t__ FLOW_MODE_SYM_OR_REM ; 
 struct skge_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void skge_get_pauseparam(struct net_device *dev,
				struct ethtool_pauseparam *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);

	ecmd->rx_pause = (skge->flow_control == FLOW_MODE_SYMMETRIC)
		|| (skge->flow_control == FLOW_MODE_SYM_OR_REM);
	ecmd->tx_pause = ecmd->rx_pause || (skge->flow_control == FLOW_MODE_LOC_SEND);

	ecmd->autoneg = ecmd->rx_pause || ecmd->tx_pause;
}