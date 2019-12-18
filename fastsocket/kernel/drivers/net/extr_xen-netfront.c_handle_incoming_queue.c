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
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct page {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_8__ {unsigned int offset; struct page* page; } ;
struct TYPE_7__ {TYPE_1__* frags; } ;
struct TYPE_5__ {struct page* page; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 TYPE_4__* NETFRONT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 void* page_address (struct page*) ; 
 scalar_t__ skb_checksum_setup (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int handle_incoming_queue(struct net_device *dev,
				 struct sk_buff_head *rxq)
{
	int packets_dropped = 0;
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(rxq)) != NULL) {
		struct page *page = NETFRONT_SKB_CB(skb)->page;
		void *vaddr = page_address(page);
		unsigned offset = NETFRONT_SKB_CB(skb)->offset;

		memcpy(skb->data, vaddr + offset,
		       skb_headlen(skb));

		if (page != skb_shinfo(skb)->frags[0].page)
			__free_page(page);

		/* Ethernet work: Delayed to here as it peeks the header. */
		skb->protocol = eth_type_trans(skb, dev);

		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			if (skb_checksum_setup(skb)) {
				kfree_skb(skb);
				packets_dropped++;
				dev->stats.rx_errors++;
				continue;
			}
		}

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;

		/* Pass it up. */
		netif_receive_skb(skb);
	}

	return packets_dropped;
}