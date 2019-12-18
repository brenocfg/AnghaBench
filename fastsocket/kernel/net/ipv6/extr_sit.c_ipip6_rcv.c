#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; scalar_t__ len; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  network_header; int /*<<< orphan*/  mac_header; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel {TYPE_2__* dev; } ;
struct TYPE_7__ {scalar_t__ flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_6__ {int priv_flags; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PORT_UNREACH ; 
 int IFF_ISATAP ; 
 TYPE_4__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipip6_ecn_decapsulate (struct iphdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipip6_lock ; 
 struct ip_tunnel* ipip6_tunnel_lookup (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatap_chksrc (struct sk_buff*,struct iphdr*,struct ip_tunnel*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static int ipip6_rcv(struct sk_buff *skb)
{
	struct iphdr *iph;
	struct ip_tunnel *tunnel;

	if (!pskb_may_pull(skb, sizeof(struct ipv6hdr)))
		goto out;

	iph = ip_hdr(skb);

	read_lock(&ipip6_lock);
	tunnel = ipip6_tunnel_lookup(dev_net(skb->dev), skb->dev,
				     iph->saddr, iph->daddr);
	if (tunnel != NULL) {
		secpath_reset(skb);
		skb->mac_header = skb->network_header;
		skb_reset_network_header(skb);
		IPCB(skb)->flags = 0;
		skb->protocol = htons(ETH_P_IPV6);
		skb->pkt_type = PACKET_HOST;

		if ((tunnel->dev->priv_flags & IFF_ISATAP) &&
		    !isatap_chksrc(skb, iph, tunnel)) {
			tunnel->dev->stats.rx_errors++;
			read_unlock(&ipip6_lock);
			kfree_skb(skb);
			return 0;
		}
		tunnel->dev->stats.rx_packets++;
		tunnel->dev->stats.rx_bytes += skb->len;
		skb->dev = tunnel->dev;
		skb_dst_drop(skb);
		nf_reset(skb);
		ipip6_ecn_decapsulate(iph, skb);
		netif_rx(skb);
		read_unlock(&ipip6_lock);
		return 0;
	}

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
	read_unlock(&ipip6_lock);
out:
	kfree_skb(skb);
	return 0;
}