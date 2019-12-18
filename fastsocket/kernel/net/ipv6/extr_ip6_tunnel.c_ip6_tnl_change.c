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
struct ip6_tnl_parm {int /*<<< orphan*/  proto; int /*<<< orphan*/  link; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  link; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_tnl_dst_reset (struct ip6_tnl*) ; 
 int /*<<< orphan*/  ip6_tnl_link_config (struct ip6_tnl*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ip6_tnl_change(struct ip6_tnl *t, struct ip6_tnl_parm *p)
{
	ipv6_addr_copy(&t->parms.laddr, &p->laddr);
	ipv6_addr_copy(&t->parms.raddr, &p->raddr);
	t->parms.flags = p->flags;
	t->parms.hop_limit = p->hop_limit;
	t->parms.encap_limit = p->encap_limit;
	t->parms.flowinfo = p->flowinfo;
	t->parms.link = p->link;
	t->parms.proto = p->proto;
	ip6_tnl_dst_reset(t);
	ip6_tnl_link_config(t);
	return 0;
}