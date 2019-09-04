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
typedef  int /*<<< orphan*/  u_int32_t ;
struct rtentry {int dummy; } ;
struct in_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct rtentry* ifnet_cached_rtlookup_inet (struct ifnet*,struct in_addr) ; 
 scalar_t__ nstat_collect ; 
 int /*<<< orphan*/  nstat_route_rx (struct rtentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 

__attribute__((used)) static void
ip_input_update_nstat(struct ifnet *ifp, struct in_addr src_ip,
    u_int32_t packets, u_int32_t bytes)
{
	if (nstat_collect) {
		struct rtentry *rt = ifnet_cached_rtlookup_inet(ifp,
		    src_ip);
		if (rt != NULL) {
			nstat_route_rx(rt, packets, bytes, 0);
			rtfree(rt);
		}
	}
}