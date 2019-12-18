#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct udphdr {int source; int dest; } ;
struct tcphdr {int source; int dest; } ;
struct TYPE_26__ {scalar_t__ proto; scalar_t__ frag; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_20__ {int src; int dst; } ;
struct TYPE_21__ {TYPE_3__ tp; } ;
struct TYPE_23__ {int tci; int type; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
struct TYPE_19__ {int /*<<< orphan*/ * tha; int /*<<< orphan*/ * sha; } ;
struct TYPE_24__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_18__ {int src; int dst; } ;
struct TYPE_25__ {TYPE_2__ arp; TYPE_7__ addr; TYPE_1__ tp; } ;
struct TYPE_22__ {int /*<<< orphan*/  skb_mark; int /*<<< orphan*/  in_port; int /*<<< orphan*/  priority; } ;
struct sw_flow_key {TYPE_9__ ip; TYPE_4__ ipv6; TYPE_6__ eth; TYPE_8__ ipv4; TYPE_5__ phy; int /*<<< orphan*/  tun_key; } ;
struct sk_buff {int /*<<< orphan*/  network_header; int /*<<< orphan*/  transport_header; scalar_t__ data; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; } ;
struct iphdr {scalar_t__ protocol; int frag_off; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct icmphdr {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct ethhdr {int h_proto; scalar_t__ h_dest; scalar_t__ h_source; } ;
struct arp_eth_header {int ar_hrd; int ar_pro; int ar_hln; int ar_pln; scalar_t__ ar_tha; scalar_t__ ar_sha; scalar_t__ ar_tip; scalar_t__ ar_sip; int /*<<< orphan*/  ar_op; } ;
typedef  int __be16 ;
struct TYPE_17__ {scalar_t__ tun_key; } ;
struct TYPE_16__ {int /*<<< orphan*/  arp; int /*<<< orphan*/  tp; int /*<<< orphan*/  addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  tp; } ;
struct TYPE_14__ {int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_RARP ; 
 int IPPROTO_ICMP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_MF ; 
 int /*<<< orphan*/  IP_OFFSET ; 
 scalar_t__ NEXTHDR_ICMP ; 
 scalar_t__ NEXTHDR_TCP ; 
 scalar_t__ NEXTHDR_UDP ; 
 TYPE_13__* OVS_CB (struct sk_buff*) ; 
 void* OVS_FRAG_TYPE_FIRST ; 
 scalar_t__ OVS_FRAG_TYPE_LATER ; 
 int SKB_GSO_UDP ; 
 int SW_FLOW_KEY_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,scalar_t__) ; 
 scalar_t__ arphdr_ok (struct sk_buff*) ; 
 int check_iphdr (struct sk_buff*) ; 
 struct ethhdr* eth ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 scalar_t__ icmp6hdr_ok (struct sk_buff*) ; 
 struct icmphdr* icmp_hdr (struct sk_buff*) ; 
 scalar_t__ icmphdr_ok (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 TYPE_12__ ipv4 ; 
 TYPE_11__ ipv6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct sw_flow_key*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int parse_ethertype (struct sk_buff*) ; 
 int parse_icmpv6 (struct sk_buff*,struct sw_flow_key*,int*,int) ; 
 int parse_ipv6hdr (struct sk_buff*,struct sw_flow_key*,int*) ; 
 int parse_vlan (struct sk_buff*,struct sw_flow_key*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 TYPE_10__* skb_shinfo (struct sk_buff*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcphdr_ok (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 scalar_t__ udphdr_ok (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

int ovs_flow_extract(struct sk_buff *skb, u16 in_port, struct sw_flow_key *key,
		 int *key_lenp)
{
	int error = 0;
	int key_len = SW_FLOW_KEY_OFFSET(eth);
	struct ethhdr *eth;

	memset(key, 0, sizeof(*key));

	key->phy.priority = skb->priority;
	if (OVS_CB(skb)->tun_key)
		memcpy(&key->tun_key, OVS_CB(skb)->tun_key, sizeof(key->tun_key));
	key->phy.in_port = in_port;
	key->phy.skb_mark = skb->mark;

	skb_reset_mac_header(skb);

	/* Link layer.  We are guaranteed to have at least the 14 byte Ethernet
	 * header in the linear data area.
	 */
	eth = eth_hdr(skb);
	memcpy(key->eth.src, eth->h_source, ETH_ALEN);
	memcpy(key->eth.dst, eth->h_dest, ETH_ALEN);

	__skb_pull(skb, 2 * ETH_ALEN);
	/* We are going to push all headers that we pull, so no need to
	 * update skb->csum here.
	 */

	if (vlan_tx_tag_present(skb))
		key->eth.tci = htons(skb->vlan_tci);
	else if (eth->h_proto == htons(ETH_P_8021Q))
		if (unlikely(parse_vlan(skb, key)))
			return -ENOMEM;

	key->eth.type = parse_ethertype(skb);
	if (unlikely(key->eth.type == htons(0)))
		return -ENOMEM;

	skb_reset_network_header(skb);
	__skb_push(skb, skb->data - skb_mac_header(skb));

	/* Network layer. */
	if (key->eth.type == htons(ETH_P_IP)) {
		struct iphdr *nh;
		__be16 offset;

		key_len = SW_FLOW_KEY_OFFSET(ipv4.addr);

		error = check_iphdr(skb);
		if (unlikely(error)) {
			if (error == -EINVAL) {
				skb->transport_header = skb->network_header;
				error = 0;
			}
			goto out;
		}

		nh = ip_hdr(skb);
		key->ipv4.addr.src = nh->saddr;
		key->ipv4.addr.dst = nh->daddr;

		key->ip.proto = nh->protocol;
		key->ip.tos = nh->tos;
		key->ip.ttl = nh->ttl;

		offset = nh->frag_off & htons(IP_OFFSET);
		if (offset) {
			key->ip.frag = OVS_FRAG_TYPE_LATER;
			goto out;
		}
		if (nh->frag_off & htons(IP_MF) ||
			 skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
			key->ip.frag = OVS_FRAG_TYPE_FIRST;

		/* Transport layer. */
		if (key->ip.proto == IPPROTO_TCP) {
			key_len = SW_FLOW_KEY_OFFSET(ipv4.tp);
			if (tcphdr_ok(skb)) {
				struct tcphdr *tcp = tcp_hdr(skb);
				key->ipv4.tp.src = tcp->source;
				key->ipv4.tp.dst = tcp->dest;
			}
		} else if (key->ip.proto == IPPROTO_UDP) {
			key_len = SW_FLOW_KEY_OFFSET(ipv4.tp);
			if (udphdr_ok(skb)) {
				struct udphdr *udp = udp_hdr(skb);
				key->ipv4.tp.src = udp->source;
				key->ipv4.tp.dst = udp->dest;
			}
		} else if (key->ip.proto == IPPROTO_ICMP) {
			key_len = SW_FLOW_KEY_OFFSET(ipv4.tp);
			if (icmphdr_ok(skb)) {
				struct icmphdr *icmp = icmp_hdr(skb);
				/* The ICMP type and code fields use the 16-bit
				 * transport port fields, so we need to store
				 * them in 16-bit network byte order. */
				key->ipv4.tp.src = htons(icmp->type);
				key->ipv4.tp.dst = htons(icmp->code);
			}
		}

	} else if ((key->eth.type == htons(ETH_P_ARP) ||
		   key->eth.type == htons(ETH_P_RARP)) && arphdr_ok(skb)) {
		struct arp_eth_header *arp;

		arp = (struct arp_eth_header *)skb_network_header(skb);

		if (arp->ar_hrd == htons(ARPHRD_ETHER)
				&& arp->ar_pro == htons(ETH_P_IP)
				&& arp->ar_hln == ETH_ALEN
				&& arp->ar_pln == 4) {

			/* We only match on the lower 8 bits of the opcode. */
			if (ntohs(arp->ar_op) <= 0xff)
				key->ip.proto = ntohs(arp->ar_op);
			memcpy(&key->ipv4.addr.src, arp->ar_sip, sizeof(key->ipv4.addr.src));
			memcpy(&key->ipv4.addr.dst, arp->ar_tip, sizeof(key->ipv4.addr.dst));
			memcpy(key->ipv4.arp.sha, arp->ar_sha, ETH_ALEN);
			memcpy(key->ipv4.arp.tha, arp->ar_tha, ETH_ALEN);
			key_len = SW_FLOW_KEY_OFFSET(ipv4.arp);
		}
	} else if (key->eth.type == htons(ETH_P_IPV6)) {
		int nh_len;             /* IPv6 Header + Extensions */

		nh_len = parse_ipv6hdr(skb, key, &key_len);
		if (unlikely(nh_len < 0)) {
			if (nh_len == -EINVAL)
				skb->transport_header = skb->network_header;
			else
				error = nh_len;
			goto out;
		}

		if (key->ip.frag == OVS_FRAG_TYPE_LATER)
			goto out;
		if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
			key->ip.frag = OVS_FRAG_TYPE_FIRST;

		/* Transport layer. */
		if (key->ip.proto == NEXTHDR_TCP) {
			key_len = SW_FLOW_KEY_OFFSET(ipv6.tp);
			if (tcphdr_ok(skb)) {
				struct tcphdr *tcp = tcp_hdr(skb);
				key->ipv6.tp.src = tcp->source;
				key->ipv6.tp.dst = tcp->dest;
			}
		} else if (key->ip.proto == NEXTHDR_UDP) {
			key_len = SW_FLOW_KEY_OFFSET(ipv6.tp);
			if (udphdr_ok(skb)) {
				struct udphdr *udp = udp_hdr(skb);
				key->ipv6.tp.src = udp->source;
				key->ipv6.tp.dst = udp->dest;
			}
		} else if (key->ip.proto == NEXTHDR_ICMP) {
			key_len = SW_FLOW_KEY_OFFSET(ipv6.tp);
			if (icmp6hdr_ok(skb)) {
				error = parse_icmpv6(skb, key, &key_len, nh_len);
				if (error < 0)
					goto out;
			}
		}
	}

out:
	*key_lenp = key_len;
	return error;
}