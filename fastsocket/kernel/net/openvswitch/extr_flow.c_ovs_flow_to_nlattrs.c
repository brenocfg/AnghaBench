#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/ * tll; int /*<<< orphan*/ * sll; int /*<<< orphan*/  target; } ;
struct TYPE_22__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_16__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_24__ {TYPE_8__ nd; TYPE_7__ tp; int /*<<< orphan*/  label; TYPE_1__ addr; } ;
struct TYPE_21__ {scalar_t__ proto; scalar_t__ frag; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_14__ {scalar_t__ type; scalar_t__ tci; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
struct TYPE_19__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_18__ {int /*<<< orphan*/ * tha; int /*<<< orphan*/ * sha; } ;
struct TYPE_17__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_20__ {TYPE_4__ tp; TYPE_3__ arp; TYPE_2__ addr; } ;
struct TYPE_13__ {scalar_t__ priority; scalar_t__ in_port; scalar_t__ skb_mark; } ;
struct TYPE_15__ {scalar_t__ ipv4_dst; } ;
struct sw_flow_key {TYPE_9__ ipv6; TYPE_6__ ip; TYPE_11__ eth; TYPE_5__ ipv4; TYPE_10__ phy; TYPE_12__ tun_key; } ;
struct sk_buff {int dummy; } ;
struct ovs_key_udp {int /*<<< orphan*/  udp_dst; int /*<<< orphan*/  udp_src; } ;
struct ovs_key_tcp {int /*<<< orphan*/  tcp_dst; int /*<<< orphan*/  tcp_src; } ;
struct ovs_key_nd {int /*<<< orphan*/  nd_tll; int /*<<< orphan*/  nd_sll; int /*<<< orphan*/  nd_target; } ;
struct ovs_key_ipv6 {scalar_t__ ipv6_proto; scalar_t__ ipv6_frag; int /*<<< orphan*/  ipv6_hlimit; int /*<<< orphan*/  ipv6_tclass; int /*<<< orphan*/  ipv6_label; int /*<<< orphan*/  ipv6_dst; int /*<<< orphan*/  ipv6_src; } ;
struct ovs_key_ipv4 {scalar_t__ ipv4_proto; scalar_t__ ipv4_frag; int /*<<< orphan*/  ipv4_ttl; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  ipv4_dst; int /*<<< orphan*/  ipv4_src; } ;
struct ovs_key_icmpv6 {scalar_t__ icmpv6_type; void* icmpv6_code; } ;
struct ovs_key_icmp {void* icmp_code; void* icmp_type; } ;
struct ovs_key_ethernet {int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  eth_src; } ;
struct ovs_key_arp {int /*<<< orphan*/  arp_tha; int /*<<< orphan*/  arp_sha; scalar_t__ arp_op; int /*<<< orphan*/  arp_tip; int /*<<< orphan*/  arp_sip; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_MAX_PORTS ; 
 int EMSGSIZE ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_P_8021Q ; 
 scalar_t__ ETH_P_802_2 ; 
 scalar_t__ ETH_P_ARP ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ ETH_P_RARP ; 
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ NDISC_NEIGHBOUR_ADVERTISEMENT ; 
 scalar_t__ NDISC_NEIGHBOUR_SOLICITATION ; 
 scalar_t__ OVS_FRAG_TYPE_LATER ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ARP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ENCAP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ETHERNET ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ETHERTYPE ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ICMP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ICMPV6 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IN_PORT ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IPV4 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IPV6 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ND ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_PRIORITY ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_SKB_MARK ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_TCP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_UDP ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_VLAN ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ovs_key_arp*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ ovs_ipv4_tun_to_nlattr (struct sk_buff*,TYPE_12__*) ; 

int ovs_flow_to_nlattrs(const struct sw_flow_key *swkey, struct sk_buff *skb)
{
	struct ovs_key_ethernet *eth_key;
	struct nlattr *nla, *encap;

	if (swkey->phy.priority &&
	    nla_put_u32(skb, OVS_KEY_ATTR_PRIORITY, swkey->phy.priority))
		goto nla_put_failure;

	if (swkey->tun_key.ipv4_dst &&
	    ovs_ipv4_tun_to_nlattr(skb, &swkey->tun_key))
		goto nla_put_failure;

	if (swkey->phy.in_port != DP_MAX_PORTS &&
	    nla_put_u32(skb, OVS_KEY_ATTR_IN_PORT, swkey->phy.in_port))
		goto nla_put_failure;

	if (swkey->phy.skb_mark &&
	    nla_put_u32(skb, OVS_KEY_ATTR_SKB_MARK, swkey->phy.skb_mark))
		goto nla_put_failure;

	nla = nla_reserve(skb, OVS_KEY_ATTR_ETHERNET, sizeof(*eth_key));
	if (!nla)
		goto nla_put_failure;
	eth_key = nla_data(nla);
	memcpy(eth_key->eth_src, swkey->eth.src, ETH_ALEN);
	memcpy(eth_key->eth_dst, swkey->eth.dst, ETH_ALEN);

	if (swkey->eth.tci || swkey->eth.type == htons(ETH_P_8021Q)) {
		if (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE, htons(ETH_P_8021Q)) ||
		    nla_put_be16(skb, OVS_KEY_ATTR_VLAN, swkey->eth.tci))
			goto nla_put_failure;
		encap = nla_nest_start(skb, OVS_KEY_ATTR_ENCAP);
		if (!swkey->eth.tci)
			goto unencap;
	} else {
		encap = NULL;
	}

	if (swkey->eth.type == htons(ETH_P_802_2))
		goto unencap;

	if (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE, swkey->eth.type))
		goto nla_put_failure;

	if (swkey->eth.type == htons(ETH_P_IP)) {
		struct ovs_key_ipv4 *ipv4_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_IPV4, sizeof(*ipv4_key));
		if (!nla)
			goto nla_put_failure;
		ipv4_key = nla_data(nla);
		ipv4_key->ipv4_src = swkey->ipv4.addr.src;
		ipv4_key->ipv4_dst = swkey->ipv4.addr.dst;
		ipv4_key->ipv4_proto = swkey->ip.proto;
		ipv4_key->ipv4_tos = swkey->ip.tos;
		ipv4_key->ipv4_ttl = swkey->ip.ttl;
		ipv4_key->ipv4_frag = swkey->ip.frag;
	} else if (swkey->eth.type == htons(ETH_P_IPV6)) {
		struct ovs_key_ipv6 *ipv6_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_IPV6, sizeof(*ipv6_key));
		if (!nla)
			goto nla_put_failure;
		ipv6_key = nla_data(nla);
		memcpy(ipv6_key->ipv6_src, &swkey->ipv6.addr.src,
				sizeof(ipv6_key->ipv6_src));
		memcpy(ipv6_key->ipv6_dst, &swkey->ipv6.addr.dst,
				sizeof(ipv6_key->ipv6_dst));
		ipv6_key->ipv6_label = swkey->ipv6.label;
		ipv6_key->ipv6_proto = swkey->ip.proto;
		ipv6_key->ipv6_tclass = swkey->ip.tos;
		ipv6_key->ipv6_hlimit = swkey->ip.ttl;
		ipv6_key->ipv6_frag = swkey->ip.frag;
	} else if (swkey->eth.type == htons(ETH_P_ARP) ||
		   swkey->eth.type == htons(ETH_P_RARP)) {
		struct ovs_key_arp *arp_key;

		nla = nla_reserve(skb, OVS_KEY_ATTR_ARP, sizeof(*arp_key));
		if (!nla)
			goto nla_put_failure;
		arp_key = nla_data(nla);
		memset(arp_key, 0, sizeof(struct ovs_key_arp));
		arp_key->arp_sip = swkey->ipv4.addr.src;
		arp_key->arp_tip = swkey->ipv4.addr.dst;
		arp_key->arp_op = htons(swkey->ip.proto);
		memcpy(arp_key->arp_sha, swkey->ipv4.arp.sha, ETH_ALEN);
		memcpy(arp_key->arp_tha, swkey->ipv4.arp.tha, ETH_ALEN);
	}

	if ((swkey->eth.type == htons(ETH_P_IP) ||
	     swkey->eth.type == htons(ETH_P_IPV6)) &&
	     swkey->ip.frag != OVS_FRAG_TYPE_LATER) {

		if (swkey->ip.proto == IPPROTO_TCP) {
			struct ovs_key_tcp *tcp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_TCP, sizeof(*tcp_key));
			if (!nla)
				goto nla_put_failure;
			tcp_key = nla_data(nla);
			if (swkey->eth.type == htons(ETH_P_IP)) {
				tcp_key->tcp_src = swkey->ipv4.tp.src;
				tcp_key->tcp_dst = swkey->ipv4.tp.dst;
			} else if (swkey->eth.type == htons(ETH_P_IPV6)) {
				tcp_key->tcp_src = swkey->ipv6.tp.src;
				tcp_key->tcp_dst = swkey->ipv6.tp.dst;
			}
		} else if (swkey->ip.proto == IPPROTO_UDP) {
			struct ovs_key_udp *udp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_UDP, sizeof(*udp_key));
			if (!nla)
				goto nla_put_failure;
			udp_key = nla_data(nla);
			if (swkey->eth.type == htons(ETH_P_IP)) {
				udp_key->udp_src = swkey->ipv4.tp.src;
				udp_key->udp_dst = swkey->ipv4.tp.dst;
			} else if (swkey->eth.type == htons(ETH_P_IPV6)) {
				udp_key->udp_src = swkey->ipv6.tp.src;
				udp_key->udp_dst = swkey->ipv6.tp.dst;
			}
		} else if (swkey->eth.type == htons(ETH_P_IP) &&
			   swkey->ip.proto == IPPROTO_ICMP) {
			struct ovs_key_icmp *icmp_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_ICMP, sizeof(*icmp_key));
			if (!nla)
				goto nla_put_failure;
			icmp_key = nla_data(nla);
			icmp_key->icmp_type = ntohs(swkey->ipv4.tp.src);
			icmp_key->icmp_code = ntohs(swkey->ipv4.tp.dst);
		} else if (swkey->eth.type == htons(ETH_P_IPV6) &&
			   swkey->ip.proto == IPPROTO_ICMPV6) {
			struct ovs_key_icmpv6 *icmpv6_key;

			nla = nla_reserve(skb, OVS_KEY_ATTR_ICMPV6,
						sizeof(*icmpv6_key));
			if (!nla)
				goto nla_put_failure;
			icmpv6_key = nla_data(nla);
			icmpv6_key->icmpv6_type = ntohs(swkey->ipv6.tp.src);
			icmpv6_key->icmpv6_code = ntohs(swkey->ipv6.tp.dst);

			if (icmpv6_key->icmpv6_type == NDISC_NEIGHBOUR_SOLICITATION ||
			    icmpv6_key->icmpv6_type == NDISC_NEIGHBOUR_ADVERTISEMENT) {
				struct ovs_key_nd *nd_key;

				nla = nla_reserve(skb, OVS_KEY_ATTR_ND, sizeof(*nd_key));
				if (!nla)
					goto nla_put_failure;
				nd_key = nla_data(nla);
				memcpy(nd_key->nd_target, &swkey->ipv6.nd.target,
							sizeof(nd_key->nd_target));
				memcpy(nd_key->nd_sll, swkey->ipv6.nd.sll, ETH_ALEN);
				memcpy(nd_key->nd_tll, swkey->ipv6.nd.tll, ETH_ALEN);
			}
		}
	}

unencap:
	if (encap)
		nla_nest_end(skb, encap);

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}