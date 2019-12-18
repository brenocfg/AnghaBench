#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct solos_card {int tx_mask; int /*<<< orphan*/  tx_lock; scalar_t__ config_regs; TYPE_2__* dev; scalar_t__ using_dma; int /*<<< orphan*/  tx_queue_lock; int /*<<< orphan*/ * tx_queue; struct sk_buff** tx_skb; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct atm_vcc {TYPE_1__* stats; } ;
struct TYPE_7__ {int dma_addr; struct atm_vcc* vcc; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ FLAGS_ADDR ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 TYPE_4__* SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TX_BUF (struct solos_card*,unsigned char) ; 
 scalar_t__ TX_DMA_ADDR (unsigned char) ; 
 scalar_t__ atmdebug ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_map_single (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_buffer (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solos_pop (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static uint32_t fpga_tx(struct solos_card *card)
{
	uint32_t tx_pending, card_flags;
	uint32_t tx_started = 0;
	struct sk_buff *skb;
	struct atm_vcc *vcc;
	unsigned char port;
	unsigned long flags;

	spin_lock_irqsave(&card->tx_lock, flags);
	
	card_flags = ioread32(card->config_regs + FLAGS_ADDR);
	/*
	 * The queue lock is required for _writing_ to tx_mask, but we're
	 * OK to read it here without locking. The only potential update
	 * that we could race with is in fpga_queue() where it sets a bit
	 * for a new port... but it's going to call this function again if
	 * it's doing that, anyway.
	 */
	tx_pending = card->tx_mask & ~card_flags;

	for (port = 0; tx_pending; tx_pending >>= 1, port++) {
		if (tx_pending & 1) {
			struct sk_buff *oldskb = card->tx_skb[port];
			if (oldskb)
				pci_unmap_single(card->dev, SKB_CB(oldskb)->dma_addr,
						 oldskb->len, PCI_DMA_TODEVICE);

			spin_lock(&card->tx_queue_lock);
			skb = skb_dequeue(&card->tx_queue[port]);
			if (!skb)
				card->tx_mask &= ~(1 << port);
			spin_unlock(&card->tx_queue_lock);

			if (skb && !card->using_dma) {
				memcpy_toio(TX_BUF(card, port), skb->data, skb->len);
				tx_started |= 1 << port;
				oldskb = skb; /* We're done with this skb already */
			} else if (skb && card->using_dma) {
				SKB_CB(skb)->dma_addr = pci_map_single(card->dev, skb->data,
								       skb->len, PCI_DMA_TODEVICE);
				iowrite32(SKB_CB(skb)->dma_addr,
					  card->config_regs + TX_DMA_ADDR(port));
			}

			if (!oldskb)
				continue;

			/* Clean up and free oldskb now it's gone */
			if (atmdebug) {
				dev_info(&card->dev->dev, "Transmitted: port %d\n",
					 port);
				print_buffer(oldskb);
			}

			vcc = SKB_CB(oldskb)->vcc;

			if (vcc) {
				atomic_inc(&vcc->stats->tx);
				solos_pop(vcc, oldskb);
			} else
				dev_kfree_skb_irq(oldskb);

		}
	}
	/* For non-DMA TX, write the 'TX start' bit for all four ports simultaneously */
	if (tx_started)
		iowrite32(tx_started, card->config_regs + FLAGS_ADDR);

	spin_unlock_irqrestore(&card->tx_lock, flags);
	return card_flags;
}