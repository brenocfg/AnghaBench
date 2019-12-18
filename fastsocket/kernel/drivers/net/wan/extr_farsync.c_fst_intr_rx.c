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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {unsigned short rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct fst_port_info {int index; int rxpos; scalar_t__ mode; } ;
struct fst_card_info {scalar_t__ family; unsigned short dma_len_rx; int dma_rxpos; scalar_t__ rx_dma_handle_card; struct fst_port_info* dma_port_rx; struct sk_buff* dma_skb_rx; scalar_t__ mem; int /*<<< orphan*/  card_no; scalar_t__ dmarx_in_progress; } ;
struct TYPE_4__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  mcnt; } ;

/* Variables and functions */
 scalar_t__ BUF_OFFSET (int /*<<< orphan*/ ) ; 
 int DBG_ASS ; 
 int DBG_INTR ; 
 int DBG_RX ; 
 unsigned char DMA_OWN ; 
 scalar_t__ FST_FAMILY_TXP ; 
 unsigned short FST_MIN_DMA_LEN ; 
 scalar_t__ FST_RAW ; 
 unsigned char FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 unsigned short FST_RDW (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,unsigned char) ; 
 int LEN_RX_BUFFER ; 
 int NET_RX_DROP ; 
 int NUM_RX_BUFFER ; 
 unsigned char RX_ENP ; 
 unsigned char RX_STP ; 
 int /*<<< orphan*/  dbg (int,char*,...) ; 
 struct sk_buff* dev_alloc_skb (unsigned short) ; 
 int /*<<< orphan*/  farsync_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  fst_log_rx_error (struct fst_card_info*,struct fst_port_info*,unsigned char,int,unsigned short) ; 
 int /*<<< orphan*/  fst_process_rx_status (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_recover_rx_error (struct fst_card_info*,struct fst_port_info*,unsigned char,int,unsigned short) ; 
 int /*<<< orphan*/  fst_rx_dma (struct fst_card_info*,char*,char*,unsigned short) ; 
 int /*<<< orphan*/  hdlc_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,unsigned short) ; 
 int netif_rx (struct sk_buff*) ; 
 struct net_device* port_to_dev (struct fst_port_info*) ; 
 int /*<<< orphan*/  printk_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ *** rxBuffer ; 
 TYPE_2__** rxDescrRing ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned short) ; 

__attribute__((used)) static void
fst_intr_rx(struct fst_card_info *card, struct fst_port_info *port)
{
	unsigned char dmabits;
	int pi;
	int rxp;
	int rx_status;
	unsigned short len;
	struct sk_buff *skb;
	struct net_device *dev = port_to_dev(port);

	/* Check we have a buffer to process */
	pi = port->index;
	rxp = port->rxpos;
	dmabits = FST_RDB(card, rxDescrRing[pi][rxp].bits);
	if (dmabits & DMA_OWN) {
		dbg(DBG_RX | DBG_INTR, "intr_rx: No buffer port %d pos %d\n",
		    pi, rxp);
		return;
	}
	if (card->dmarx_in_progress) {
		return;
	}

	/* Get buffer length */
	len = FST_RDW(card, rxDescrRing[pi][rxp].mcnt);
	/* Discard the CRC */
	len -= 2;
	if (len == 0) {
		/*
		 * This seems to happen on the TE1 interface sometimes
		 * so throw the frame away and log the event.
		 */
		printk_err("Frame received with 0 length. Card %d Port %d\n",
			   card->card_no, port->index);
		/* Return descriptor to card */
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

		rxp = (rxp+1) % NUM_RX_BUFFER;
		port->rxpos = rxp;
		return;
	}

	/* Check buffer length and for other errors. We insist on one packet
	 * in one buffer. This simplifies things greatly and since we've
	 * allocated 8K it shouldn't be a real world limitation
	 */
	dbg(DBG_RX, "intr_rx: %d,%d: flags %x len %d\n", pi, rxp, dmabits, len);
	if (dmabits != (RX_STP | RX_ENP) || len > LEN_RX_BUFFER - 2) {
		fst_log_rx_error(card, port, dmabits, rxp, len);
		fst_recover_rx_error(card, port, dmabits, rxp, len);
		return;
	}

	/* Allocate SKB */
	if ((skb = dev_alloc_skb(len)) == NULL) {
		dbg(DBG_RX, "intr_rx: can't allocate buffer\n");

		dev->stats.rx_dropped++;

		/* Return descriptor to card */
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

		rxp = (rxp+1) % NUM_RX_BUFFER;
		port->rxpos = rxp;
		return;
	}

	/*
	 * We know the length we need to receive, len.
	 * It's not worth using the DMA for reads of less than
	 * FST_MIN_DMA_LEN
	 */

	if ((len < FST_MIN_DMA_LEN) || (card->family == FST_FAMILY_TXP)) {
		memcpy_fromio(skb_put(skb, len),
			      card->mem + BUF_OFFSET(rxBuffer[pi][rxp][0]),
			      len);

		/* Reset buffer descriptor */
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

		/* Update stats */
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += len;

		/* Push upstream */
		dbg(DBG_RX, "Pushing frame up the stack\n");
		if (port->mode == FST_RAW)
			skb->protocol = farsync_type_trans(skb, dev);
		else
			skb->protocol = hdlc_type_trans(skb, dev);
		rx_status = netif_rx(skb);
		fst_process_rx_status(rx_status, port_to_dev(port)->name);
		if (rx_status == NET_RX_DROP)
			dev->stats.rx_dropped++;
	} else {
		card->dma_skb_rx = skb;
		card->dma_port_rx = port;
		card->dma_len_rx = len;
		card->dma_rxpos = rxp;
		fst_rx_dma(card, (char *) card->rx_dma_handle_card,
			   (char *) BUF_OFFSET(rxBuffer[pi][rxp][0]), len);
	}
	if (rxp != port->rxpos) {
		dbg(DBG_ASS, "About to increment rxpos by more than 1\n");
		dbg(DBG_ASS, "rxp = %d rxpos = %d\n", rxp, port->rxpos);
	}
	rxp = (rxp+1) % NUM_RX_BUFFER;
	port->rxpos = rxp;
}