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
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ip6_tnl_parm {struct in6_addr laddr; struct in6_addr raddr; } ;
struct ip6_tnl_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;
struct ip6_tnl {TYPE_1__ parms; struct ip6_tnl* next; } ;

/* Variables and functions */
 struct ip6_tnl** ip6_tnl_bucket (struct ip6_tnl_net*,struct ip6_tnl_parm*) ; 
 struct ip6_tnl* ip6_tnl_create (struct net*,struct ip6_tnl_parm*) ; 
 int /*<<< orphan*/  ip6_tnl_net_id ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,int /*<<< orphan*/ *) ; 
 struct ip6_tnl_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ip6_tnl *ip6_tnl_locate(struct net *net,
		struct ip6_tnl_parm *p, int create)
{
	struct in6_addr *remote = &p->raddr;
	struct in6_addr *local = &p->laddr;
	struct ip6_tnl *t;
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	for (t = *ip6_tnl_bucket(ip6n, p); t; t = t->next) {
		if (ipv6_addr_equal(local, &t->parms.laddr) &&
		    ipv6_addr_equal(remote, &t->parms.raddr))
			return t;
	}
	if (!create)
		return NULL;
	return ip6_tnl_create(net, p);
}