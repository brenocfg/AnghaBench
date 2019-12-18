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
struct smsc9420_pdata {scalar_t__ tx_ring_tail; scalar_t__ tx_ring_head; TYPE_2__* tx_buffers; TYPE_1__* tx_ring; int /*<<< orphan*/  pdev; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  mapping; struct sk_buff* skb; } ;
struct TYPE_3__ {scalar_t__ buffer2; scalar_t__ buffer1; scalar_t__ length; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void smsc9420_free_tx_ring(struct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->tx_ring);

	if (!pd->tx_buffers)
		return;

	for (i = 0; i < TX_RING_SIZE; i++) {
		struct sk_buff *skb = pd->tx_buffers[i].skb;

		if (skb) {
			BUG_ON(!pd->tx_buffers[i].mapping);
			pci_unmap_single(pd->pdev, pd->tx_buffers[i].mapping,
					 skb->len, PCI_DMA_TODEVICE);
			dev_kfree_skb_any(skb);
		}

		pd->tx_ring[i].status = 0;
		pd->tx_ring[i].length = 0;
		pd->tx_ring[i].buffer1 = 0;
		pd->tx_ring[i].buffer2 = 0;
	}
	wmb();

	kfree(pd->tx_buffers);
	pd->tx_buffers = NULL;

	pd->tx_ring_head = 0;
	pd->tx_ring_tail = 0;
}