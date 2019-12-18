#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; int /*<<< orphan*/  data; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ truesize; int /*<<< orphan*/  head; int /*<<< orphan*/  data; struct sk_buff* skb; } ;
typedef  TYPE_1__ iobuff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IRDA ; 
 scalar_t__ IRDA_RX_COPY_THRESHOLD ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static inline void
async_bump(struct net_device *dev,
	   struct net_device_stats *stats,
	   iobuff_t *rx_buff)
{
	struct sk_buff *newskb;
	struct sk_buff *dataskb;
	int		docopy;

	/* Check if we need to copy the data to a new skb or not.
	 * If the driver doesn't use ZeroCopy Rx, we have to do it.
	 * With ZeroCopy Rx, the rx_buff already point to a valid
	 * skb. But, if the frame is small, it is more efficient to
	 * copy it to save memory (copy will be fast anyway - that's
	 * called Rx-copy-break). Jean II */
	docopy = ((rx_buff->skb == NULL) ||
		  (rx_buff->len < IRDA_RX_COPY_THRESHOLD));

	/* Allocate a new skb */
	newskb = dev_alloc_skb(docopy ? rx_buff->len + 1 : rx_buff->truesize);
	if (!newskb)  {
		stats->rx_dropped++;
		/* We could deliver the current skb if doing ZeroCopy Rx,
		 * but this would stall the Rx path. Better drop the
		 * packet... Jean II */
		return;
	}

	/* Align IP header to 20 bytes (i.e. increase skb->data)
	 * Note this is only useful with IrLAN, as PPP has a variable
	 * header size (2 or 1 bytes) - Jean II */
	skb_reserve(newskb, 1);

	if(docopy) {
		/* Copy data without CRC (length already checked) */
		skb_copy_to_linear_data(newskb, rx_buff->data,
					rx_buff->len - 2);
		/* Deliver this skb */
		dataskb = newskb;
	} else {
		/* We are using ZeroCopy. Deliver old skb */
		dataskb = rx_buff->skb;
		/* And hook the new skb to the rx_buff */
		rx_buff->skb = newskb;
		rx_buff->head = newskb->data;	/* NOT newskb->head */
		//printk(KERN_DEBUG "ZeroCopy : len = %d, dataskb = %p, newskb = %p\n", rx_buff->len, dataskb, newskb);
	}

	/* Set proper length on skb (without CRC) */
	skb_put(dataskb, rx_buff->len - 2);

	/* Feed it to IrLAP layer */
	dataskb->dev = dev;
	skb_reset_mac_header(dataskb);
	dataskb->protocol = htons(ETH_P_IRDA);

	netif_rx(dataskb);

	stats->rx_packets++;
	stats->rx_bytes += rx_buff->len;

	/* Clean up rx_buff (redundant with async_unwrap_bof() ???) */
	rx_buff->data = rx_buff->head;
	rx_buff->len = 0;
}