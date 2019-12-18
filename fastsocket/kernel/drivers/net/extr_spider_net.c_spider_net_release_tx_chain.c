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
typedef  int /*<<< orphan*/  u32 ;
struct spider_net_hw_descr {int /*<<< orphan*/  buf_addr; int /*<<< orphan*/  dmac_cmd_status; } ;
struct spider_net_descr_chain {int /*<<< orphan*/  lock; struct spider_net_descr* tail; struct spider_net_descr* head; } ;
struct spider_net_descr {struct sk_buff* skb; struct spider_net_descr* next; struct spider_net_hw_descr* hwdescr; } ;
struct spider_net_card {int /*<<< orphan*/  pdev; struct net_device* netdev; struct spider_net_descr_chain tx_chain; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
#define  SPIDER_NET_DESCR_CARDOWNED 132 
#define  SPIDER_NET_DESCR_COMPLETE 131 
#define  SPIDER_NET_DESCR_FORCE_END 130 
 int /*<<< orphan*/  SPIDER_NET_DESCR_NOT_IN_USE ; 
#define  SPIDER_NET_DESCR_PROTECTION_ERROR 129 
#define  SPIDER_NET_DESCR_RESPONSE_ERROR 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_msg_tx_err (struct spider_net_card*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spider_net_get_descr_status (struct spider_net_hw_descr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
spider_net_release_tx_chain(struct spider_net_card *card, int brutal)
{
	struct net_device *dev = card->netdev;
	struct spider_net_descr_chain *chain = &card->tx_chain;
	struct spider_net_descr *descr;
	struct spider_net_hw_descr *hwdescr;
	struct sk_buff *skb;
	u32 buf_addr;
	unsigned long flags;
	int status;

	while (1) {
		spin_lock_irqsave(&chain->lock, flags);
		if (chain->tail == chain->head) {
			spin_unlock_irqrestore(&chain->lock, flags);
			return 0;
		}
		descr = chain->tail;
		hwdescr = descr->hwdescr;

		status = spider_net_get_descr_status(hwdescr);
		switch (status) {
		case SPIDER_NET_DESCR_COMPLETE:
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += descr->skb->len;
			break;

		case SPIDER_NET_DESCR_CARDOWNED:
			if (!brutal) {
				spin_unlock_irqrestore(&chain->lock, flags);
				return 1;
			}

			/* fallthrough, if we release the descriptors
			 * brutally (then we don't care about
			 * SPIDER_NET_DESCR_CARDOWNED) */

		case SPIDER_NET_DESCR_RESPONSE_ERROR:
		case SPIDER_NET_DESCR_PROTECTION_ERROR:
		case SPIDER_NET_DESCR_FORCE_END:
			if (netif_msg_tx_err(card))
				dev_err(&card->netdev->dev, "forcing end of tx descriptor "
				       "with status x%02x\n", status);
			dev->stats.tx_errors++;
			break;

		default:
			dev->stats.tx_dropped++;
			if (!brutal) {
				spin_unlock_irqrestore(&chain->lock, flags);
				return 1;
			}
		}

		chain->tail = descr->next;
		hwdescr->dmac_cmd_status |= SPIDER_NET_DESCR_NOT_IN_USE;
		skb = descr->skb;
		descr->skb = NULL;
		buf_addr = hwdescr->buf_addr;
		spin_unlock_irqrestore(&chain->lock, flags);

		/* unmap the skb */
		if (skb) {
			pci_unmap_single(card->pdev, buf_addr, skb->len,
					PCI_DMA_TODEVICE);
			dev_kfree_skb(skb);
		}
	}
	return 0;
}