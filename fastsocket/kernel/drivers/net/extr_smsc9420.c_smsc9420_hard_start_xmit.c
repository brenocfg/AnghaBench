#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct smsc9420_pdata {int tx_ring_head; int tx_ring_tail; TYPE_2__* tx_ring; int /*<<< orphan*/  dev; TYPE_1__* tx_buffers; int /*<<< orphan*/  pdev; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  void* dma_addr_t ;
struct TYPE_4__ {int status; int length; void* buffer1; } ;
struct TYPE_3__ {int skb; int mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TDES0_OWN_ ; 
 int TDES1_IC_ ; 
 int TDES1_LS_ ; 
 int TDES1_TER_ ; 
 int /*<<< orphan*/  TX_ERR ; 
 int /*<<< orphan*/  TX_POLL_DEMAND ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  jiffies ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 void* pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smsc9420_complete_tx (struct net_device*) ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t smsc9420_hard_start_xmit(struct sk_buff *skb,
					    struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	dma_addr_t mapping;
	int index = pd->tx_ring_head;
	u32 tmp_desc1;
	bool about_to_take_last_desc =
		(((pd->tx_ring_head + 2) % TX_RING_SIZE) == pd->tx_ring_tail);

	smsc9420_complete_tx(dev);

	rmb();
	BUG_ON(pd->tx_ring[index].status & TDES0_OWN_);
	BUG_ON(pd->tx_buffers[index].skb);
	BUG_ON(pd->tx_buffers[index].mapping);

	mapping = pci_map_single(pd->pdev, skb->data,
				 skb->len, PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(pd->pdev, mapping)) {
		smsc_warn(TX_ERR, "pci_map_single failed, dropping packet");
		return NETDEV_TX_BUSY;
	}

	pd->tx_buffers[index].skb = skb;
	pd->tx_buffers[index].mapping = mapping;

	tmp_desc1 = (TDES1_LS_ | ((u32)skb->len & 0x7FF));
	if (unlikely(about_to_take_last_desc)) {
		tmp_desc1 |= TDES1_IC_;
		netif_stop_queue(pd->dev);
	}

	/* check if we are at the last descriptor and need to set EOR */
	if (unlikely(index == (TX_RING_SIZE - 1)))
		tmp_desc1 |= TDES1_TER_;

	pd->tx_ring[index].buffer1 = mapping;
	pd->tx_ring[index].length = tmp_desc1;
	wmb();

	/* increment head */
	pd->tx_ring_head = (pd->tx_ring_head + 1) % TX_RING_SIZE;

	/* assign ownership to DMAC */
	pd->tx_ring[index].status = TDES0_OWN_;
	wmb();

	/* kick the DMA */
	smsc9420_reg_write(pd, TX_POLL_DEMAND, 1);
	smsc9420_pci_flush_write(pd);

	dev->trans_start = jiffies;

	return NETDEV_TX_OK;
}