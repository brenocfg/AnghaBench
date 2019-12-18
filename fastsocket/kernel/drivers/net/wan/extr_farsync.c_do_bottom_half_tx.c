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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_1__ stats; } ;
struct fst_port_info {size_t txpos; int txqe; size_t txqs; scalar_t__ start; struct sk_buff** txq; int /*<<< orphan*/  run; } ;
struct fst_card_info {int nports; scalar_t__ family; scalar_t__ dma_len_tx; size_t dma_txpos; scalar_t__ tx_dma_handle_card; struct fst_port_info* dma_port_tx; int /*<<< orphan*/  tx_dma_handle_host; scalar_t__ mem; int /*<<< orphan*/  card_lock; int /*<<< orphan*/  dmatx_in_progress; struct fst_port_info* ports; } ;
struct TYPE_4__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  bcnt; } ;

/* Variables and functions */
 scalar_t__ BUF_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_TX ; 
 int DMA_OWN ; 
 scalar_t__ FST_FAMILY_TXP ; 
 scalar_t__ FST_MIN_DMA_LEN ; 
 int FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int FST_TXQ_DEPTH ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FST_WRW (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t NUM_TX_BUFFER ; 
 int TX_ENP ; 
 int TX_STP ; 
 int /*<<< orphan*/  cnv_bcnt (scalar_t__) ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  fst_tx_dma (struct fst_card_info*,char*,char*,scalar_t__) ; 
 int fst_txq_low ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 struct net_device* port_to_dev (struct fst_port_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ *** txBuffer ; 
 TYPE_2__** txDescrRing ; 

__attribute__((used)) static void
do_bottom_half_tx(struct fst_card_info *card)
{
	struct fst_port_info *port;
	int pi;
	int txq_length;
	struct sk_buff *skb;
	unsigned long flags;
	struct net_device *dev;

	/*
	 *  Find a free buffer for the transmit
	 *  Step through each port on this card
	 */

	dbg(DBG_TX, "do_bottom_half_tx\n");
	for (pi = 0, port = card->ports; pi < card->nports; pi++, port++) {
		if (!port->run)
			continue;

		dev = port_to_dev(port);
		while (!(FST_RDB(card, txDescrRing[pi][port->txpos].bits) &
			 DMA_OWN)
		       && !(card->dmatx_in_progress)) {
			/*
			 * There doesn't seem to be a txdone event per-se
			 * We seem to have to deduce it, by checking the DMA_OWN
			 * bit on the next buffer we think we can use
			 */
			spin_lock_irqsave(&card->card_lock, flags);
			if ((txq_length = port->txqe - port->txqs) < 0) {
				/*
				 * This is the case where one has wrapped and the
				 * maths gives us a negative number
				 */
				txq_length = txq_length + FST_TXQ_DEPTH;
			}
			spin_unlock_irqrestore(&card->card_lock, flags);
			if (txq_length > 0) {
				/*
				 * There is something to send
				 */
				spin_lock_irqsave(&card->card_lock, flags);
				skb = port->txq[port->txqs];
				port->txqs++;
				if (port->txqs == FST_TXQ_DEPTH) {
					port->txqs = 0;
				}
				spin_unlock_irqrestore(&card->card_lock, flags);
				/*
				 * copy the data and set the required indicators on the
				 * card.
				 */
				FST_WRW(card, txDescrRing[pi][port->txpos].bcnt,
					cnv_bcnt(skb->len));
				if ((skb->len < FST_MIN_DMA_LEN)
				    || (card->family == FST_FAMILY_TXP)) {
					/* Enqueue the packet with normal io */
					memcpy_toio(card->mem +
						    BUF_OFFSET(txBuffer[pi]
							       [port->
								txpos][0]),
						    skb->data, skb->len);
					FST_WRB(card,
						txDescrRing[pi][port->txpos].
						bits,
						DMA_OWN | TX_STP | TX_ENP);
					dev->stats.tx_packets++;
					dev->stats.tx_bytes += skb->len;
					dev->trans_start = jiffies;
				} else {
					/* Or do it through dma */
					memcpy(card->tx_dma_handle_host,
					       skb->data, skb->len);
					card->dma_port_tx = port;
					card->dma_len_tx = skb->len;
					card->dma_txpos = port->txpos;
					fst_tx_dma(card,
						   (char *) card->
						   tx_dma_handle_card,
						   (char *)
						   BUF_OFFSET(txBuffer[pi]
							      [port->txpos][0]),
						   skb->len);
				}
				if (++port->txpos >= NUM_TX_BUFFER)
					port->txpos = 0;
				/*
				 * If we have flow control on, can we now release it?
				 */
				if (port->start) {
					if (txq_length < fst_txq_low) {
						netif_wake_queue(port_to_dev
								 (port));
						port->start = 0;
					}
				}
				dev_kfree_skb(skb);
			} else {
				/*
				 * Nothing to send so break out of the while loop
				 */
				break;
			}
		}
	}
}