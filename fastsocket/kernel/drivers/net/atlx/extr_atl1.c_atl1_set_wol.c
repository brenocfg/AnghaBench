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
struct ethtool_wolinfo {int wolopts; } ;
struct atl1_adapter {int /*<<< orphan*/  wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATLX_WUFC_MAG ; 
 int EOPNOTSUPP ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atl1_set_wol(struct net_device *netdev,
	struct ethtool_wolinfo *wol)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);

	if (wol->wolopts & (WAKE_PHY | WAKE_UCAST | WAKE_MCAST | WAKE_BCAST |
		WAKE_ARP | WAKE_MAGICSECURE))
		return -EOPNOTSUPP;
	adapter->wol = 0;
	if (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= ATLX_WUFC_MAG;
	return 0;
}