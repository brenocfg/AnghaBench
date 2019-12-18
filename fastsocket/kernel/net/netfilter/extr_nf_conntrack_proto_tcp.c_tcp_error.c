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
typedef  size_t u_int8_t ;
struct tcphdr {int doff; } ;
struct sk_buff {unsigned int len; } ;
struct TYPE_2__ {scalar_t__ sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ LOG_INVALID (struct net*,int /*<<< orphan*/ ) ; 
 int NF_ACCEPT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 size_t TH_CWR ; 
 size_t TH_ECE ; 
 size_t TH_PUSH ; 
 scalar_t__ nf_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nf_log_packet (size_t,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct tcphdr*) ; 
 int /*<<< orphan*/ * tcp_valid_flags ; 

__attribute__((used)) static int tcp_error(struct net *net,
		     struct sk_buff *skb,
		     unsigned int dataoff,
		     enum ip_conntrack_info *ctinfo,
		     u_int8_t pf,
		     unsigned int hooknum)
{
	const struct tcphdr *th;
	struct tcphdr _tcph;
	unsigned int tcplen = skb->len - dataoff;
	u_int8_t tcpflags;

	/* Smaller that minimal TCP header? */
	th = skb_header_pointer(skb, dataoff, sizeof(_tcph), &_tcph);
	if (th == NULL) {
		if (LOG_INVALID(net, IPPROTO_TCP))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				"nf_ct_tcp: short packet ");
		return -NF_ACCEPT;
	}

	/* Not whole TCP header or malformed packet */
	if (th->doff*4 < sizeof(struct tcphdr) || tcplen < th->doff*4) {
		if (LOG_INVALID(net, IPPROTO_TCP))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				"nf_ct_tcp: truncated/malformed packet ");
		return -NF_ACCEPT;
	}

	/* Checksum invalid? Ignore.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be correct.
	 */
	/* FIXME: Source route IP option packets --RR */
	if (net->ct.sysctl_checksum && hooknum == NF_INET_PRE_ROUTING &&
	    nf_checksum(skb, hooknum, dataoff, IPPROTO_TCP, pf)) {
		if (LOG_INVALID(net, IPPROTO_TCP))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				  "nf_ct_tcp: bad TCP checksum ");
		return -NF_ACCEPT;
	}

	/* Check TCP flags. */
	tcpflags = (((u_int8_t *)th)[13] & ~(TH_ECE|TH_CWR|TH_PUSH));
	if (!tcp_valid_flags[tcpflags]) {
		if (LOG_INVALID(net, IPPROTO_TCP))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				  "nf_ct_tcp: invalid TCP flag combination ");
		return -NF_ACCEPT;
	}

	return NF_ACCEPT;
}