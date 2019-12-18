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
struct udphdr {int ihl; int protocol; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct tcphdr {int ihl; int protocol; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int ihl; int protocol; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dccp_hdr {int ihl; int protocol; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; TYPE_1__ v4info; } ;
struct TYPE_6__ {TYPE_2__ net; } ;
struct common_audit_data {TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  _udph ;
typedef  int /*<<< orphan*/  _tcph ;
typedef  int /*<<< orphan*/  _iph ;
typedef  int /*<<< orphan*/  _dccph ;

/* Variables and functions */
 int EINVAL ; 
#define  IPPROTO_DCCP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IP_OFFSET ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,int,int,struct udphdr*) ; 
 int skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static int selinux_parse_skb_ipv4(struct sk_buff *skb,
			struct common_audit_data *ad, u8 *proto)
{
	int offset, ihlen, ret = -EINVAL;
	struct iphdr _iph, *ih;

	offset = skb_network_offset(skb);
	ih = skb_header_pointer(skb, offset, sizeof(_iph), &_iph);
	if (ih == NULL)
		goto out;

	ihlen = ih->ihl * 4;
	if (ihlen < sizeof(_iph))
		goto out;

	ad->u.net.v4info.saddr = ih->saddr;
	ad->u.net.v4info.daddr = ih->daddr;
	ret = 0;

	if (proto)
		*proto = ih->protocol;

	switch (ih->protocol) {
	case IPPROTO_TCP: {
		struct tcphdr _tcph, *th;

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		offset += ihlen;
		th = skb_header_pointer(skb, offset, sizeof(_tcph), &_tcph);
		if (th == NULL)
			break;

		ad->u.net.sport = th->source;
		ad->u.net.dport = th->dest;
		break;
	}

	case IPPROTO_UDP: {
		struct udphdr _udph, *uh;

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		offset += ihlen;
		uh = skb_header_pointer(skb, offset, sizeof(_udph), &_udph);
		if (uh == NULL)
			break;

		ad->u.net.sport = uh->source;
		ad->u.net.dport = uh->dest;
		break;
	}

	case IPPROTO_DCCP: {
		struct dccp_hdr _dccph, *dh;

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		offset += ihlen;
		dh = skb_header_pointer(skb, offset, sizeof(_dccph), &_dccph);
		if (dh == NULL)
			break;

		ad->u.net.sport = dh->dccph_sport;
		ad->u.net.dport = dh->dccph_dport;
		break;
	}

	default:
		break;
	}
out:
	return ret;
}