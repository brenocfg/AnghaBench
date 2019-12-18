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
struct net_device {int mtu; int /*<<< orphan*/  dev_addr; } ;
struct et131x_adapter {int RegistryJumboPacket; int Flags; int /*<<< orphan*/  CurrentAddress; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int et131x_adapter_memory_alloc (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_adapter_memory_free (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_adapter_setup (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_disable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_enable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_handle_recv_interrupt (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_handle_send_interrupt (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_init_send (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_rx_dma_disable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_rx_dma_enable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_setup_hardware_properties (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_soft_reset (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_disable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_enable (struct et131x_adapter*) ; 
 int fMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

int et131x_change_mtu(struct net_device *netdev, int new_mtu)
{
	int result = 0;
	struct et131x_adapter *adapter = netdev_priv(netdev);

	/* Make sure the requested MTU is valid */
	if (new_mtu < 64 || new_mtu > 9216)
		return -EINVAL;

	/* Stop the netif queue */
	netif_stop_queue(netdev);

	/* Stop the Tx and Rx DMA engines */
	et131x_rx_dma_disable(adapter);
	et131x_tx_dma_disable(adapter);

	/* Disable device interrupts */
	et131x_disable_interrupts(adapter);
	et131x_handle_send_interrupt(adapter);
	et131x_handle_recv_interrupt(adapter);

	/* Set the new MTU */
	netdev->mtu = new_mtu;

	/* Free Rx DMA memory */
	et131x_adapter_memory_free(adapter);

	/* Set the config parameter for Jumbo Packet support */
	adapter->RegistryJumboPacket = new_mtu + 14;
	et131x_soft_reset(adapter);

	/* Alloc and init Rx DMA memory */
	result = et131x_adapter_memory_alloc(adapter);
	if (result != 0) {
		dev_warn(&adapter->pdev->dev,
			"Change MTU failed; couldn't re-alloc DMA memory\n");
		return result;
	}

	et131x_init_send(adapter);

	et131x_setup_hardware_properties(adapter);
	memcpy(netdev->dev_addr, adapter->CurrentAddress, ETH_ALEN);

	/* Init the device with the new settings */
	et131x_adapter_setup(adapter);

	/* Enable interrupts */
	if (adapter->Flags & fMP_ADAPTER_INTERRUPT_IN_USE)
		et131x_enable_interrupts(adapter);

	/* Restart the Tx and Rx DMA engines */
	et131x_rx_dma_enable(adapter);
	et131x_tx_dma_enable(adapter);

	/* Restart the netif queue */
	netif_wake_queue(netdev);
	return result;
}