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
typedef  int u32 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct ioc3_private {int rx_ci; int rx_pi; int flags; struct sk_buff** rx_skbs; TYPE_1__ stats; scalar_t__ rxr; struct ioc3* regs; } ;
struct ioc3_erxbuf {scalar_t__ w0; scalar_t__ err; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int ERPIR_ARM ; 
 int ERXBUF_BYTECNT_SHIFT ; 
 int ERXBUF_CRCERR ; 
 int ERXBUF_FRAMERR ; 
 int ERXBUF_GOODPKT ; 
 int ERXBUF_IPCKSUM_MASK ; 
 int ERXBUF_V ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IOC3_FLAG_RX_CHECKSUMS ; 
 int /*<<< orphan*/  RX_BUF_ALLOC_SIZE ; 
 scalar_t__ RX_OFFSET ; 
 int be32_to_cpu (scalar_t__) ; 
 unsigned long cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ioc3_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_map (struct ioc3_erxbuf*,int) ; 
 int /*<<< orphan*/  ioc3_tcpudp_checksum (struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  ioc3_w_erpir (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  priv_netdev (struct ioc3_private*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static inline void ioc3_rx(struct ioc3_private *ip)
{
	struct sk_buff *skb, *new_skb;
	struct ioc3 *ioc3 = ip->regs;
	int rx_entry, n_entry, len;
	struct ioc3_erxbuf *rxb;
	unsigned long *rxr;
	u32 w0, err;

	rxr = (unsigned long *) ip->rxr;		/* Ring base */
	rx_entry = ip->rx_ci;				/* RX consume index */
	n_entry = ip->rx_pi;

	skb = ip->rx_skbs[rx_entry];
	rxb = (struct ioc3_erxbuf *) (skb->data - RX_OFFSET);
	w0 = be32_to_cpu(rxb->w0);

	while (w0 & ERXBUF_V) {
		err = be32_to_cpu(rxb->err);		/* It's valid ...  */
		if (err & ERXBUF_GOODPKT) {
			len = ((w0 >> ERXBUF_BYTECNT_SHIFT) & 0x7ff) - 4;
			skb_trim(skb, len);
			skb->protocol = eth_type_trans(skb, priv_netdev(ip));

			new_skb = ioc3_alloc_skb(RX_BUF_ALLOC_SIZE, GFP_ATOMIC);
			if (!new_skb) {
				/* Ouch, drop packet and just recycle packet
				   to keep the ring filled.  */
				ip->stats.rx_dropped++;
				new_skb = skb;
				goto next;
			}

			if (likely(ip->flags & IOC3_FLAG_RX_CHECKSUMS))
				ioc3_tcpudp_checksum(skb,
					w0 & ERXBUF_IPCKSUM_MASK, len);

			netif_rx(skb);

			ip->rx_skbs[rx_entry] = NULL;	/* Poison  */

			/* Because we reserve afterwards. */
			skb_put(new_skb, (1664 + RX_OFFSET));
			rxb = (struct ioc3_erxbuf *) new_skb->data;
			skb_reserve(new_skb, RX_OFFSET);

			ip->stats.rx_packets++;		/* Statistics */
			ip->stats.rx_bytes += len;
		} else {
 			/* The frame is invalid and the skb never
                           reached the network layer so we can just
                           recycle it.  */
 			new_skb = skb;
 			ip->stats.rx_errors++;
		}
		if (err & ERXBUF_CRCERR)	/* Statistics */
			ip->stats.rx_crc_errors++;
		if (err & ERXBUF_FRAMERR)
			ip->stats.rx_frame_errors++;
next:
		ip->rx_skbs[n_entry] = new_skb;
		rxr[n_entry] = cpu_to_be64(ioc3_map(rxb, 1));
		rxb->w0 = 0;				/* Clear valid flag */
		n_entry = (n_entry + 1) & 511;		/* Update erpir */

		/* Now go on to the next ring entry.  */
		rx_entry = (rx_entry + 1) & 511;
		skb = ip->rx_skbs[rx_entry];
		rxb = (struct ioc3_erxbuf *) (skb->data - RX_OFFSET);
		w0 = be32_to_cpu(rxb->w0);
	}
	ioc3_w_erpir((n_entry << 3) | ERPIR_ARM);
	ip->rx_pi = n_entry;
	ip->rx_ci = rx_entry;
}