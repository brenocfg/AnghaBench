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
typedef  void* u8 ;
struct sk_buff {void** data; } ;
struct iphdr {int ihl; int frag_off; int protocol; int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct flowi {int proto; int /*<<< orphan*/  fl4_tos; int /*<<< orphan*/  fl4_src; int /*<<< orphan*/  fl4_dst; void* fl_ipsec_spi; void* fl_icmp_code; void* fl_icmp_type; void* fl_ip_dport; void* fl_ip_sport; } ;
typedef  void* __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
#define  IPPROTO_AH 136 
#define  IPPROTO_COMP 135 
#define  IPPROTO_DCCP 134 
#define  IPPROTO_ESP 133 
#define  IPPROTO_ICMP 132 
#define  IPPROTO_SCTP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int IP_MF ; 
 int IP_OFFSET ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int htons (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (void*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,void**) ; 
 void** skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static void
_decode_session4(struct sk_buff *skb, struct flowi *fl, int reverse)
{
	struct iphdr *iph = ip_hdr(skb);
	u8 *xprth = skb_network_header(skb) + iph->ihl * 4;

	memset(fl, 0, sizeof(struct flowi));
	if (!(iph->frag_off & htons(IP_MF | IP_OFFSET))) {
		switch (iph->protocol) {
		case IPPROTO_UDP:
		case IPPROTO_UDPLITE:
		case IPPROTO_TCP:
		case IPPROTO_SCTP:
		case IPPROTO_DCCP:
			if (xprth + 4 < skb->data ||
			    pskb_may_pull(skb, xprth + 4 - skb->data)) {
				__be16 *ports = (__be16 *)xprth;

				fl->fl_ip_sport = ports[!!reverse];
				fl->fl_ip_dport = ports[!reverse];
			}
			break;

		case IPPROTO_ICMP:
			if (pskb_may_pull(skb, xprth + 2 - skb->data)) {
				u8 *icmp = xprth;

				fl->fl_icmp_type = icmp[0];
				fl->fl_icmp_code = icmp[1];
			}
			break;

		case IPPROTO_ESP:
			if (pskb_may_pull(skb, xprth + 4 - skb->data)) {
				__be32 *ehdr = (__be32 *)xprth;

				fl->fl_ipsec_spi = ehdr[0];
			}
			break;

		case IPPROTO_AH:
			if (pskb_may_pull(skb, xprth + 8 - skb->data)) {
				__be32 *ah_hdr = (__be32*)xprth;

				fl->fl_ipsec_spi = ah_hdr[1];
			}
			break;

		case IPPROTO_COMP:
			if (pskb_may_pull(skb, xprth + 4 - skb->data)) {
				__be16 *ipcomp_hdr = (__be16 *)xprth;

				fl->fl_ipsec_spi = htonl(ntohs(ipcomp_hdr[1]));
			}
			break;
		default:
			fl->fl_ipsec_spi = 0;
			break;
		}
	}
	fl->proto = iph->protocol;
	fl->fl4_dst = reverse ? iph->saddr : iph->daddr;
	fl->fl4_src = reverse ? iph->daddr : iph->saddr;
	fl->fl4_tos = iph->tos;
}