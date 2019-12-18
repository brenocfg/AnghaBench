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
typedef  int u8 ;
struct sk_buff {scalar_t__ len; TYPE_2__* dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; } ;
struct packet_type {int dummy; } ;
struct net_device {struct dsa_switch_tree* dsa_ptr; } ;
struct dsa_switch_tree {struct dsa_switch** ds; } ;
struct dsa_switch {TYPE_2__** ports; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int DSA_MAX_PORTS ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trailer_rcv(struct sk_buff *skb, struct net_device *dev,
		       struct packet_type *pt, struct net_device *orig_dev)
{
	struct dsa_switch_tree *dst = dev->dsa_ptr;
	struct dsa_switch *ds;
	u8 *trailer;
	int source_port;

	if (unlikely(dst == NULL))
		goto out_drop;
	ds = dst->ds[0];

	skb = skb_unshare(skb, GFP_ATOMIC);
	if (skb == NULL)
		goto out;

	if (skb_linearize(skb))
		goto out_drop;

	trailer = skb_tail_pointer(skb) - 4;
	if (trailer[0] != 0x80 || (trailer[1] & 0xf8) != 0x00 ||
	    (trailer[3] & 0xef) != 0x00 || trailer[3] != 0x00)
		goto out_drop;

	source_port = trailer[1] & 7;
	if (source_port >= DSA_MAX_PORTS || ds->ports[source_port] == NULL)
		goto out_drop;

	pskb_trim_rcsum(skb, skb->len - 4);

	skb->dev = ds->ports[source_port];
	skb_push(skb, ETH_HLEN);
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, skb->dev);

	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;

	netif_receive_skb(skb);

	return 0;

out_drop:
	kfree_skb(skb);
out:
	return 0;
}