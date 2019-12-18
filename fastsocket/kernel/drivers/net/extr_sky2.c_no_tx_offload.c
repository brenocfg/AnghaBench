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
struct sky2_port {struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ chip_id; } ;
struct net_device {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_YUKON_EC_U ; 
 scalar_t__ ETH_DATA_LEN ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int no_tx_offload(struct net_device *dev)
{
	const struct sky2_port *sky2 = netdev_priv(dev);
	const struct sky2_hw *hw = sky2->hw;

	return dev->mtu > ETH_DATA_LEN && hw->chip_id == CHIP_ID_YUKON_EC_U;
}