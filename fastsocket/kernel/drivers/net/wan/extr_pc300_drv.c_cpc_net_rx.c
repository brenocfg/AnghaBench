#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  protocol; int /*<<< orphan*/ * data; struct net_device* dev; } ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {int mtu; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ trace_on; scalar_t__ chan; } ;
typedef  TYPE_2__ pc300dev_t ;
struct TYPE_7__ {int channel; scalar_t__ card; } ;
typedef  TYPE_3__ pc300ch_t ;
typedef  int /*<<< orphan*/  pc300_t ;
struct TYPE_8__ {scalar_t__ priv; } ;

/* Variables and functions */
 int DST_ABT ; 
 int DST_CRC ; 
 int DST_OVR ; 
 int DST_RBIT ; 
 int DST_SHRT ; 
 int /*<<< orphan*/  cpc_trace (struct net_device*,struct sk_buff*,char) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 TYPE_4__* dev_to_hdlc (struct net_device*) ; 
 int dma_buf_read (int /*<<< orphan*/ *,int,struct sk_buff*) ; 
 int dma_get_rx_frame_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdlc_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void cpc_net_rx(struct net_device *dev)
{
	pc300dev_t *d = (pc300dev_t *) dev_to_hdlc(dev)->priv;
	pc300ch_t *chan = (pc300ch_t *) d->chan;
	pc300_t *card = (pc300_t *) chan->card;
	int ch = chan->channel;
#ifdef PC300_DEBUG_RX
	int i;
#endif
	int rxb;
	struct sk_buff *skb;

	while (1) {
		if ((rxb = dma_get_rx_frame_size(card, ch)) == -1)
			return;

		if (!netif_carrier_ok(dev)) {
			/* DCD must be OFF: drop packet */
		    printk("%s : DCD is OFF - drop %d rx bytes\n", dev->name, rxb); 
			skb = NULL;
		} else {
			if (rxb > (dev->mtu + 40)) { /* add headers */
				printk("%s : MTU exceeded %d\n", dev->name, rxb); 
				skb = NULL;
			} else {
				skb = dev_alloc_skb(rxb);
				if (skb == NULL) {
					printk("%s: Memory squeeze!!\n", dev->name);
					return;
				}
				skb->dev = dev;
			}
		}

		if (((rxb = dma_buf_read(card, ch, skb)) <= 0) || (skb == NULL)) {
#ifdef PC300_DEBUG_RX
			printk("%s: rxb = %x\n", dev->name, rxb);
#endif
			if ((skb == NULL) && (rxb > 0)) {
				/* rxb > dev->mtu */
				dev->stats.rx_errors++;
				dev->stats.rx_length_errors++;
				continue;
			}

			if (rxb < 0) {	/* Invalid frame */
				rxb = -rxb;
				if (rxb & DST_OVR) {
					dev->stats.rx_errors++;
					dev->stats.rx_fifo_errors++;
				}
				if (rxb & DST_CRC) {
					dev->stats.rx_errors++;
					dev->stats.rx_crc_errors++;
				}
				if (rxb & (DST_RBIT | DST_SHRT | DST_ABT)) {
					dev->stats.rx_errors++;
					dev->stats.rx_frame_errors++;
				}
			}
			if (skb) {
				dev_kfree_skb_irq(skb);
			}
			continue;
		}

		dev->stats.rx_bytes += rxb;

#ifdef PC300_DEBUG_RX
		printk("%s R:", dev->name);
		for (i = 0; i < skb->len; i++)
			printk(" %02x", *(skb->data + i));
		printk("\n");
#endif
		if (d->trace_on) {
			cpc_trace(dev, skb, 'R');
		}
		dev->stats.rx_packets++;
		skb->protocol = hdlc_type_trans(skb, dev);
		netif_rx(skb);
	}
}