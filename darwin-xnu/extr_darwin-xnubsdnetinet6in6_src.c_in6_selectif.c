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
struct sockaddr_in6 {int dummy; } ;
struct rtentry {int rt_flags; TYPE_1__* rt_ifa; } ;
struct route_in6 {struct rtentry* ro_rt; } ;
struct ip6_pktopts {int dummy; } ;
struct ip6_out_args {int dummy; } ;
struct ip6_moptions {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  sro ;
struct TYPE_2__ {struct ifnet* ifa_ifp; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  ROUTE_RELEASE (struct route_in6*) ; 
 int RTF_BLACKHOLE ; 
 int RTF_HOST ; 
 int RTF_REJECT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct route_in6*,int) ; 
 int /*<<< orphan*/  ifnet_reference (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 int selectroute (int /*<<< orphan*/ *,struct sockaddr_in6*,struct ip6_pktopts*,struct ip6_moptions*,int /*<<< orphan*/ *,struct route_in6*,struct ifnet**,struct rtentry**,int /*<<< orphan*/ ,int,struct ip6_out_args*) ; 

int
in6_selectif(struct sockaddr_in6 *dstsock, struct ip6_pktopts *opts,
    struct ip6_moptions *mopts, struct route_in6 *ro,
    struct ip6_out_args *ip6oa, struct ifnet **retifp)
{
	int err = 0;
	struct route_in6 sro;
	struct rtentry *rt = NULL;

	if (ro == NULL) {
		bzero(&sro, sizeof (sro));
		ro = &sro;
	}

	if ((err = selectroute(NULL, dstsock, opts, mopts, NULL, ro, retifp,
	    &rt, 0, 1, ip6oa)) != 0)
		goto done;

	/*
	 * do not use a rejected or black hole route.
	 * XXX: this check should be done in the L2 output routine.
	 * However, if we skipped this check here, we'd see the following
	 * scenario:
	 * - install a rejected route for a scoped address prefix
	 *   (like fe80::/10)
	 * - send a packet to a destination that matches the scoped prefix,
	 *   with ambiguity about the scope zone.
	 * - pick the outgoing interface from the route, and disambiguate the
	 *   scope zone with the interface.
	 * - ip6_output() would try to get another route with the "new"
	 *   destination, which may be valid.
	 * - we'd see no error on output.
	 * Although this may not be very harmful, it should still be confusing.
	 * We thus reject the case here.
	 */
	if (rt && (rt->rt_flags & (RTF_REJECT | RTF_BLACKHOLE))) {
		err = ((rt->rt_flags & RTF_HOST) ? EHOSTUNREACH : ENETUNREACH);
		goto done;
	}

	/*
	 * Adjust the "outgoing" interface.  If we're going to loop the packet
	 * back to ourselves, the ifp would be the loopback interface.
	 * However, we'd rather know the interface associated to the
	 * destination address (which should probably be one of our own
	 * addresses.)
	 */
	if (rt != NULL && rt->rt_ifa != NULL && rt->rt_ifa->ifa_ifp != NULL &&
	    retifp != NULL) {
		ifnet_reference(rt->rt_ifa->ifa_ifp);
		if (*retifp != NULL)
			ifnet_release(*retifp);
		*retifp = rt->rt_ifa->ifa_ifp;
	}

done:
	if (ro == &sro) {
		VERIFY(rt == NULL || rt == ro->ro_rt);
		ROUTE_RELEASE(ro);
	}

	/*
	 * retifp might point to a valid ifp with a reference held;
	 * caller is responsible for releasing it if non-NULL.
	 */
	return (err);
}