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
struct sk_buff {TYPE_2__* dev; scalar_t__ len; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  network_header; int /*<<< orphan*/  mac_header; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipip_ecn_decapsulate (struct iphdr const*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipip_lock ; 
 struct ip_tunnel* ipip_tunnel_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm4_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int ipip_rcv(struct sk_buff *skb)
{
	struct ip_tunnel *tunnel;
	const struct iphdr *iph = ip_hdr(skb);

	read_lock(&ipip_lock);
	if ((tunnel = ipip_tunnel_lookup(dev_net(skb->dev),
					iph->saddr, iph->daddr)) != NULL) {
		if (!xfrm4_policy_check(NULL, XFRM_POLICY_IN, skb)) {
			read_unlock(&ipip_lock);
			kfree_skb(skb);
			return 0;
		}

		secpath_reset(skb);

		skb->mac_header = skb->network_header;
		skb_reset_network_header(skb);
		skb->protocol = htons(ETH_P_IP);
		skb->pkt_type = PACKET_HOST;

		tunnel->dev->stats.rx_packets++;
		tunnel->dev->stats.rx_bytes += skb->len;
		skb->dev = tunnel->dev;
		skb_dst_drop(skb);
		nf_reset(skb);
		ipip_ecn_decapsulate(iph, skb);
		netif_rx(skb);
		read_unlock(&ipip_lock);
		return 0;
	}
	read_unlock(&ipip_lock);

	return -1;
}