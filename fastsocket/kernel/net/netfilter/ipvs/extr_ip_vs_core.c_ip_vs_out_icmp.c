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
union nf_inet_addr {int /*<<< orphan*/  ip; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int frag_off; int ihl; scalar_t__ type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ip_vs_protocol {struct ip_vs_conn* (* conn_out_get ) (int /*<<< orphan*/ ,struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_iphdr*,unsigned int,int) ;scalar_t__ dont_defrag; } ;
struct ip_vs_iphdr {int dummy; } ;
struct ip_vs_conn {int dummy; } ;
struct icmphdr {int frag_off; int ihl; scalar_t__ type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  _icmph ;
typedef  int /*<<< orphan*/  _ciph ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ ICMP_DEST_UNREACH ; 
 scalar_t__ ICMP_SOURCE_QUENCH ; 
 scalar_t__ ICMP_TIME_EXCEEDED ; 
 int /*<<< orphan*/  IP_DEFRAG_VS_OUT ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_PKT (int,struct ip_vs_protocol*,struct sk_buff*,unsigned int,char*) ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int NF_STOLEN ; 
 int handle_response_icmp (int /*<<< orphan*/ ,struct sk_buff*,union nf_inet_addr*,int /*<<< orphan*/ ,struct ip_vs_conn*,struct ip_vs_protocol*,unsigned int,unsigned int) ; 
 int htons (int) ; 
 int /*<<< orphan*/  icmp_id (struct iphdr*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_vs_fill_iphdr (int /*<<< orphan*/ ,struct iphdr*,struct ip_vs_iphdr*) ; 
 scalar_t__ ip_vs_gather_frags (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ip_vs_protocol* ip_vs_proto_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct iphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct iphdr*) ; 
 struct ip_vs_conn* stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_iphdr*,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_vs_out_icmp(struct sk_buff *skb, int *related)
{
	struct iphdr *iph;
	struct icmphdr	_icmph, *ic;
	struct iphdr	_ciph, *cih;	/* The ip header contained within the ICMP */
	struct ip_vs_iphdr ciph;
	struct ip_vs_conn *cp;
	struct ip_vs_protocol *pp;
	unsigned int offset, ihl;
	union nf_inet_addr snet;

	*related = 1;

	/* reassemble IP fragments */
	if (ip_hdr(skb)->frag_off & htons(IP_MF | IP_OFFSET)) {
		if (ip_vs_gather_frags(skb, IP_DEFRAG_VS_OUT))
			return NF_STOLEN;
	}

	iph = ip_hdr(skb);
	offset = ihl = iph->ihl * 4;
	ic = skb_header_pointer(skb, offset, sizeof(_icmph), &_icmph);
	if (ic == NULL)
		return NF_DROP;

	IP_VS_DBG(12, "Outgoing ICMP (%d,%d) %pI4->%pI4\n",
		  ic->type, ntohs(icmp_id(ic)),
		  &iph->saddr, &iph->daddr);

	/*
	 * Work through seeing if this is for us.
	 * These checks are supposed to be in an order that means easy
	 * things are checked first to speed up processing.... however
	 * this means that some packets will manage to get a long way
	 * down this stack and then be rejected, but that's life.
	 */
	if ((ic->type != ICMP_DEST_UNREACH) &&
	    (ic->type != ICMP_SOURCE_QUENCH) &&
	    (ic->type != ICMP_TIME_EXCEEDED)) {
		*related = 0;
		return NF_ACCEPT;
	}

	/* Now find the contained IP header */
	offset += sizeof(_icmph);
	cih = skb_header_pointer(skb, offset, sizeof(_ciph), &_ciph);
	if (cih == NULL)
		return NF_ACCEPT; /* The packet looks wrong, ignore */

	pp = ip_vs_proto_get(cih->protocol);
	if (!pp)
		return NF_ACCEPT;

	/* Is the embedded protocol header present? */
	if (unlikely(cih->frag_off & htons(IP_OFFSET) &&
		     pp->dont_defrag))
		return NF_ACCEPT;

	IP_VS_DBG_PKT(11, pp, skb, offset, "Checking outgoing ICMP for");

	offset += cih->ihl * 4;

	ip_vs_fill_iphdr(AF_INET, cih, &ciph);
	/* The embedded headers contain source and dest in reverse order */
	cp = pp->conn_out_get(AF_INET, skb, pp, &ciph, offset, 1);
	if (!cp)
		return NF_ACCEPT;

	snet.ip = iph->saddr;
	return handle_response_icmp(AF_INET, skb, &snet, cih->protocol, cp,
				    pp, offset, ihl);
}