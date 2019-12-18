#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct rtentry {int rt_flags; TYPE_1__* rt_ifa; int /*<<< orphan*/  rt_gateway; } ;
struct rt_addrinfo {struct sockaddr** rti_info; } ;
struct ifnet {unsigned int if_index; } ;
struct ifaddr {int /*<<< orphan*/  ifa_addr; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int sa_len; } ;
struct TYPE_5__ {short rts_dynamic; short rts_newgateway; int /*<<< orphan*/  rts_badredirect; } ;
struct TYPE_4__ {struct sockaddr* ifa_addr; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 unsigned int IFSCOPE_NONE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  ROUTE_ENTRY_REFRESH ; 
 size_t RTAX_AUTHOR ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_NETMASK ; 
 int RTF_CLONING ; 
 int RTF_DONE ; 
 int RTF_DYNAMIC ; 
 int RTF_GATEWAY ; 
 int RTF_HOST ; 
 int RTF_MODIFIED ; 
 int RTF_PRCLONING ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  RTM_REDIRECT ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_NOTHELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  equal (struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct ifaddr* ifa_ifwithaddr (struct sockaddr*) ; 
 struct ifaddr* ifa_ifwithnet_scoped (struct sockaddr*,unsigned int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  route_event_enqueue_nwk_wq_entry (struct rtentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  routegenid_inet6_update () ; 
 int /*<<< orphan*/  routegenid_inet_update () ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 TYPE_3__* rt_mask (struct rtentry*) ; 
 int /*<<< orphan*/  rt_missmsg (int /*<<< orphan*/ ,struct rt_addrinfo*,int,int) ; 
 int rt_setgate (struct rtentry*,int /*<<< orphan*/ ,struct sockaddr*) ; 
 struct rtentry* rtalloc1_scoped_locked (struct sockaddr*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtentry*) ; 
 int rtrequest_scoped_locked (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,struct sockaddr*,int,int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_2__ rtstat ; 
 struct sockaddr* sa_copy (struct sockaddr*,struct sockaddr_storage*,unsigned int*) ; 

void
rtredirect(struct ifnet *ifp, struct sockaddr *dst, struct sockaddr *gateway,
    struct sockaddr *netmask, int flags, struct sockaddr *src,
    struct rtentry **rtp)
{
	struct rtentry *rt = NULL;
	int error = 0;
	short *stat = 0;
	struct rt_addrinfo info;
	struct ifaddr *ifa = NULL;
	unsigned int ifscope = (ifp != NULL) ? ifp->if_index : IFSCOPE_NONE;
	struct sockaddr_storage ss;
	int af = src->sa_family;

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_NOTOWNED);
	lck_mtx_lock(rnh_lock);

	/*
	 * Transform src into the internal routing table form for
	 * comparison against rt_gateway below.
	 */
#if INET6
	if ((af == AF_INET) || (af == AF_INET6))
#else
	if (af == AF_INET)
#endif /* !INET6 */
		src = sa_copy(src, &ss, &ifscope);

	/*
	 * Verify the gateway is directly reachable; if scoped routing
	 * is enabled, verify that it is reachable from the interface
	 * where the ICMP redirect arrived on.
	 */
	if ((ifa = ifa_ifwithnet_scoped(gateway, ifscope)) == NULL) {
		error = ENETUNREACH;
		goto out;
	}

	/* Lookup route to the destination (from the original IP header) */
	rt = rtalloc1_scoped_locked(dst, 0, RTF_CLONING|RTF_PRCLONING, ifscope);
	if (rt != NULL)
		RT_LOCK(rt);

	/*
	 * If the redirect isn't from our current router for this dst,
	 * it's either old or wrong.  If it redirects us to ourselves,
	 * we have a routing loop, perhaps as a result of an interface
	 * going down recently.  Holding rnh_lock here prevents the
	 * possibility of rt_ifa/ifa's ifa_addr from changing (e.g.
	 * in_ifinit), so okay to access ifa_addr without locking.
	 */
	if (!(flags & RTF_DONE) && rt != NULL &&
	    (!equal(src, rt->rt_gateway) || !equal(rt->rt_ifa->ifa_addr,
	    ifa->ifa_addr))) {
		error = EINVAL;
	} else {
		IFA_REMREF(ifa);
		if ((ifa = ifa_ifwithaddr(gateway))) {
			IFA_REMREF(ifa);
			ifa = NULL;
			error = EHOSTUNREACH;
		}
	}

	if (ifa) {
		IFA_REMREF(ifa);
		ifa = NULL;
	}

	if (error) {
		if (rt != NULL)
			RT_UNLOCK(rt);
		goto done;
	}

	/*
	 * Create a new entry if we just got back a wildcard entry
	 * or the the lookup failed.  This is necessary for hosts
	 * which use routing redirects generated by smart gateways
	 * to dynamically build the routing tables.
	 */
	if ((rt == NULL) || (rt_mask(rt) != NULL && rt_mask(rt)->sa_len < 2))
		goto create;
	/*
	 * Don't listen to the redirect if it's
	 * for a route to an interface.
	 */
	RT_LOCK_ASSERT_HELD(rt);
	if (rt->rt_flags & RTF_GATEWAY) {
		if (((rt->rt_flags & RTF_HOST) == 0) && (flags & RTF_HOST)) {
			/*
			 * Changing from route to net => route to host.
			 * Create new route, rather than smashing route
			 * to net; similar to cloned routes, the newly
			 * created host route is scoped as well.
			 */
create:
			if (rt != NULL)
				RT_UNLOCK(rt);
			flags |=  RTF_GATEWAY | RTF_DYNAMIC;
			error = rtrequest_scoped_locked(RTM_ADD, dst,
			    gateway, netmask, flags, NULL, ifscope);
			stat = &rtstat.rts_dynamic;
		} else {
			/*
			 * Smash the current notion of the gateway to
			 * this destination.  Should check about netmask!!!
			 */
			rt->rt_flags |= RTF_MODIFIED;
			flags |= RTF_MODIFIED;
			stat = &rtstat.rts_newgateway;
			/*
			 * add the key and gateway (in one malloc'd chunk).
			 */
			error = rt_setgate(rt, rt_key(rt), gateway);
			RT_UNLOCK(rt);
		}
	} else {
		RT_UNLOCK(rt);
		error = EHOSTUNREACH;
	}
done:
	if (rt != NULL) {
		RT_LOCK_ASSERT_NOTHELD(rt);
		if (!error) {
			/* Enqueue event to refresh flow route entries */
			route_event_enqueue_nwk_wq_entry(rt, NULL, ROUTE_ENTRY_REFRESH, NULL, FALSE);
			if (rtp)
				*rtp = rt;
			else
				rtfree_locked(rt);
		}
		else
			rtfree_locked(rt);
	}
out:
	if (error) {
		rtstat.rts_badredirect++;
	} else {
		if (stat != NULL)
			(*stat)++;

		if (af == AF_INET)
			routegenid_inet_update();
#if INET6
		else if (af == AF_INET6)
			routegenid_inet6_update();
#endif /* INET6 */
	}
	lck_mtx_unlock(rnh_lock);
	bzero((caddr_t)&info, sizeof(info));
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_GATEWAY] = gateway;
	info.rti_info[RTAX_NETMASK] = netmask;
	info.rti_info[RTAX_AUTHOR] = src;
	rt_missmsg(RTM_REDIRECT, &info, flags, error);
}