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
struct sk_buff {unsigned int len; int /*<<< orphan*/ * sk; scalar_t__ data; struct net_device* dev; } ;
struct net_device_stats {unsigned int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ arp_find (unsigned char*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rose_route_frame (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rose_rebuild_header(struct sk_buff *skb)
{
#ifdef CONFIG_INET
	struct net_device *dev = skb->dev;
	struct net_device_stats *stats = &dev->stats;
	unsigned char *bp = (unsigned char *)skb->data;
	struct sk_buff *skbn;
	unsigned int len;

	if (arp_find(bp + 7, skb)) {
		return 1;
	}

	if ((skbn = skb_clone(skb, GFP_ATOMIC)) == NULL) {
		kfree_skb(skb);
		return 1;
	}

	if (skb->sk != NULL)
		skb_set_owner_w(skbn, skb->sk);

	kfree_skb(skb);

	len = skbn->len;

	if (!rose_route_frame(skbn, NULL)) {
		kfree_skb(skbn);
		stats->tx_errors++;
		return 1;
	}

	stats->tx_packets++;
	stats->tx_bytes += len;
#endif
	return 1;
}