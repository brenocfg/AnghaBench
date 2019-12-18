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
typedef  scalar_t__ u32 ;
struct xfrm_dst {scalar_t__ route_mtu_cached; int /*<<< orphan*/  route; scalar_t__ child_mtu_cached; } ;
struct dst_entry {scalar_t__* metrics; int /*<<< orphan*/  xfrm; int /*<<< orphan*/  child; struct dst_entry* next; } ;

/* Variables and functions */
 int RTAX_MTU ; 
 scalar_t__ dst_mtu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_state_mtu (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xfrm_init_pmtu(struct dst_entry *dst)
{
	do {
		struct xfrm_dst *xdst = (struct xfrm_dst *)dst;
		u32 pmtu, route_mtu_cached;

		pmtu = dst_mtu(dst->child);
		xdst->child_mtu_cached = pmtu;

		pmtu = xfrm_state_mtu(dst->xfrm, pmtu);

		route_mtu_cached = dst_mtu(xdst->route);
		xdst->route_mtu_cached = route_mtu_cached;

		if (pmtu > route_mtu_cached)
			pmtu = route_mtu_cached;

		dst->metrics[RTAX_MTU-1] = pmtu;
	} while ((dst = dst->next));
}