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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct e1000_adapter {int flags; } ;

/* Variables and functions */
 int FLAG_RX_CSUM_ENABLED ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 e1000_get_rx_csum(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	return adapter->flags & FLAG_RX_CSUM_ENABLED;
}