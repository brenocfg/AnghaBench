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
struct smsc9420_pdata {int /*<<< orphan*/  phy_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int phy_start_aneg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc9420_ethtool_nway_reset(struct net_device *netdev)
{
	struct smsc9420_pdata *pd = netdev_priv(netdev);

	if (!pd->phy_dev)
		return -ENODEV;

	return phy_start_aneg(pd->phy_dev);
}