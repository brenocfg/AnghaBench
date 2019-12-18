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
struct ip6_tnl_parm {int flags; scalar_t__ link; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;
struct ip6_tnl {struct ip6_tnl_parm parms; } ;

/* Variables and functions */
 int IP6_TNL_F_CAP_RCV ; 
 int IP6_TNL_F_CAP_XMIT ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_LOOPBACK ; 
 int IPV6_ADDR_MULTICAST ; 
 int IPV6_ADDR_UNICAST ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip6_tnl_set_cap(struct ip6_tnl *t)
{
	struct ip6_tnl_parm *p = &t->parms;
	int ltype = ipv6_addr_type(&p->laddr);
	int rtype = ipv6_addr_type(&p->raddr);

	p->flags &= ~(IP6_TNL_F_CAP_XMIT|IP6_TNL_F_CAP_RCV);

	if (ltype & (IPV6_ADDR_UNICAST|IPV6_ADDR_MULTICAST) &&
	    rtype & (IPV6_ADDR_UNICAST|IPV6_ADDR_MULTICAST) &&
	    !((ltype|rtype) & IPV6_ADDR_LOOPBACK) &&
	    (!((ltype|rtype) & IPV6_ADDR_LINKLOCAL) || p->link)) {
		if (ltype&IPV6_ADDR_UNICAST)
			p->flags |= IP6_TNL_F_CAP_XMIT;
		if (rtype&IPV6_ADDR_UNICAST)
			p->flags |= IP6_TNL_F_CAP_RCV;
	}
}