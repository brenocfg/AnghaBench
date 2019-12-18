#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct TYPE_14__ {int /*<<< orphan*/  port; } ;
struct TYPE_15__ {TYPE_6__ dccp; } ;
struct TYPE_13__ {int /*<<< orphan*/  ip; } ;
struct TYPE_16__ {TYPE_7__ u; TYPE_5__ u3; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_2__ dccp; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; } ;
struct TYPE_12__ {TYPE_3__ u; TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_8__ dst; TYPE_4__ src; } ;
struct iphdr {int ihl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_checksum; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IP_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
dccp_manip_pkt(struct sk_buff *skb,
	       unsigned int iphdroff,
	       const struct nf_conntrack_tuple *tuple,
	       enum nf_nat_manip_type maniptype)
{
	const struct iphdr *iph = (const void *)(skb->data + iphdroff);
	struct dccp_hdr *hdr;
	unsigned int hdroff = iphdroff + iph->ihl * 4;
	__be32 oldip, newip;
	__be16 *portptr, oldport, newport;
	int hdrsize = 8; /* DCCP connection tracking guarantees this much */

	if (skb->len >= hdroff + sizeof(struct dccp_hdr))
		hdrsize = sizeof(struct dccp_hdr);

	if (!skb_make_writable(skb, hdroff + hdrsize))
		return false;

	iph = (struct iphdr *)(skb->data + iphdroff);
	hdr = (struct dccp_hdr *)(skb->data + hdroff);

	if (maniptype == IP_NAT_MANIP_SRC) {
		oldip = iph->saddr;
		newip = tuple->src.u3.ip;
		newport = tuple->src.u.dccp.port;
		portptr = &hdr->dccph_sport;
	} else {
		oldip = iph->daddr;
		newip = tuple->dst.u3.ip;
		newport = tuple->dst.u.dccp.port;
		portptr = &hdr->dccph_dport;
	}

	oldport = *portptr;
	*portptr = newport;

	if (hdrsize < sizeof(*hdr))
		return true;

	inet_proto_csum_replace4(&hdr->dccph_checksum, skb, oldip, newip, 1);
	inet_proto_csum_replace2(&hdr->dccph_checksum, skb, oldport, newport,
				 0);
	return true;
}