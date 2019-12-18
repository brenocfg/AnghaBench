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
struct sk_buff {int /*<<< orphan*/  data; struct net_device* dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  head; } ;
struct TYPE_3__ {short rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct corkscrew_private {int cur_rx; scalar_t__ dirty_rx; TYPE_2__* rx_ring; struct sk_buff** rx_skbuff; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ EL3_STATUS ; 
 short PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int RxDComplete ; 
 int RxDError ; 
 scalar_t__ RxStatus ; 
 int corkscrew_debug ; 
 struct sk_buff* dev_alloc_skb (short) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int inw (scalar_t__) ; 
 void* isa_bus_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_virt_to_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,short) ; 
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,short,...) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rx_copy ; 
 short rx_copybreak ; 
 int /*<<< orphan*/  rx_nocopy ; 
 void* skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int boomerang_rx(struct net_device *dev)
{
	struct corkscrew_private *vp = netdev_priv(dev);
	int entry = vp->cur_rx % RX_RING_SIZE;
	int ioaddr = dev->base_addr;
	int rx_status;

	if (corkscrew_debug > 5)
		pr_debug("   In boomerang_rx(), status %4.4x, rx_status %4.4x.\n",
			inw(ioaddr + EL3_STATUS), inw(ioaddr + RxStatus));
	while ((rx_status = vp->rx_ring[entry].status) & RxDComplete) {
		if (rx_status & RxDError) {	/* Error, update stats. */
			unsigned char rx_error = rx_status >> 16;
			if (corkscrew_debug > 2)
				pr_debug(" Rx error: status %2.2x.\n",
				       rx_error);
			dev->stats.rx_errors++;
			if (rx_error & 0x01)
				dev->stats.rx_over_errors++;
			if (rx_error & 0x02)
				dev->stats.rx_length_errors++;
			if (rx_error & 0x04)
				dev->stats.rx_frame_errors++;
			if (rx_error & 0x08)
				dev->stats.rx_crc_errors++;
			if (rx_error & 0x10)
				dev->stats.rx_length_errors++;
		} else {
			/* The packet length: up to 4.5K!. */
			short pkt_len = rx_status & 0x1fff;
			struct sk_buff *skb;

			dev->stats.rx_bytes += pkt_len;
			if (corkscrew_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
				     pkt_len, rx_status);

			/* Check if the packet is long enough to just accept without
			   copying to a properly sized skbuff. */
			if (pkt_len < rx_copybreak
			    && (skb = dev_alloc_skb(pkt_len + 4)) != NULL) {
				skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
				/* 'skb_put()' points to the start of sk_buff data area. */
				memcpy(skb_put(skb, pkt_len),
				       isa_bus_to_virt(vp->rx_ring[entry].
						   addr), pkt_len);
				rx_copy++;
			} else {
				void *temp;
				/* Pass up the skbuff already on the Rx ring. */
				skb = vp->rx_skbuff[entry];
				vp->rx_skbuff[entry] = NULL;
				temp = skb_put(skb, pkt_len);
				/* Remove this checking code for final release. */
				if (isa_bus_to_virt(vp->rx_ring[entry].addr) != temp)
					pr_warning("%s: Warning -- the skbuff addresses do not match"
					     " in boomerang_rx: %p vs. %p / %p.\n",
					     dev->name,
					     isa_bus_to_virt(vp->
							 rx_ring[entry].
							 addr), skb->head,
					     temp);
				rx_nocopy++;
			}
			skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
			dev->stats.rx_packets++;
		}
		entry = (++vp->cur_rx) % RX_RING_SIZE;
	}
	/* Refill the Rx ring buffers. */
	for (; vp->cur_rx - vp->dirty_rx > 0; vp->dirty_rx++) {
		struct sk_buff *skb;
		entry = vp->dirty_rx % RX_RING_SIZE;
		if (vp->rx_skbuff[entry] == NULL) {
			skb = dev_alloc_skb(PKT_BUF_SZ);
			if (skb == NULL)
				break;	/* Bad news!  */
			skb->dev = dev;	/* Mark as being used by this device. */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			vp->rx_ring[entry].addr = isa_virt_to_bus(skb->data);
			vp->rx_skbuff[entry] = skb;
		}
		vp->rx_ring[entry].status = 0;	/* Clear complete bit. */
	}
	return 0;
}