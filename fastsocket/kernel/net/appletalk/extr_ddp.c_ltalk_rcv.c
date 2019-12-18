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
struct sk_buff {int len; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;
struct ddpehdr {int deh_dnode; int deh_snode; int /*<<< orphan*/  deh_len_hops; scalar_t__ deh_sum; int /*<<< orphan*/  deh_snet; int /*<<< orphan*/  deh_dnet; } ;
struct atalk_addr {int /*<<< orphan*/  s_net; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int DDP_MAXHOPS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct atalk_addr* atalk_find_dev_addr (struct net_device*) ; 
 int atalk_rcv (struct sk_buff*,struct net_device*,struct packet_type*,struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltalk_rcv(struct sk_buff *skb, struct net_device *dev,
		     struct packet_type *pt, struct net_device *orig_dev)
{
	if (!net_eq(dev_net(dev), &init_net))
		goto freeit;

	/* Expand any short form frames */
	if (skb_mac_header(skb)[2] == 1) {
		struct ddpehdr *ddp;
		/* Find our address */
		struct atalk_addr *ap = atalk_find_dev_addr(dev);

		if (!ap || skb->len < sizeof(__be16) || skb->len > 1023)
			goto freeit;

		/* Don't mangle buffer if shared */
		if (!(skb = skb_share_check(skb, GFP_ATOMIC)))
			return 0;

		/*
		 * The push leaves us with a ddephdr not an shdr, and
		 * handily the port bytes in the right place preset.
		 */
		ddp = (struct ddpehdr *) skb_push(skb, sizeof(*ddp) - 4);

		/* Now fill in the long header */

		/*
		 * These two first. The mac overlays the new source/dest
		 * network information so we MUST copy these before
		 * we write the network numbers !
		 */

		ddp->deh_dnode = skb_mac_header(skb)[0];     /* From physical header */
		ddp->deh_snode = skb_mac_header(skb)[1];     /* From physical header */

		ddp->deh_dnet  = ap->s_net;	/* Network number */
		ddp->deh_snet  = ap->s_net;
		ddp->deh_sum   = 0;		/* No checksum */
		/*
		 * Not sure about this bit...
		 */
		/* Non routable, so force a drop if we slip up later */
		ddp->deh_len_hops = htons(skb->len + (DDP_MAXHOPS << 10));
	}
	skb_reset_transport_header(skb);

	return atalk_rcv(skb, dev, pt, orig_dev);
freeit:
	kfree_skb(skb);
	return 0;
}