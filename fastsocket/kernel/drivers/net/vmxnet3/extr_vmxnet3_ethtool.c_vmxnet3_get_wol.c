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
struct vmxnet3_adapter {int /*<<< orphan*/  wol; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int /*<<< orphan*/  wolopts; } ;

/* Variables and functions */
 int WAKE_ARP ; 
 int WAKE_MAGIC ; 
 int WAKE_UCAST ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
vmxnet3_get_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_UCAST | WAKE_ARP | WAKE_MAGIC;
	wol->wolopts = adapter->wol;
}