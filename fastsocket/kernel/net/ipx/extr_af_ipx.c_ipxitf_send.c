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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; scalar_t__ data; } ;
struct net_device {int flags; int addr_len; char* broadcast; } ;
struct TYPE_7__ {scalar_t__ net; } ;
struct TYPE_6__ {scalar_t__ net; } ;
struct ipxhdr {scalar_t__ ipx_tctrl; TYPE_3__ ipx_source; TYPE_2__ ipx_dest; } ;
struct ipx_interface {scalar_t__ if_netnum; int /*<<< orphan*/  if_node; struct datalink_proto* if_dlink; struct net_device* if_dev; } ;
struct datalink_proto {int /*<<< orphan*/  (* request ) (struct datalink_proto*,struct sk_buff*,char*) ;} ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {int index; int /*<<< orphan*/  netnum; } ;
struct TYPE_8__ {scalar_t__ ipx_tctrl; scalar_t__ ipx_dest_net; scalar_t__ ipx_source_net; TYPE_1__ last_hop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPX ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_LOOPBACK ; 
 int IPX_NODE_LEN ; 
 TYPE_4__* IPX_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_broadcast_node ; 
 struct ipxhdr* ipx_hdr (struct sk_buff*) ; 
 struct ipx_interface* ipx_internal_net ; 
 scalar_t__ ipxcfg_max_hops ; 
 struct sk_buff* ipxitf_adjust_skbuff (struct ipx_interface*,struct sk_buff*) ; 
 int ipxitf_demux_socket (struct ipx_interface*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct datalink_proto*,struct sk_buff*,char*) ; 

int ipxitf_send(struct ipx_interface *intrfc, struct sk_buff *skb, char *node)
{
	struct ipxhdr *ipx = ipx_hdr(skb);
	struct net_device *dev = intrfc->if_dev;
	struct datalink_proto *dl = intrfc->if_dlink;
	char dest_node[IPX_NODE_LEN];
	int send_to_wire = 1;
	int addr_len;

	ipx->ipx_tctrl = IPX_SKB_CB(skb)->ipx_tctrl;
	ipx->ipx_dest.net = IPX_SKB_CB(skb)->ipx_dest_net;
	ipx->ipx_source.net = IPX_SKB_CB(skb)->ipx_source_net;

	/* see if we need to include the netnum in the route list */
	if (IPX_SKB_CB(skb)->last_hop.index >= 0) {
		__be32 *last_hop = (__be32 *)(((u8 *) skb->data) +
				sizeof(struct ipxhdr) +
				IPX_SKB_CB(skb)->last_hop.index *
				sizeof(__be32));
		*last_hop = IPX_SKB_CB(skb)->last_hop.netnum;
		IPX_SKB_CB(skb)->last_hop.index = -1;
	}

	/*
	 * We need to know how many skbuffs it will take to send out this
	 * packet to avoid unnecessary copies.
	 */

	if (!dl || !dev || dev->flags & IFF_LOOPBACK)
		send_to_wire = 0;	/* No non looped */

	/*
	 * See if this should be demuxed to sockets on this interface
	 *
	 * We want to ensure the original was eaten or that we only use
	 * up clones.
	 */

	if (ipx->ipx_dest.net == intrfc->if_netnum) {
		/*
		 * To our own node, loop and free the original.
		 * The internal net will receive on all node address.
		 */
		if (intrfc == ipx_internal_net ||
		    !memcmp(intrfc->if_node, node, IPX_NODE_LEN)) {
			/* Don't charge sender */
			skb_orphan(skb);

			/* Will charge receiver */
			return ipxitf_demux_socket(intrfc, skb, 0);
		}

		/* Broadcast, loop and possibly keep to send on. */
		if (!memcmp(ipx_broadcast_node, node, IPX_NODE_LEN)) {
			if (!send_to_wire)
				skb_orphan(skb);
			ipxitf_demux_socket(intrfc, skb, send_to_wire);
			if (!send_to_wire)
				goto out;
		}
	}

	/*
	 * If the originating net is not equal to our net; this is routed
	 * We are still charging the sender. Which is right - the driver
	 * free will handle this fairly.
	 */
	if (ipx->ipx_source.net != intrfc->if_netnum) {
		/*
		 * Unshare the buffer before modifying the count in
		 * case it's a flood or tcpdump
		 */
		skb = skb_unshare(skb, GFP_ATOMIC);
		if (!skb)
			goto out;
		if (++ipx->ipx_tctrl > ipxcfg_max_hops)
			send_to_wire = 0;
	}

	if (!send_to_wire) {
		kfree_skb(skb);
		goto out;
	}

	/* Determine the appropriate hardware address */
	addr_len = dev->addr_len;
	if (!memcmp(ipx_broadcast_node, node, IPX_NODE_LEN))
		memcpy(dest_node, dev->broadcast, addr_len);
	else
		memcpy(dest_node, &(node[IPX_NODE_LEN-addr_len]), addr_len);

	/* Make any compensation for differing physical/data link size */
	skb = ipxitf_adjust_skbuff(intrfc, skb);
	if (!skb)
		goto out;

	/* set up data link and physical headers */
	skb->dev	= dev;
	skb->protocol	= htons(ETH_P_IPX);

	/* Send it out */
	dl->request(dl, skb, dest_node);
out:
	return 0;
}