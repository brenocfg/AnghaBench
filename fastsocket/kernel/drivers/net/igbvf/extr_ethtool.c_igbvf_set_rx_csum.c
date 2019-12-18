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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct igbvf_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGBVF_FLAG_RX_CSUM_DISABLED ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igbvf_set_rx_csum(struct net_device *netdev, u32 data)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);

	if (data)
		adapter->flags &= ~IGBVF_FLAG_RX_CSUM_DISABLED;
	else
		adapter->flags |= IGBVF_FLAG_RX_CSUM_DISABLED;

	return 0;
}