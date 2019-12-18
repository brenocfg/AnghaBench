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
struct ql_adapter {int /*<<< orphan*/  link_config; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_PAUSE_STD ; 
 int EINVAL ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int ql_mb_set_port_cfg (struct ql_adapter*) ; 

__attribute__((used)) static int ql_set_pauseparam(struct net_device *netdev,
			struct ethtool_pauseparam *pause)
{
	struct ql_adapter *qdev = netdev_priv(netdev);
	int status = 0;

	if ((pause->rx_pause) && (pause->tx_pause))
		qdev->link_config |= CFG_PAUSE_STD;
	else if (!pause->rx_pause && !pause->tx_pause)
		qdev->link_config &= ~CFG_PAUSE_STD;
	else
		return -EINVAL;

	status = ql_mb_set_port_cfg(qdev);
	if (status)
		return status;
	return status;
}