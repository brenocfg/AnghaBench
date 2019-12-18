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
struct rtentry {int rt_flags; TYPE_1__* rt_ifp; } ;
struct ifaddr {int /*<<< orphan*/  ifa_addr; } ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int RTF_HOST ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  in6_ifloop_request (int /*<<< orphan*/ ,struct ifaddr*) ; 
 struct rtentry* rtalloc1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
in6_ifaddloop(struct ifaddr *ifa)
{
	struct rtentry *rt;

	/*
	 * If there is no loopback entry, allocate one.  ifa_addr for
	 * INET6 is set once during init; no need to hold lock.
	 */
	rt = rtalloc1(ifa->ifa_addr, 0, 0);
	if (rt != NULL)
		RT_LOCK(rt);
	if (rt == NULL || (rt->rt_flags & RTF_HOST) == 0 ||
	    (rt->rt_ifp->if_flags & IFF_LOOPBACK) == 0) {
		if (rt != NULL) {
			RT_REMREF_LOCKED(rt);
			RT_UNLOCK(rt);
		}
		in6_ifloop_request(RTM_ADD, ifa);
	} else if (rt != NULL) {
		RT_REMREF_LOCKED(rt);
		RT_UNLOCK(rt);
	}
}