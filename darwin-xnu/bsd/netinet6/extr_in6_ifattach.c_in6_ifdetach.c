#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr16; } ;
struct sockaddr_in6 {int sin6_len; TYPE_4__ sin6_addr; scalar_t__ sin6_family; } ;
struct sockaddr {int dummy; } ;
struct rtentry {int /*<<< orphan*/  rt_flags; struct sockaddr* rt_gateway; struct ifnet* rt_ifp; } ;
struct in6_multi_mship {int dummy; } ;
struct ifaddr {TYPE_3__* ifa_addr; struct ifnet* ifa_ifp; } ;
struct TYPE_5__ {struct in6_multi_mship* lh_first; } ;
struct in6_ifaddr {int ia_flags; struct ifaddr ia_ifa; struct in6_ifaddr* ia_next; int /*<<< orphan*/  ia_prefixmask; int /*<<< orphan*/  ia_addr; TYPE_1__ ia6_memberships; } ;
struct ifnet {int /*<<< orphan*/  if_index; int /*<<< orphan*/  if_addrlist; } ;
typedef  int /*<<< orphan*/  sin6 ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IFA_ADDREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int IFA_ROUTE ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct in6_multi_mship*,int /*<<< orphan*/ ) ; 
 scalar_t__ LLTABLE6 (struct ifnet*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  RTF_CONDEMNED ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 struct ifaddr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct ifaddr* TAILQ_NEXT (struct ifaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i6mm_chain ; 
 int /*<<< orphan*/  if_detach_ifa (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifa_list ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  in6_ifaddr_rwlock ; 
 struct in6_ifaddr* in6_ifaddrs ; 
 int /*<<< orphan*/  in6_leavegroup (struct in6_multi_mship*) ; 
 int /*<<< orphan*/  in6_purgeaddr (struct ifaddr*) ; 
 TYPE_4__ in6addr_linklocal_allnodes ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lltable_free (scalar_t__) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6_purge (struct ifnet*) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  routegenid_inet6_update () ; 
 struct sockaddr* rt_key (struct rtentry*) ; 
 struct sockaddr* rt_mask (struct rtentry*) ; 
 struct rtentry* rtalloc1 (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 
 int /*<<< orphan*/  rtrequest (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,struct rtentry**) ; 
 TYPE_2__* satosin6 (TYPE_3__**) ; 

void
in6_ifdetach(struct ifnet *ifp)
{
	struct in6_ifaddr *ia, *oia;
	struct ifaddr *ifa;
	struct rtentry *rt;
	struct sockaddr_in6 sin6;
	struct in6_multi_mship *imm;
	int unlinked;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);

	/* remove neighbor management table */
	nd6_purge(ifp);

	if (LLTABLE6(ifp))
		lltable_free(LLTABLE6(ifp));

	/* nuke any of IPv6 addresses we have */
	lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
	ia = in6_ifaddrs;
	while (ia != NULL) {
		if (ia->ia_ifa.ifa_ifp != ifp) {
			ia = ia->ia_next;
			continue;
		}
		IFA_ADDREF(&ia->ia_ifa);	/* for us */
		lck_rw_done(&in6_ifaddr_rwlock);
		in6_purgeaddr(&ia->ia_ifa);
		IFA_REMREF(&ia->ia_ifa);	/* for us */
		lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
		/*
		 * Purging the address caused in6_ifaddr_rwlock
		 * to be dropped and reacquired;
		 * therefore search again from the beginning
		 * of in6_ifaddrs list.
		 */
		ia = in6_ifaddrs;
	}
	lck_rw_done(&in6_ifaddr_rwlock);

	ifnet_lock_exclusive(ifp);

	/* undo everything done by in6_ifattach(), just in case */
	ifa = TAILQ_FIRST(&ifp->if_addrlist);
	while (ifa != NULL) {
		IFA_LOCK(ifa);
		if (ifa->ifa_addr->sa_family != AF_INET6 ||
		    !IN6_IS_ADDR_LINKLOCAL(&satosin6(&ifa->ifa_addr)->
		    sin6_addr)) {
			IFA_UNLOCK(ifa);
			ifa = TAILQ_NEXT(ifa, ifa_list);
			continue;
		}

		ia = (struct in6_ifaddr *)ifa;

		/* hold a reference for this routine */
		IFA_ADDREF_LOCKED(ifa);
		/* remove from the linked list */
		if_detach_ifa(ifp, ifa);
		IFA_UNLOCK(ifa);

		/*
		 * Leaving the multicast group(s) may involve freeing the
		 * link address multicast structure(s) for the interface,
		 * which is protected by ifnet lock.  To avoid violating
		 * lock ordering, we must drop ifnet lock before doing so.
		 * The ifa won't go away since we held a refcnt above.
		 */
		ifnet_lock_done(ifp);

		/*
		 * We have to do this work manually here instead of calling
		 * in6_purgeaddr() since in6_purgeaddr() uses the RTM_HOST flag.
		 */

		/*
		 * leave from multicast groups we have joined for the interface
		 */
		IFA_LOCK(ifa);
		while ((imm = ia->ia6_memberships.lh_first) != NULL) {
			LIST_REMOVE(imm, i6mm_chain);
			IFA_UNLOCK(ifa);
			in6_leavegroup(imm);
			IFA_LOCK(ifa);
		}

		/* remove from the routing table */
		if (ia->ia_flags & IFA_ROUTE) {
			IFA_UNLOCK(ifa);
			rt = rtalloc1((struct sockaddr *)&ia->ia_addr, 0, 0);
			if (rt != NULL) {
				(void) rtrequest(RTM_DELETE,
					(struct sockaddr *)&ia->ia_addr,
					(struct sockaddr *)&ia->ia_addr,
					(struct sockaddr *)&ia->ia_prefixmask,
					rt->rt_flags, (struct rtentry **)0);
				rtfree(rt);
			}
		} else {
			IFA_UNLOCK(ifa);
		}

		/* also remove from the IPv6 address chain(itojun&jinmei) */
		unlinked = 1;
		oia = ia;
		lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
		if (oia == (ia = in6_ifaddrs)) {
			in6_ifaddrs = ia->ia_next;
		} else {
			while (ia->ia_next && (ia->ia_next != oia))
				ia = ia->ia_next;
			if (ia->ia_next) {
				ia->ia_next = oia->ia_next;
			} else {
				nd6log((LOG_ERR,
				    "%s: didn't unlink in6ifaddr from "
				    "list\n", if_name(ifp)));
				unlinked = 0;
			}
		}
		lck_rw_done(&in6_ifaddr_rwlock);

		ifa = &oia->ia_ifa;
		/*
		 * release another refcnt for the link from in6_ifaddrs.
		 * Do this only if it's not already unlinked in the event
		 * that we lost the race, since in6_ifaddr_rwlock was
		 * momentarily dropped above.
		 */
		if (unlinked)
			IFA_REMREF(ifa);
		/* release reference held for this routine */
		IFA_REMREF(ifa);

		/*
		 * This is suboptimal, but since we dropped ifnet lock above
		 * the list might have changed.  Repeat the search from the
		 * beginning until we find the first eligible IPv6 address.
		 */
		ifnet_lock_exclusive(ifp);
		ifa = TAILQ_FIRST(&ifp->if_addrlist);
	}
	ifnet_lock_done(ifp);

	/* invalidate route caches */
	routegenid_inet6_update();

	/*
	 * remove neighbor management table.  we call it twice just to make
	 * sure we nuke everything.  maybe we need just one call.
	 * XXX: since the first call did not release addresses, some prefixes
	 * might remain.  We should call nd6_purge() again to release the
	 * prefixes after removing all addresses above.
	 * (Or can we just delay calling nd6_purge until at this point?)
	 */
	nd6_purge(ifp);

	/* remove route to link-local allnodes multicast (ff02::1) */
	bzero(&sin6, sizeof (sin6));
	sin6.sin6_len = sizeof (struct sockaddr_in6);
	sin6.sin6_family = AF_INET6;
	sin6.sin6_addr = in6addr_linklocal_allnodes;
	sin6.sin6_addr.s6_addr16[1] = htons(ifp->if_index);
	rt = rtalloc1((struct sockaddr *)&sin6, 0, 0);
	if (rt != NULL) {
		RT_LOCK(rt);
		if (rt->rt_ifp == ifp) {
			/*
			 * Prevent another thread from modifying rt_key,
			 * rt_gateway via rt_setgate() after the rt_lock
			 * is dropped by marking the route as defunct.
			 */
			rt->rt_flags |= RTF_CONDEMNED;
			RT_UNLOCK(rt);
			(void) rtrequest(RTM_DELETE, rt_key(rt), rt->rt_gateway,
			    rt_mask(rt), rt->rt_flags, 0);
		} else {
			RT_UNLOCK(rt);
		}
		rtfree(rt);
	}
}