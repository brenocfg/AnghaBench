#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;
struct net_device {int features; } ;

/* Variables and functions */
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 netxen_nic_get_tso(struct net_device *dev)
{
	struct netxen_adapter *adapter = netdev_priv(dev);

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		return (dev->features & (NETIF_F_TSO | NETIF_F_TSO6)) != 0;

	return (dev->features & NETIF_F_TSO) != 0;
}