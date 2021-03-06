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
struct udphdr {int /*<<< orphan*/  check; int /*<<< orphan*/  len; } ;
struct sk_buff {unsigned int len; } ;
struct TYPE_2__ {scalar_t__ sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _hdr ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IPPROTO_UDPLITE ; 
 scalar_t__ LOG_INVALID (struct net*,int /*<<< orphan*/ ) ; 
 int NF_ACCEPT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 scalar_t__ nf_checksum_partial (struct sk_buff*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_log_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct udphdr*) ; 

__attribute__((used)) static int udplite_error(struct net *net,
			 struct sk_buff *skb,
			 unsigned int dataoff,
			 enum ip_conntrack_info *ctinfo,
			 u_int8_t pf,
			 unsigned int hooknum)
{
	unsigned int udplen = skb->len - dataoff;
	const struct udphdr *hdr;
	struct udphdr _hdr;
	unsigned int cscov;

	/* Header is too small? */
	hdr = skb_header_pointer(skb, dataoff, sizeof(_hdr), &_hdr);
	if (hdr == NULL) {
		if (LOG_INVALID(net, IPPROTO_UDPLITE))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				      "nf_ct_udplite: short packet ");
		return -NF_ACCEPT;
	}

	cscov = ntohs(hdr->len);
	if (cscov == 0)
		cscov = udplen;
	else if (cscov < sizeof(*hdr) || cscov > udplen) {
		if (LOG_INVALID(net, IPPROTO_UDPLITE))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				"nf_ct_udplite: invalid checksum coverage ");
		return -NF_ACCEPT;
	}

	/* UDPLITE mandates checksums */
	if (!hdr->check) {
		if (LOG_INVALID(net, IPPROTO_UDPLITE))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				      "nf_ct_udplite: checksum missing ");
		return -NF_ACCEPT;
	}

	/* Checksum invalid? Ignore. */
	if (net->ct.sysctl_checksum && hooknum == NF_INET_PRE_ROUTING &&
	    nf_checksum_partial(skb, hooknum, dataoff, cscov, IPPROTO_UDP,
	    			pf)) {
		if (LOG_INVALID(net, IPPROTO_UDPLITE))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				      "nf_ct_udplite: bad UDPLite checksum ");
		return -NF_ACCEPT;
	}

	return NF_ACCEPT;
}