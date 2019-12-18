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
struct trllc {scalar_t__ ethertype; } ;
struct trh_hdr {int /*<<< orphan*/  daddr; } ;
struct sk_buff {struct net_device* dev; scalar_t__ data; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ arp_find (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_source_route (struct sk_buff*,struct trh_hdr*,struct net_device*) ; 

__attribute__((used)) static int tr_rebuild_header(struct sk_buff *skb)
{
	struct trh_hdr *trh=(struct trh_hdr *)skb->data;
	struct trllc *trllc=(struct trllc *)(skb->data+sizeof(struct trh_hdr));
	struct net_device *dev = skb->dev;

	/*
	 *	FIXME: We don't yet support IPv6 over token rings
	 */

	if(trllc->ethertype != htons(ETH_P_IP)) {
		printk("tr_rebuild_header: Don't know how to resolve type %04X addresses ?\n", ntohs(trllc->ethertype));
		return 0;
	}

#ifdef CONFIG_INET
	if(arp_find(trh->daddr, skb)) {
			return 1;
	}
	else
#endif
	{
		tr_source_route(skb,trh,dev);
		return 0;
	}
}