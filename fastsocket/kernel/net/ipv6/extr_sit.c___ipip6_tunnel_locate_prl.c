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
struct ip_tunnel_prl_entry {scalar_t__ addr; struct ip_tunnel_prl_entry* next; } ;
struct ip_tunnel {struct ip_tunnel_prl_entry* prl; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */

__attribute__((used)) static struct ip_tunnel_prl_entry *
__ipip6_tunnel_locate_prl(struct ip_tunnel *t, __be32 addr)
{
	struct ip_tunnel_prl_entry *p = (struct ip_tunnel_prl_entry *)NULL;

	for (p = t->prl; p; p = p->next)
		if (p->addr == addr)
			break;
	return p;

}