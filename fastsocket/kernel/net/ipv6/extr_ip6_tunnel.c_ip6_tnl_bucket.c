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
struct in6_addr {int dummy; } ;
struct ip6_tnl_parm {struct in6_addr laddr; struct in6_addr raddr; } ;
struct ip6_tnl_net {struct ip6_tnl*** tnls; } ;
struct ip6_tnl {int dummy; } ;

/* Variables and functions */
 unsigned int HASH (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr*) ; 

__attribute__((used)) static struct ip6_tnl **
ip6_tnl_bucket(struct ip6_tnl_net *ip6n, struct ip6_tnl_parm *p)
{
	struct in6_addr *remote = &p->raddr;
	struct in6_addr *local = &p->laddr;
	unsigned h = 0;
	int prio = 0;

	if (!ipv6_addr_any(remote) || !ipv6_addr_any(local)) {
		prio = 1;
		h = HASH(remote) ^ HASH(local);
	}
	return &ip6n->tnls[prio][h];
}