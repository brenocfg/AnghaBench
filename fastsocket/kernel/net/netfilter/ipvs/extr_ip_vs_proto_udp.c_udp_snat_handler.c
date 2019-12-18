#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udphdr {scalar_t__ check; int /*<<< orphan*/  source; } ;
struct sk_buff {unsigned int len; scalar_t__ ip_summed; int /*<<< orphan*/  csum; } ;
struct ipv6hdr {int dummy; } ;
struct ip_vs_protocol {int /*<<< orphan*/  name; int /*<<< orphan*/  (* csum_check ) (scalar_t__,struct sk_buff*,struct ip_vs_protocol*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct ip_vs_conn {scalar_t__ af; int /*<<< orphan*/  protocol; TYPE_1__ caddr; TYPE_2__ vaddr; int /*<<< orphan*/  vport; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/ * app; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ CHECKSUM_COMPLETE ; 
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 unsigned int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_vs_app_pkt_out (struct ip_vs_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,struct sk_buff*,struct ip_vs_protocol*) ; 
 int /*<<< orphan*/  udp_fast_csum_update (scalar_t__,struct udphdr*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_partial_csum_update (scalar_t__,struct udphdr*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udp_snat_handler(struct sk_buff *skb,
		 struct ip_vs_protocol *pp, struct ip_vs_conn *cp)
{
	struct udphdr *udph;
	unsigned int udphoff;
	int oldlen;

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6)
		udphoff = sizeof(struct ipv6hdr);
	else
#endif
		udphoff = ip_hdrlen(skb);
	oldlen = skb->len - udphoff;

	/* csum_check requires unshared skb */
	if (!skb_make_writable(skb, udphoff+sizeof(*udph)))
		return 0;

	if (unlikely(cp->app != NULL)) {
		/* Some checks before mangling */
		if (pp->csum_check && !pp->csum_check(cp->af, skb, pp))
			return 0;

		/*
		 *	Call application helper if needed
		 */
		if (!ip_vs_app_pkt_out(cp, skb))
			return 0;
	}

	udph = (void *)skb_network_header(skb) + udphoff;
	udph->source = cp->vport;

	/*
	 *	Adjust UDP checksums
	 */
	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		udp_partial_csum_update(cp->af, udph, &cp->daddr, &cp->vaddr,
					htons(oldlen),
					htons(skb->len - udphoff));
	} else if (!cp->app && (udph->check != 0)) {
		/* Only port and addr are changed, do fast csum update */
		udp_fast_csum_update(cp->af, udph, &cp->daddr, &cp->vaddr,
				     cp->dport, cp->vport);
		if (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->ip_summed = CHECKSUM_NONE;
	} else {
		/* full checksum calculation */
		udph->check = 0;
		skb->csum = skb_checksum(skb, udphoff, skb->len - udphoff, 0);
#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			udph->check = csum_ipv6_magic(&cp->vaddr.in6,
						      &cp->caddr.in6,
						      skb->len - udphoff,
						      cp->protocol, skb->csum);
		else
#endif
			udph->check = csum_tcpudp_magic(cp->vaddr.ip,
							cp->caddr.ip,
							skb->len - udphoff,
							cp->protocol,
							skb->csum);
		if (udph->check == 0)
			udph->check = CSUM_MANGLED_0;
		IP_VS_DBG(11, "O-pkt: %s O-csum=%d (+%zd)\n",
			  pp->name, udph->check,
			  (char*)&(udph->check) - (char*)udph);
	}
	return 1;
}