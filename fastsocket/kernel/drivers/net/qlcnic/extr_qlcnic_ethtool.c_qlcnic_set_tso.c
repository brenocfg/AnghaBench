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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct net_device {int features; } ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int QLCNIC_FW_CAPABILITY_TSO ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qlcnic_set_tso(struct net_device *dev, u32 data)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	if (!(adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_TSO))
		return -EOPNOTSUPP;
	if (data)
		dev->features |= (NETIF_F_TSO | NETIF_F_TSO6);
	else
		dev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6);

	return 0;
}