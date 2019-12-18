#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int rmx_locks; int /*<<< orphan*/  rmx_mtu; } ;
struct rtentry {int rt_flags; struct ifaddr* rt_ifa; struct ifnet* rt_ifp; TYPE_1__ rt_rmx; int /*<<< orphan*/  (* rt_if_ref_fn ) (struct ifnet*,int) ;int /*<<< orphan*/  (* rt_llinfo_purge ) (struct rtentry*) ;} ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_index; int /*<<< orphan*/  if_addrhead; } ;
struct ifaddr {void (* ifa_rtrequest ) (int,struct rtentry*,struct sockaddr*) ;struct ifnet* ifa_ifp; } ;
struct TYPE_7__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ CLAT46_HDR_EXPANSION_OVERHD ; 
 int /*<<< orphan*/  IFA_ADDREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IN6_LINKMTU (struct ifnet*) ; 
 scalar_t__ INTF_ADJUST_MTU_FOR_CLAT46 (struct ifnet*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int RTF_CONDEMNED ; 
 int RTF_HOST ; 
 int RTM_ADD ; 
 int RTM_DELETE ; 
 int RTV_MTU ; 
 int /*<<< orphan*/  RT_ADDREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 struct ifaddr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct ifnet* if_withname (struct sockaddr*) ; 
 struct ifaddr* ifa_ifwithaddr (TYPE_2__*) ; 
 struct ifaddr* ifa_ifwithaddr_scoped (struct sockaddr*,unsigned int) ; 
 struct ifaddr* ifa_ifwithnet_scoped (struct sockaddr*,unsigned int) ; 
 struct ifaddr* ifa_ifwithroute_scoped_locked (int,TYPE_2__*,struct sockaddr*,unsigned int) ; 
 struct ifaddr* ifaof_ifpforaddr (struct sockaddr*,struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  routegenid_inet6_update () ; 
 int /*<<< orphan*/  routegenid_inet_update () ; 
 TYPE_2__* rt_key (struct rtentry*) ; 
 scalar_t__ rt_primary_default (struct rtentry*,TYPE_2__*) ; 
 int /*<<< orphan*/  rtsetifa (struct rtentry*,struct ifaddr*) ; 
 int /*<<< orphan*/  set_primary_ifscope (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rtentry*) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,int) ; 
 int /*<<< orphan*/  stub3 (struct ifnet*,int) ; 

__attribute__((used)) static void
rt_setif(struct rtentry *rt, struct sockaddr *Ifpaddr, struct sockaddr *Ifaaddr,
    struct sockaddr *Gate, unsigned int ifscope)
{
	struct ifaddr *ifa = NULL;
	struct ifnet *ifp = NULL;
	void (*ifa_rtrequest)(int, struct rtentry *, struct sockaddr *);

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	RT_LOCK_ASSERT_HELD(rt);

	/* Don't update a defunct route */
	if (rt->rt_flags & RTF_CONDEMNED)
		return;

	/* Add an extra ref for ourselves */
	RT_ADDREF_LOCKED(rt);

	/* Become a regular mutex, just in case */
	RT_CONVERT_LOCK(rt);

	/*
	 * New gateway could require new ifaddr, ifp; flags may also
	 * be different; ifp may be specified by ll sockaddr when
	 * protocol address is ambiguous.
	 */
	if (Ifpaddr && (ifa = ifa_ifwithnet_scoped(Ifpaddr, ifscope)) &&
	    (ifp = ifa->ifa_ifp) && (Ifaaddr || Gate)) {
		IFA_REMREF(ifa);
		ifa = ifaof_ifpforaddr(Ifaaddr ? Ifaaddr : Gate, ifp);
	} else {
		if (ifa != NULL) {
			IFA_REMREF(ifa);
			ifa = NULL;
		}
		if (Ifpaddr && (ifp = if_withname(Ifpaddr))) {
			if (Gate) {
				ifa = ifaof_ifpforaddr(Gate, ifp);
			} else {
				ifnet_lock_shared(ifp);
				ifa = TAILQ_FIRST(&ifp->if_addrhead);
				if (ifa != NULL)
					IFA_ADDREF(ifa);
				ifnet_lock_done(ifp);
			}
		} else if (Ifaaddr &&
		    (ifa = ifa_ifwithaddr_scoped(Ifaaddr, ifscope))) {
			ifp = ifa->ifa_ifp;
		} else if (Gate != NULL) {
			/*
			 * Safe to drop rt_lock and use rt_key, since holding
			 * rnh_lock here prevents another thread from calling
			 * rt_setgate() on this route.  We cannot hold the
			 * lock across ifa_ifwithroute since the lookup done
			 * by that routine may point to the same route.
			 */
			RT_UNLOCK(rt);
			if ((ifa = ifa_ifwithroute_scoped_locked(rt->rt_flags,
			    rt_key(rt), Gate, ifscope)) != NULL)
				ifp = ifa->ifa_ifp;
			RT_LOCK(rt);
			/* Don't update a defunct route */
			if (rt->rt_flags & RTF_CONDEMNED) {
				if (ifa != NULL)
					IFA_REMREF(ifa);
				/* Release extra ref */
				RT_REMREF_LOCKED(rt);
				return;
			}
		}
	}

	/* trigger route cache reevaluation */
	if (rt_key(rt)->sa_family == AF_INET)
		routegenid_inet_update();
#if INET6
	else if (rt_key(rt)->sa_family == AF_INET6)
		routegenid_inet6_update();
#endif /* INET6 */

	if (ifa != NULL) {
		struct ifaddr *oifa = rt->rt_ifa;
		if (oifa != ifa) {
			if (oifa != NULL) {
				IFA_LOCK_SPIN(oifa);
				ifa_rtrequest = oifa->ifa_rtrequest;
				IFA_UNLOCK(oifa);
				if (ifa_rtrequest != NULL)
					ifa_rtrequest(RTM_DELETE, rt, Gate);
			}
			rtsetifa(rt, ifa);

			if (rt->rt_ifp != ifp) {
				/*
				 * Purge any link-layer info caching.
				 */
				if (rt->rt_llinfo_purge != NULL)
					rt->rt_llinfo_purge(rt);

				/*
				 * Adjust route ref count for the interfaces.
				 */
				if (rt->rt_if_ref_fn != NULL) {
					rt->rt_if_ref_fn(ifp, 1);
					rt->rt_if_ref_fn(rt->rt_ifp, -1);
				}
			}
			rt->rt_ifp = ifp;
			/*
			 * If this is the (non-scoped) default route, record
			 * the interface index used for the primary ifscope.
			 */
			if (rt_primary_default(rt, rt_key(rt))) {
				set_primary_ifscope(rt_key(rt)->sa_family,
				    rt->rt_ifp->if_index);
			}
			/*
			 * If rmx_mtu is not locked, update it
			 * to the MTU used by the new interface.
			 */
			if (!(rt->rt_rmx.rmx_locks & RTV_MTU)) {
				rt->rt_rmx.rmx_mtu = rt->rt_ifp->if_mtu;
				if (rt_key(rt)->sa_family == AF_INET &&
				    INTF_ADJUST_MTU_FOR_CLAT46(ifp)) {
					rt->rt_rmx.rmx_mtu = IN6_LINKMTU(rt->rt_ifp);
					/* Further adjust the size for CLAT46 expansion */
					rt->rt_rmx.rmx_mtu -= CLAT46_HDR_EXPANSION_OVERHD;
				}
			}

			if (rt->rt_ifa != NULL) {
				IFA_LOCK_SPIN(rt->rt_ifa);
				ifa_rtrequest = rt->rt_ifa->ifa_rtrequest;
				IFA_UNLOCK(rt->rt_ifa);
				if (ifa_rtrequest != NULL)
					ifa_rtrequest(RTM_ADD, rt, Gate);
			}
			IFA_REMREF(ifa);
			/* Release extra ref */
			RT_REMREF_LOCKED(rt);
			return;
		}
		IFA_REMREF(ifa);
		ifa = NULL;
	}

	/* XXX: to reset gateway to correct value, at RTM_CHANGE */
	if (rt->rt_ifa != NULL) {
		IFA_LOCK_SPIN(rt->rt_ifa);
		ifa_rtrequest = rt->rt_ifa->ifa_rtrequest;
		IFA_UNLOCK(rt->rt_ifa);
		if (ifa_rtrequest != NULL)
			ifa_rtrequest(RTM_ADD, rt, Gate);
	}

	/*
	 * Workaround for local address routes pointing to the loopback
	 * interface added by configd, until <rdar://problem/12970142>.
	 */
	if ((rt->rt_ifp->if_flags & IFF_LOOPBACK) &&
	    (rt->rt_flags & RTF_HOST) && rt->rt_ifa->ifa_ifp == rt->rt_ifp) {
		ifa = ifa_ifwithaddr(rt_key(rt));
		if (ifa != NULL) {
			if (ifa != rt->rt_ifa)
				rtsetifa(rt, ifa);
			IFA_REMREF(ifa);
		}
	}

	/* Release extra ref */
	RT_REMREF_LOCKED(rt);
}