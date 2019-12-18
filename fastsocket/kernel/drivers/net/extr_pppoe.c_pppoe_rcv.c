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
struct sk_buff {int len; } ;
struct pppox_sock {int dummy; } ;
struct pppoe_net {int dummy; } ;
struct pppoe_hdr {int /*<<< orphan*/  sid; int /*<<< orphan*/  length; } ;
struct packet_type {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 struct pppox_sock* get_item (struct pppoe_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct pppoe_hdr* pppoe_hdr (struct sk_buff*) ; 
 struct pppoe_net* pppoe_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ pskb_trim_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sk_pppox (struct pppox_sock*) ; 
 int sk_receive_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pppoe_rcv(struct sk_buff *skb, struct net_device *dev,
		     struct packet_type *pt, struct net_device *orig_dev)
{
	struct pppoe_hdr *ph;
	struct pppox_sock *po;
	struct pppoe_net *pn;
	int len;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (!pskb_may_pull(skb, sizeof(struct pppoe_hdr)))
		goto drop;

	ph = pppoe_hdr(skb);
	len = ntohs(ph->length);

	skb_pull_rcsum(skb, sizeof(*ph));
	if (skb->len < len)
		goto drop;

	if (pskb_trim_rcsum(skb, len))
		goto drop;

	pn = pppoe_pernet(dev_net(dev));

	/* Note that get_item does a sock_hold(), so sk_pppox(po)
	 * is known to be safe.
	 */
	po = get_item(pn, ph->sid, eth_hdr(skb)->h_source, dev->ifindex);
	if (!po)
		goto drop;

	return sk_receive_skb(sk_pppox(po), skb, 0);

drop:
	kfree_skb(skb);
out:
	return NET_RX_DROP;
}