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
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {unsigned char const* data; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ipv6_opt_hdr {int nexthdr; } ;
struct ip6_mh {int /*<<< orphan*/  ip6mh_type; } ;
struct flowi {int proto; int fl_icmp_type; int fl_icmp_code; int /*<<< orphan*/  fl_ipsec_spi; int /*<<< orphan*/  fl_mh_type; void* fl_ip_dport; void* fl_ip_sport; int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; } ;
typedef  void* __be16 ;
struct TYPE_2__ {size_t nhoff; } ;

/* Variables and functions */
 TYPE_1__* IP6CB (struct sk_buff*) ; 
#define  IPPROTO_AH 141 
#define  IPPROTO_COMP 140 
#define  IPPROTO_DCCP 139 
#define  IPPROTO_ESP 138 
#define  IPPROTO_ICMPV6 137 
#define  IPPROTO_MH 136 
#define  IPPROTO_SCTP 135 
#define  IPPROTO_TCP 134 
#define  IPPROTO_UDP 133 
#define  IPPROTO_UDPLITE 132 
#define  NEXTHDR_DEST 131 
#define  NEXTHDR_FRAGMENT 130 
#define  NEXTHDR_HOP 129 
#define  NEXTHDR_ROUTING 128 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_optlen (struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 

__attribute__((used)) static inline void
_decode_session6(struct sk_buff *skb, struct flowi *fl, int reverse)
{
	int onlyproto = 0;
	u16 offset = skb_network_header_len(skb);
	struct ipv6hdr *hdr = ipv6_hdr(skb);
	struct ipv6_opt_hdr *exthdr;
	const unsigned char *nh = skb_network_header(skb);
	u8 nexthdr = nh[IP6CB(skb)->nhoff];

	memset(fl, 0, sizeof(struct flowi));
	ipv6_addr_copy(&fl->fl6_dst, reverse ? &hdr->saddr : &hdr->daddr);
	ipv6_addr_copy(&fl->fl6_src, reverse ? &hdr->daddr : &hdr->saddr);

	while (nh + offset + 1 < skb->data ||
	       pskb_may_pull(skb, nh + offset + 1 - skb->data)) {
		nh = skb_network_header(skb);
		exthdr = (struct ipv6_opt_hdr *)(nh + offset);

		switch (nexthdr) {
		case NEXTHDR_FRAGMENT:
			onlyproto = 1;
		case NEXTHDR_ROUTING:
		case NEXTHDR_HOP:
		case NEXTHDR_DEST:
			offset += ipv6_optlen(exthdr);
			nexthdr = exthdr->nexthdr;
			exthdr = (struct ipv6_opt_hdr *)(nh + offset);
			break;

		case IPPROTO_UDP:
		case IPPROTO_UDPLITE:
		case IPPROTO_TCP:
		case IPPROTO_SCTP:
		case IPPROTO_DCCP:
			if (!onlyproto && (nh + offset + 4 < skb->data ||
			     pskb_may_pull(skb, nh + offset + 4 - skb->data))) {
				__be16 *ports = (__be16 *)exthdr;

				fl->fl_ip_sport = ports[!!reverse];
				fl->fl_ip_dport = ports[!reverse];
			}
			fl->proto = nexthdr;
			return;

		case IPPROTO_ICMPV6:
			if (!onlyproto && pskb_may_pull(skb, nh + offset + 2 - skb->data)) {
				u8 *icmp = (u8 *)exthdr;

				fl->fl_icmp_type = icmp[0];
				fl->fl_icmp_code = icmp[1];
			}
			fl->proto = nexthdr;
			return;

#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
		case IPPROTO_MH:
			if (!onlyproto && pskb_may_pull(skb, nh + offset + 3 - skb->data)) {
				struct ip6_mh *mh;
				mh = (struct ip6_mh *)exthdr;

				fl->fl_mh_type = mh->ip6mh_type;
			}
			fl->proto = nexthdr;
			return;
#endif

		/* XXX Why are there these headers? */
		case IPPROTO_AH:
		case IPPROTO_ESP:
		case IPPROTO_COMP:
		default:
			fl->fl_ipsec_spi = 0;
			fl->proto = nexthdr;
			return;
		}
	}
}