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
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip6t_ip6 {int invflags; int flags; int proto; int /*<<< orphan*/  outiface; int /*<<< orphan*/  outiface_mask; int /*<<< orphan*/  iniface; int /*<<< orphan*/  iniface_mask; int /*<<< orphan*/  dst; int /*<<< orphan*/  dmsk; int /*<<< orphan*/  src; int /*<<< orphan*/  smsk; } ;

/* Variables and functions */
 scalar_t__ FWINV (int,int) ; 
 int IP6T_F_PROTO ; 
 int IP6T_INV_DSTIP ; 
 int IP6T_INV_PROTO ; 
 int IP6T_INV_SRCIP ; 
 int IP6T_INV_VIA_IN ; 
 int IP6T_INV_VIA_OUT ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 unsigned long ifname_compare_aligned (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipv6_find_hdr (struct sk_buff const*,unsigned int*,int,unsigned short*,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 
 int ipv6_masked_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
ip6_packet_match(const struct sk_buff *skb,
		 const char *indev,
		 const char *outdev,
		 const struct ip6t_ip6 *ip6info,
		 unsigned int *protoff,
		 int *fragoff, bool *hotdrop)
{
	unsigned long ret;
	const struct ipv6hdr *ipv6 = ipv6_hdr(skb);

#define FWINV(bool, invflg) ((bool) ^ !!(ip6info->invflags & (invflg)))

	if (FWINV(ipv6_masked_addr_cmp(&ipv6->saddr, &ip6info->smsk,
				       &ip6info->src), IP6T_INV_SRCIP)
	    || FWINV(ipv6_masked_addr_cmp(&ipv6->daddr, &ip6info->dmsk,
					  &ip6info->dst), IP6T_INV_DSTIP)) {
		dprintf("Source or dest mismatch.\n");
/*
		dprintf("SRC: %u. Mask: %u. Target: %u.%s\n", ip->saddr,
			ipinfo->smsk.s_addr, ipinfo->src.s_addr,
			ipinfo->invflags & IP6T_INV_SRCIP ? " (INV)" : "");
		dprintf("DST: %u. Mask: %u. Target: %u.%s\n", ip->daddr,
			ipinfo->dmsk.s_addr, ipinfo->dst.s_addr,
			ipinfo->invflags & IP6T_INV_DSTIP ? " (INV)" : "");*/
		return false;
	}

	ret = ifname_compare_aligned(indev, ip6info->iniface, ip6info->iniface_mask);

	if (FWINV(ret != 0, IP6T_INV_VIA_IN)) {
		dprintf("VIA in mismatch (%s vs %s).%s\n",
			indev, ip6info->iniface,
			ip6info->invflags&IP6T_INV_VIA_IN ?" (INV)":"");
		return false;
	}

	ret = ifname_compare_aligned(outdev, ip6info->outiface, ip6info->outiface_mask);

	if (FWINV(ret != 0, IP6T_INV_VIA_OUT)) {
		dprintf("VIA out mismatch (%s vs %s).%s\n",
			outdev, ip6info->outiface,
			ip6info->invflags&IP6T_INV_VIA_OUT ?" (INV)":"");
		return false;
	}

/* ... might want to do something with class and flowlabel here ... */

	/* look for the desired protocol header */
	if((ip6info->flags & IP6T_F_PROTO)) {
		int protohdr;
		unsigned short _frag_off;

		protohdr = ipv6_find_hdr(skb, protoff, -1, &_frag_off, NULL);
		if (protohdr < 0) {
			if (_frag_off == 0)
				*hotdrop = true;
			return false;
		}
		*fragoff = _frag_off;

		dprintf("Packet protocol %hi ?= %s%hi.\n",
				protohdr,
				ip6info->invflags & IP6T_INV_PROTO ? "!":"",
				ip6info->proto);

		if (ip6info->proto == protohdr) {
			if(ip6info->invflags & IP6T_INV_PROTO) {
				return false;
			}
			return true;
		}

		/* We need match for the '-p all', too! */
		if ((ip6info->proto != 0) &&
			!(ip6info->invflags & IP6T_INV_PROTO))
			return false;
	}
	return true;
}