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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;
struct icmphdr {scalar_t__ type; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _ih ;

/* Variables and functions */
 scalar_t__ ICMP_DEST_UNREACH ; 
 scalar_t__ ICMP_PARAMETERPROB ; 
 scalar_t__ ICMP_REDIRECT ; 
 scalar_t__ ICMP_SOURCE_QUENCH ; 
 scalar_t__ ICMP_TIME_EXCEEDED ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 scalar_t__ LOG_INVALID (struct net*,int /*<<< orphan*/ ) ; 
 int NF_ACCEPT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 scalar_t__ NR_ICMP_TYPES ; 
 int /*<<< orphan*/  PF_INET ; 
 int icmp_error_message (struct net*,struct sk_buff*,int*,unsigned int) ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 scalar_t__ nf_ip_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_log_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct icmphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct icmphdr*) ; 

__attribute__((used)) static int
icmp_error(struct net *net, struct sk_buff *skb, unsigned int dataoff,
	   enum ip_conntrack_info *ctinfo, u_int8_t pf, unsigned int hooknum)
{
	const struct icmphdr *icmph;
	struct icmphdr _ih;

	/* Not enough header? */
	icmph = skb_header_pointer(skb, ip_hdrlen(skb), sizeof(_ih), &_ih);
	if (icmph == NULL) {
		if (LOG_INVALID(net, IPPROTO_ICMP))
			nf_log_packet(PF_INET, 0, skb, NULL, NULL, NULL,
				      "nf_ct_icmp: short packet ");
		return -NF_ACCEPT;
	}

	/* See ip_conntrack_proto_tcp.c */
	if (net->ct.sysctl_checksum && hooknum == NF_INET_PRE_ROUTING &&
	    nf_ip_checksum(skb, hooknum, dataoff, 0)) {
		if (LOG_INVALID(net, IPPROTO_ICMP))
			nf_log_packet(PF_INET, 0, skb, NULL, NULL, NULL,
				      "nf_ct_icmp: bad HW ICMP checksum ");
		return -NF_ACCEPT;
	}

	/*
	 *	18 is the highest 'known' ICMP type. Anything else is a mystery
	 *
	 *	RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently
	 *		  discarded.
	 */
	if (icmph->type > NR_ICMP_TYPES) {
		if (LOG_INVALID(net, IPPROTO_ICMP))
			nf_log_packet(PF_INET, 0, skb, NULL, NULL, NULL,
				      "nf_ct_icmp: invalid ICMP type ");
		return -NF_ACCEPT;
	}

	/* Need to track icmp error message? */
	if (icmph->type != ICMP_DEST_UNREACH
	    && icmph->type != ICMP_SOURCE_QUENCH
	    && icmph->type != ICMP_TIME_EXCEEDED
	    && icmph->type != ICMP_PARAMETERPROB
	    && icmph->type != ICMP_REDIRECT)
		return NF_ACCEPT;

	return icmp_error_message(net, skb, ctinfo, hooknum);
}