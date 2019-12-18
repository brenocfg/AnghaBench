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
struct ipv6hdr {int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  raddr; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 int ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
ip6_tnl_addr_conflict(struct ip6_tnl *t, struct ipv6hdr *hdr)
{
	return ipv6_addr_equal(&t->parms.raddr, &hdr->saddr);
}