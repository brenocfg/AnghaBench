#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int s_addr; } ;
struct TYPE_7__ {int s_addr; } ;
struct TYPE_6__ {int s_addr; } ;
struct TYPE_5__ {int s_addr; } ;
struct ipt_ip {int invflags; int flags; int /*<<< orphan*/  proto; int /*<<< orphan*/  outiface; int /*<<< orphan*/  outiface_mask; int /*<<< orphan*/  iniface; int /*<<< orphan*/  iniface_mask; TYPE_4__ dst; TYPE_3__ dmsk; TYPE_2__ src; TYPE_1__ smsk; } ;
struct iphdr {int saddr; int daddr; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 scalar_t__ FWINV (int,int) ; 
 int IPT_F_FRAG ; 
 int IPT_INV_DSTIP ; 
 int IPT_INV_FRAG ; 
 int IPT_INV_PROTO ; 
 int IPT_INV_SRCIP ; 
 int IPT_INV_VIA_IN ; 
 int IPT_INV_VIA_OUT ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 unsigned long ifname_compare_aligned (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
ip_packet_match(const struct iphdr *ip,
		const char *indev,
		const char *outdev,
		const struct ipt_ip *ipinfo,
		int isfrag)
{
	unsigned long ret;

#define FWINV(bool, invflg) ((bool) ^ !!(ipinfo->invflags & (invflg)))

	if (FWINV((ip->saddr&ipinfo->smsk.s_addr) != ipinfo->src.s_addr,
		  IPT_INV_SRCIP)
	    || FWINV((ip->daddr&ipinfo->dmsk.s_addr) != ipinfo->dst.s_addr,
		     IPT_INV_DSTIP)) {
		dprintf("Source or dest mismatch.\n");

		dprintf("SRC: %pI4. Mask: %pI4. Target: %pI4.%s\n",
			&ip->saddr, &ipinfo->smsk.s_addr, &ipinfo->src.s_addr,
			ipinfo->invflags & IPT_INV_SRCIP ? " (INV)" : "");
		dprintf("DST: %pI4 Mask: %pI4 Target: %pI4.%s\n",
			&ip->daddr, &ipinfo->dmsk.s_addr, &ipinfo->dst.s_addr,
			ipinfo->invflags & IPT_INV_DSTIP ? " (INV)" : "");
		return false;
	}

	ret = ifname_compare_aligned(indev, ipinfo->iniface, ipinfo->iniface_mask);

	if (FWINV(ret != 0, IPT_INV_VIA_IN)) {
		dprintf("VIA in mismatch (%s vs %s).%s\n",
			indev, ipinfo->iniface,
			ipinfo->invflags&IPT_INV_VIA_IN ?" (INV)":"");
		return false;
	}

	ret = ifname_compare_aligned(outdev, ipinfo->outiface, ipinfo->outiface_mask);

	if (FWINV(ret != 0, IPT_INV_VIA_OUT)) {
		dprintf("VIA out mismatch (%s vs %s).%s\n",
			outdev, ipinfo->outiface,
			ipinfo->invflags&IPT_INV_VIA_OUT ?" (INV)":"");
		return false;
	}

	/* Check specific protocol */
	if (ipinfo->proto
	    && FWINV(ip->protocol != ipinfo->proto, IPT_INV_PROTO)) {
		dprintf("Packet protocol %hi does not match %hi.%s\n",
			ip->protocol, ipinfo->proto,
			ipinfo->invflags&IPT_INV_PROTO ? " (INV)":"");
		return false;
	}

	/* If we have a fragment rule but the packet is not a fragment
	 * then we return zero */
	if (FWINV((ipinfo->flags&IPT_F_FRAG) && !isfrag, IPT_INV_FRAG)) {
		dprintf("Fragment rule but not fragment.%s\n",
			ipinfo->invflags & IPT_INV_FRAG ? " (INV)" : "");
		return false;
	}

	return true;
}