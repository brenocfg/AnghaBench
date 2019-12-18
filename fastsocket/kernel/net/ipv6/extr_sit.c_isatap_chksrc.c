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
struct sk_buff {int /*<<< orphan*/  ndisc_nodetype; } ;
struct iphdr {scalar_t__ saddr; } ;
struct ip_tunnel_prl_entry {int flags; } ;
struct ip_tunnel {int /*<<< orphan*/  dev; } ;
struct in6_addr {scalar_t__* s6_addr32; } ;
struct TYPE_2__ {struct in6_addr saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDISC_NODETYPE_DEFAULT ; 
 int /*<<< orphan*/  NDISC_NODETYPE_HOST ; 
 int /*<<< orphan*/  NDISC_NODETYPE_NODEFAULT ; 
 int PRL_DEFAULT ; 
 struct ip_tunnel_prl_entry* __ipip6_tunnel_locate_prl (struct ip_tunnel*,scalar_t__) ; 
 int /*<<< orphan*/  ipip6_lock ; 
 scalar_t__ ipv6_addr_is_isatap (struct in6_addr*) ; 
 scalar_t__ ipv6_chk_prefix (struct in6_addr*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isatap_chksrc(struct sk_buff *skb, struct iphdr *iph, struct ip_tunnel *t)
{
	struct ip_tunnel_prl_entry *p;
	int ok = 1;

	read_lock(&ipip6_lock);
	p = __ipip6_tunnel_locate_prl(t, iph->saddr);
	if (p) {
		if (p->flags & PRL_DEFAULT)
			skb->ndisc_nodetype = NDISC_NODETYPE_DEFAULT;
		else
			skb->ndisc_nodetype = NDISC_NODETYPE_NODEFAULT;
	} else {
		struct in6_addr *addr6 = &ipv6_hdr(skb)->saddr;
		if (ipv6_addr_is_isatap(addr6) &&
		    (addr6->s6_addr32[3] == iph->saddr) &&
		    ipv6_chk_prefix(addr6, t->dev))
			skb->ndisc_nodetype = NDISC_NODETYPE_HOST;
		else
			ok = 0;
	}
	read_unlock(&ipip6_lock);
	return ok;
}