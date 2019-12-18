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

/* Variables and functions */
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_ethtool_ops ; 
 int /*<<< orphan*/  ixgbe_ethtool_ops_ext ; 
 int /*<<< orphan*/  set_ethtool_ops_ext (struct net_device*,int /*<<< orphan*/ *) ; 

void ixgbe_set_ethtool_ops(struct net_device *netdev)
{
	SET_ETHTOOL_OPS(netdev, &ixgbe_ethtool_ops);
	set_ethtool_ops_ext(netdev, &ixgbe_ethtool_ops_ext);
}