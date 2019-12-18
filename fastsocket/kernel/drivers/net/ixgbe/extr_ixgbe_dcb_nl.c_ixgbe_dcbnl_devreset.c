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
struct net_device {TYPE_1__* netdev_ops; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_clear_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_init_interrupt_scheme (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ixgbe_dcbnl_devreset(struct net_device *dev)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	while (test_and_set_bit(__IXGBE_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	if (netif_running(dev))
		dev->netdev_ops->ndo_stop(dev);

	ixgbe_clear_interrupt_scheme(adapter);
	ixgbe_init_interrupt_scheme(adapter);

	if (netif_running(dev))
		dev->netdev_ops->ndo_open(dev);

	clear_bit(__IXGBE_RESETTING, &adapter->state);
}