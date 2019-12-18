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
typedef  int /*<<< orphan*/  u32 ;
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NUM_RX_REGS ; 
 int NUM_TX_REGS ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
vmxnet3_get_regs_len(struct net_device *netdev)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	return (adapter->num_tx_queues * NUM_TX_REGS * sizeof(u32) +
		adapter->num_rx_queues * NUM_RX_REGS * sizeof(u32));
}