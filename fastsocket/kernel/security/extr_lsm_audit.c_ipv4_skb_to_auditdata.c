#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {int dummy; } ;
struct sctphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct iphdr {int protocol; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; TYPE_1__ v4info; } ;
struct TYPE_6__ {TYPE_2__ net; } ;
struct common_audit_data {TYPE_3__ u; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPPROTO_DCCP 131 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IP_OFFSET ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

int ipv4_skb_to_auditdata(struct sk_buff *skb,
		struct common_audit_data *ad, u8 *proto)
{
	int ret = 0;
	struct iphdr *ih;

	ih = ip_hdr(skb);
	if (ih == NULL)
		return -EINVAL;

	ad->u.net.v4info.saddr = ih->saddr;
	ad->u.net.v4info.daddr = ih->daddr;

	if (proto)
		*proto = ih->protocol;
	/* non initial fragment */
	if (ntohs(ih->frag_off) & IP_OFFSET)
		return 0;

	switch (ih->protocol) {
	case IPPROTO_TCP: {
		struct tcphdr *th = tcp_hdr(skb);
		if (th == NULL)
			break;

		ad->u.net.sport = th->source;
		ad->u.net.dport = th->dest;
		break;
	}
	case IPPROTO_UDP: {
		struct udphdr *uh = udp_hdr(skb);
		if (uh == NULL)
			break;

		ad->u.net.sport = uh->source;
		ad->u.net.dport = uh->dest;
		break;
	}
	case IPPROTO_DCCP: {
		struct dccp_hdr *dh = dccp_hdr(skb);
		if (dh == NULL)
			break;

		ad->u.net.sport = dh->dccph_sport;
		ad->u.net.dport = dh->dccph_dport;
		break;
	}
	case IPPROTO_SCTP: {
		struct sctphdr *sh = sctp_hdr(skb);
		if (sh == NULL)
			break;
		ad->u.net.sport = sh->source;
		ad->u.net.dport = sh->dest;
		break;
	}
	default:
		ret = -EINVAL;
	}
	return ret;
}