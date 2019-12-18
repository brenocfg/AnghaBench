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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct TYPE_5__ {TYPE_1__ gre; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_3__ dst; } ;
struct iphdr {int ihl; } ;
struct gre_hdr_pptp {int /*<<< orphan*/  call_id; } ;
struct gre_hdr {int version; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
#define  GRE_VERSION_1701 129 
#define  GRE_VERSION_PPTP 128 
 int IP_NAT_MANIP_DST ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
gre_manip_pkt(struct sk_buff *skb, unsigned int iphdroff,
	      const struct nf_conntrack_tuple *tuple,
	      enum nf_nat_manip_type maniptype)
{
	const struct gre_hdr *greh;
	struct gre_hdr_pptp *pgreh;
	const struct iphdr *iph = (struct iphdr *)(skb->data + iphdroff);
	unsigned int hdroff = iphdroff + iph->ihl * 4;

	/* pgreh includes two optional 32bit fields which are not required
	 * to be there.  That's where the magic '8' comes from */
	if (!skb_make_writable(skb, hdroff + sizeof(*pgreh) - 8))
		return false;

	greh = (void *)skb->data + hdroff;
	pgreh = (struct gre_hdr_pptp *)greh;

	/* we only have destination manip of a packet, since 'source key'
	 * is not present in the packet itself */
	if (maniptype != IP_NAT_MANIP_DST)
		return true;
	switch (greh->version) {
	case GRE_VERSION_1701:
		/* We do not currently NAT any GREv0 packets.
		 * Try to behave like "nf_nat_proto_unknown" */
		break;
	case GRE_VERSION_PPTP:
		pr_debug("call_id -> 0x%04x\n", ntohs(tuple->dst.u.gre.key));
		pgreh->call_id = tuple->dst.u.gre.key;
		break;
	default:
		pr_debug("can't nat unknown GRE version\n");
		return false;
	}
	return true;
}