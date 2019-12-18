#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rx {TYPE_2__* prev; scalar_t__ dma_addr; TYPE_3__* skb; } ;
struct rfd {int /*<<< orphan*/  link; } ;
struct nic {int /*<<< orphan*/  pdev; int /*<<< orphan*/  blank_rfd; int /*<<< orphan*/  netdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_addr; TYPE_1__* skb; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  RFD_BUF_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_3__*) ; 
 TYPE_3__* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int e100_rx_alloc_skb(struct nic *nic, struct rx *rx)
{
	if (!(rx->skb = netdev_alloc_skb_ip_align(nic->netdev, RFD_BUF_LEN)))
		return -ENOMEM;

	/* Init, and map the RFD. */
	skb_copy_to_linear_data(rx->skb, &nic->blank_rfd, sizeof(struct rfd));
	rx->dma_addr = pci_map_single(nic->pdev, rx->skb->data,
		RFD_BUF_LEN, PCI_DMA_BIDIRECTIONAL);

	if (pci_dma_mapping_error(nic->pdev, rx->dma_addr)) {
		dev_kfree_skb_any(rx->skb);
		rx->skb = NULL;
		rx->dma_addr = 0;
		return -ENOMEM;
	}

	/* Link the RFD to end of RFA by linking previous RFD to
	 * this one.  We are safe to touch the previous RFD because
	 * it is protected by the before last buffer's el bit being set */
	if (rx->prev->skb) {
		struct rfd *prev_rfd = (struct rfd *)rx->prev->skb->data;
		put_unaligned_le32(rx->dma_addr, &prev_rfd->link);
		pci_dma_sync_single_for_device(nic->pdev, rx->prev->dma_addr,
			sizeof(struct rfd), PCI_DMA_BIDIRECTIONAL);
	}

	return 0;
}