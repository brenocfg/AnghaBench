#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct ioc3_private {unsigned long* rxr; int rx_pi; scalar_t__ tx_ci; scalar_t__ tx_pi; struct ioc3_etxd* txr; scalar_t__ rx_ci; struct sk_buff** rx_skbs; } ;
struct ioc3_etxd {int dummy; } ;
struct ioc3_erxbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_BUFFS ; 
 int /*<<< orphan*/  RX_BUF_ALLOC_SIZE ; 
 scalar_t__ RX_OFFSET ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 unsigned long cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 struct sk_buff* ioc3_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_map (struct ioc3_erxbuf*,int) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  show_free_areas () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void ioc3_alloc_rings(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3_erxbuf *rxb;
	unsigned long *rxr;
	int i;

	if (ip->rxr == NULL) {
		/* Allocate and initialize rx ring.  4kb = 512 entries  */
		ip->rxr = (unsigned long *) get_zeroed_page(GFP_ATOMIC);
		rxr = (unsigned long *) ip->rxr;
		if (!rxr)
			printk("ioc3_alloc_rings(): get_zeroed_page() failed!\n");

		/* Now the rx buffers.  The RX ring may be larger but
		   we only allocate 16 buffers for now.  Need to tune
		   this for performance and memory later.  */
		for (i = 0; i < RX_BUFFS; i++) {
			struct sk_buff *skb;

			skb = ioc3_alloc_skb(RX_BUF_ALLOC_SIZE, GFP_ATOMIC);
			if (!skb) {
				show_free_areas();
				continue;
			}

			ip->rx_skbs[i] = skb;

			/* Because we reserve afterwards. */
			skb_put(skb, (1664 + RX_OFFSET));
			rxb = (struct ioc3_erxbuf *) skb->data;
			rxr[i] = cpu_to_be64(ioc3_map(rxb, 1));
			skb_reserve(skb, RX_OFFSET);
		}
		ip->rx_ci = 0;
		ip->rx_pi = RX_BUFFS;
	}

	if (ip->txr == NULL) {
		/* Allocate and initialize tx rings.  16kb = 128 bufs.  */
		ip->txr = (struct ioc3_etxd *)__get_free_pages(GFP_KERNEL, 2);
		if (!ip->txr)
			printk("ioc3_alloc_rings(): __get_free_pages() failed!\n");
		ip->tx_pi = 0;
		ip->tx_ci = 0;
	}
}