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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_IPV6 ; 
 int /*<<< orphan*/  ifnet_llreach_set_reachable (struct ifnet*,int /*<<< orphan*/ ,void*,unsigned int) ; 
 scalar_t__ nd6_llreach_base ; 

void
nd6_llreach_set_reachable(struct ifnet *ifp, void *addr, unsigned int alen)
{
	/* Nothing more to do if it's disabled */
	if (nd6_llreach_base == 0)
		return;

	ifnet_llreach_set_reachable(ifp, ETHERTYPE_IPV6, addr, alen);
}