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
struct sockaddr_pkt {int /*<<< orphan*/  spkt_protocol; int /*<<< orphan*/  spkt_device; int /*<<< orphan*/  spkt_family; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct packet_type {struct sock* af_packet_priv; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {struct sockaddr_pkt pkt; } ;
struct TYPE_4__ {TYPE_1__ sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PACKET_LOOPBACK ; 
 TYPE_2__* PACKET_SKB_CB (struct sk_buff*) ; 
 scalar_t__ dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_net (struct sock*) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int packet_rcv_spkt(struct sk_buff *skb, struct net_device *dev,
			   struct packet_type *pt, struct net_device *orig_dev)
{
	struct sock *sk;
	struct sockaddr_pkt *spkt;

	/*
	 *	When we registered the protocol we saved the socket in the data
	 *	field for just this event.
	 */

	sk = pt->af_packet_priv;

	/*
	 *	Yank back the headers [hope the device set this
	 *	right or kerboom...]
	 *
	 *	Incoming packets have ll header pulled,
	 *	push it back.
	 *
	 *	For outgoing ones skb->data == skb_mac_header(skb)
	 *	so that this procedure is noop.
	 */

	if (skb->pkt_type == PACKET_LOOPBACK)
		goto out;

	if (dev_net(dev) != sock_net(sk))
		goto out;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (skb == NULL)
		goto oom;

	/* drop any routing info */
	skb_dst_drop(skb);

	/* drop conntrack reference */
	nf_reset(skb);

	spkt = &PACKET_SKB_CB(skb)->sa.pkt;

	skb_push(skb, skb->data - skb_mac_header(skb));

	/*
	 *	The SOCK_PACKET socket receives _all_ frames.
	 */

	spkt->spkt_family = dev->type;
	strlcpy(spkt->spkt_device, dev->name, sizeof(spkt->spkt_device));
	spkt->spkt_protocol = skb->protocol;

	/*
	 *	Charge the memory to the socket. This is done specifically
	 *	to prevent sockets using all the memory up.
	 */

	if (sock_queue_rcv_skb(sk, skb) == 0)
		return 0;

out:
	kfree_skb(skb);
oom:
	return 0;
}