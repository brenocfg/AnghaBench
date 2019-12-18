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
typedef  size_t u32 ;
struct tg3_tx_ring_info {int fragmented; struct sk_buff* skb; } ;
struct tg3_napi {struct tg3_tx_ring_info* tx_buffers; TYPE_1__* tp; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 size_t NEXT_TX (size_t) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dma_unmap_addr (struct tg3_tx_ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void tg3_tx_skb_unmap(struct tg3_napi *tnapi, u32 entry, int last)
{
	int i;
	struct sk_buff *skb;
	struct tg3_tx_ring_info *txb = &tnapi->tx_buffers[entry];

	skb = txb->skb;
	txb->skb = NULL;

	pci_unmap_single(tnapi->tp->pdev,
			 dma_unmap_addr(txb, mapping),
			 skb_headlen(skb),
			 PCI_DMA_TODEVICE);

	while (txb->fragmented) {
		txb->fragmented = false;
		entry = NEXT_TX(entry);
		txb = &tnapi->tx_buffers[entry];
	}

	for (i = 0; i <= last; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		entry = NEXT_TX(entry);
		txb = &tnapi->tx_buffers[entry];

		pci_unmap_page(tnapi->tp->pdev,
			       dma_unmap_addr(txb, mapping),
			       skb_frag_size(frag), PCI_DMA_TODEVICE);

		while (txb->fragmented) {
			txb->fragmented = false;
			entry = NEXT_TX(entry);
			txb = &tnapi->tx_buffers[entry];
		}
	}
}