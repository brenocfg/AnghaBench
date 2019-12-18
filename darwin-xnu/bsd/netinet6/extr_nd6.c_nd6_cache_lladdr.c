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
typedef  scalar_t__ uint64_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_dl {scalar_t__ sdl_alen; } ;
struct rtentry {int rt_flags; TYPE_1__* rt_gateway; scalar_t__ rt_llinfo; } ;
struct route_event {int dummy; } ;
struct radix_node_head {int /*<<< orphan*/  (* rnh_walktree ) (struct radix_node_head*,int /*<<< orphan*/ ,void*) ;} ;
struct nd_ifinfo {scalar_t__ initialized; int flags; } ;
struct mbuf {int dummy; } ;
struct llinfo_nd6 {int ln_state; int ln_router; struct mbuf* ln_hold; } ;
struct in6_addr {int dummy; } ;
struct ifnet {scalar_t__ if_addrlen; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 size_t AF_INET6 ; 
 scalar_t__ AF_LINK ; 
 scalar_t__ FALSE ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (struct in6_addr*) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  ND6_CACHE_STATE_TRANSITION (struct llinfo_nd6*,int) ; 
 int ND6_IFF_PERFORMNUD ; 
 int ND6_LLINFO_INCOMPLETE ; 
 int ND6_LLINFO_NOSTATE ; 
 int ND6_LLINFO_REACHABLE ; 
 int ND6_LLINFO_STALE ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
#define  ND_NEIGHBOR_SOLICIT 131 
#define  ND_REDIRECT 130 
 int ND_REDIRECT_ROUTER ; 
#define  ND_ROUTER_ADVERT 129 
#define  ND_ROUTER_SOLICIT 128 
 int ROUTE_LLENTRY_CHANGED ; 
 int ROUTE_LLENTRY_RESOLVED ; 
 int RTF_GATEWAY ; 
 int RTF_LLINFO ; 
 int RTF_ROUTER ; 
 int RTF_STATIC ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 struct sockaddr_dl* SDL (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ bcmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  defrouter_select (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ln_setexpire (struct llinfo_nd6*,scalar_t__) ; 
 int /*<<< orphan*/  nd6_free (struct rtentry*) ; 
 scalar_t__ nd6_gctimer ; 
 int /*<<< orphan*/  nd6_llreach_alloc (struct rtentry*,struct ifnet*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct rtentry* nd6_lookup (struct in6_addr*,int,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6_output_list (struct ifnet*,struct ifnet*,struct mbuf*,struct sockaddr_in6*,struct rtentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_sched_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ net_uptime () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  route_event_enqueue_nwk_wq_entry (struct rtentry*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  route_event_init (struct route_event*,struct rtentry*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  route_event_walktree ; 
 struct radix_node_head** rt_tables ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 
 int /*<<< orphan*/  rtkey_to_sa6 (struct rtentry*,struct sockaddr_in6*) ; 
 int /*<<< orphan*/  stub1 (struct radix_node_head*,int /*<<< orphan*/ ,void*) ; 

void
nd6_cache_lladdr(struct ifnet *ifp, struct in6_addr *from, char *lladdr,
    int lladdrlen, int type, int code)
{
#pragma unused(lladdrlen)
	struct rtentry *rt = NULL;
	struct llinfo_nd6 *ln = NULL;
	int is_newentry;
	struct sockaddr_dl *sdl = NULL;
	int do_update;
	int olladdr;
	int llchange;
	int newstate = 0;
	uint64_t timenow;
	boolean_t sched_timeout = FALSE;
	struct nd_ifinfo *ndi = NULL;

	if (ifp == NULL)
		panic("ifp == NULL in nd6_cache_lladdr");
	if (from == NULL)
		panic("from == NULL in nd6_cache_lladdr");

	/* nothing must be updated for unspecified address */
	if (IN6_IS_ADDR_UNSPECIFIED(from))
		return;

	/*
	 * Validation about ifp->if_addrlen and lladdrlen must be done in
	 * the caller.
	 */
	timenow = net_uptime();

	rt = nd6_lookup(from, 0, ifp, 0);
	if (rt == NULL) {
		if ((rt = nd6_lookup(from, 1, ifp, 0)) == NULL)
			return;
		RT_LOCK_ASSERT_HELD(rt);
		is_newentry = 1;
	} else {
		RT_LOCK_ASSERT_HELD(rt);
		/* do nothing if static ndp is set */
		if (rt->rt_flags & RTF_STATIC) {
			RT_REMREF_LOCKED(rt);
			RT_UNLOCK(rt);
			return;
		}
		is_newentry = 0;
	}

	if (rt == NULL)
		return;
	if ((rt->rt_flags & (RTF_GATEWAY | RTF_LLINFO)) != RTF_LLINFO) {
fail:
		RT_UNLOCK(rt);
		nd6_free(rt);
		rtfree(rt);
		return;
	}
	ln = (struct llinfo_nd6 *)rt->rt_llinfo;
	if (ln == NULL)
		goto fail;
	if (rt->rt_gateway == NULL)
		goto fail;
	if (rt->rt_gateway->sa_family != AF_LINK)
		goto fail;
	sdl = SDL(rt->rt_gateway);

	olladdr = (sdl->sdl_alen) ? 1 : 0;
	if (olladdr && lladdr) {
		if (bcmp(lladdr, LLADDR(sdl), ifp->if_addrlen))
			llchange = 1;
		else
			llchange = 0;
	} else
		llchange = 0;

	/*
	 * newentry olladdr  lladdr  llchange	(*=record)
	 *	0	n	n	--	(1)
	 *	0	y	n	--	(2)
	 *	0	n	y	--	(3) * STALE
	 *	0	y	y	n	(4) *
	 *	0	y	y	y	(5) * STALE
	 *	1	--	n	--	(6)   NOSTATE(= PASSIVE)
	 *	1	--	y	--	(7) * STALE
	 */

	if (lladdr != NULL) {		/* (3-5) and (7) */
		/*
		 * Record source link-layer address
		 * XXX is it dependent to ifp->if_type?
		 */
		sdl->sdl_alen = ifp->if_addrlen;
		bcopy(lladdr, LLADDR(sdl), ifp->if_addrlen);

		/* cache the gateway (sender HW) address */
		nd6_llreach_alloc(rt, ifp, LLADDR(sdl), sdl->sdl_alen, FALSE);
	}

	if (is_newentry == 0) {
		if ((!olladdr && lladdr != NULL) ||	/* (3) */
		    (olladdr && lladdr != NULL && llchange)) {	/* (5) */
			do_update = 1;
			newstate = ND6_LLINFO_STALE;
		} else					/* (1-2,4) */
			do_update = 0;
	} else {
		do_update = 1;
		if (lladdr == NULL)			/* (6) */
			newstate = ND6_LLINFO_NOSTATE;
		else					/* (7) */
			newstate = ND6_LLINFO_STALE;
	}

	/*
	 * For interface's that do not perform NUD
	 * neighbor cache entres must always be marked
	 * reachable with no expiry
	 */
	ndi = ND_IFINFO(ifp);
	VERIFY((NULL != ndi) && (TRUE == ndi->initialized));

	if (ndi && !(ndi->flags & ND6_IFF_PERFORMNUD)) {
		newstate = ND6_LLINFO_REACHABLE;
		ln_setexpire(ln, 0);
	}

	if (do_update) {
		/*
		 * Update the state of the neighbor cache.
		 */
		ND6_CACHE_STATE_TRANSITION(ln, newstate);

		if ((ln->ln_state == ND6_LLINFO_STALE) ||
		   (ln->ln_state == ND6_LLINFO_REACHABLE)) {
			struct mbuf *m = ln->ln_hold;
			/*
			 * XXX: since nd6_output() below will cause
			 * state tansition to DELAY and reset the timer,
			 * we must set the timer now, although it is actually
			 * meaningless.
			 */
			if (ln->ln_state == ND6_LLINFO_STALE)
				ln_setexpire(ln, timenow + nd6_gctimer);

			ln->ln_hold = NULL;
			if (m != NULL) {
				struct sockaddr_in6 sin6;

				rtkey_to_sa6(rt, &sin6);
				/*
				 * we assume ifp is not a p2p here, so just
				 * set the 2nd argument as the 1st one.
				 */
				RT_UNLOCK(rt);
				nd6_output_list(ifp, ifp, m, &sin6, rt, NULL);
				RT_LOCK(rt);
			}
		} else if (ln->ln_state == ND6_LLINFO_INCOMPLETE) {
			/* probe right away */
			ln_setexpire(ln, timenow);
			sched_timeout = TRUE;
		}
	}

	/*
	 * ICMP6 type dependent behavior.
	 *
	 * NS: clear IsRouter if new entry
	 * RS: clear IsRouter
	 * RA: set IsRouter if there's lladdr
	 * redir: clear IsRouter if new entry
	 *
	 * RA case, (1):
	 * The spec says that we must set IsRouter in the following cases:
	 * - If lladdr exist, set IsRouter.  This means (1-5).
	 * - If it is old entry (!newentry), set IsRouter.  This means (7).
	 * So, based on the spec, in (1-5) and (7) cases we must set IsRouter.
	 * A quetion arises for (1) case.  (1) case has no lladdr in the
	 * neighbor cache, this is similar to (6).
	 * This case is rare but we figured that we MUST NOT set IsRouter.
	 *
	 * newentry olladdr  lladdr  llchange	    NS  RS	RA	redir
	 *								D R
	 *	0	n	n	--	(1)	c	?	s
	 *	0	y	n	--	(2)	c	s	s
	 *	0	n	y	--	(3)	c	s	s
	 *	0	y	y	n	(4)	c	s	s
	 *	0	y	y	y	(5)	c	s	s
	 *	1	--	n	--	(6) c	c		c s
	 *	1	--	y	--	(7) c	c	s	c s
	 *
	 *					(c=clear s=set)
	 */
	switch (type & 0xff) {
	case ND_NEIGHBOR_SOLICIT:
		/*
		 * New entry must have is_router flag cleared.
		 */
		if (is_newentry)	/* (6-7) */
			ln->ln_router = 0;
		break;
	case ND_REDIRECT:
		/*
		 * If the ICMP message is a Redirect to a better router, always
		 * set the is_router flag.  Otherwise, if the entry is newly
		 * created, then clear the flag.  [RFC 4861, sec 8.3]
		 */
		if (code == ND_REDIRECT_ROUTER)
			ln->ln_router = 1;
		else if (is_newentry) /* (6-7) */
			ln->ln_router = 0;
		break;
	case ND_ROUTER_SOLICIT:
		/*
		 * is_router flag must always be cleared.
		 */
		ln->ln_router = 0;
		break;
	case ND_ROUTER_ADVERT:
		/*
		 * Mark an entry with lladdr as a router.
		 */
		if ((!is_newentry && (olladdr || lladdr)) ||	/* (2-5) */
		    (is_newentry && lladdr)) {			/* (7) */
			ln->ln_router = 1;
		}
		break;
	}

	if (do_update) {
		int route_ev_code = 0;

		if (llchange)
			route_ev_code = ROUTE_LLENTRY_CHANGED;
		else
			route_ev_code = ROUTE_LLENTRY_RESOLVED;

		/* Enqueue work item to invoke callback for this route entry */
		route_event_enqueue_nwk_wq_entry(rt, NULL, route_ev_code, NULL, TRUE);

		if (ln->ln_router || (rt->rt_flags & RTF_ROUTER)) {
			struct radix_node_head  *rnh = NULL;
			struct route_event rt_ev;
			route_event_init(&rt_ev, rt, NULL, llchange ? ROUTE_LLENTRY_CHANGED :
			    ROUTE_LLENTRY_RESOLVED);
			/*
			 * We already have a valid reference on rt.
			 * The function frees that before returning.
			 * We therefore don't need an extra reference here
			 */
			RT_UNLOCK(rt);
			lck_mtx_lock(rnh_lock);

			rnh = rt_tables[AF_INET6];
			if (rnh != NULL)
				(void) rnh->rnh_walktree(rnh, route_event_walktree,
				    (void *)&rt_ev);
			lck_mtx_unlock(rnh_lock);
			RT_LOCK(rt);
		}
	}

	/*
	 * When the link-layer address of a router changes, select the
	 * best router again.  In particular, when the neighbor entry is newly
	 * created, it might affect the selection policy.
	 * Question: can we restrict the first condition to the "is_newentry"
	 * case?
	 *
	 * Note: Perform default router selection even when we are a router,
	 * if Scoped Routing is enabled.
	 */
	if (do_update && ln->ln_router) {
		RT_REMREF_LOCKED(rt);
		RT_UNLOCK(rt);
		lck_mtx_lock(nd6_mutex);
		defrouter_select(ifp);
		lck_mtx_unlock(nd6_mutex);
	} else {
		RT_REMREF_LOCKED(rt);
		RT_UNLOCK(rt);
	}
	if (sched_timeout) {
		lck_mtx_lock(rnh_lock);
		nd6_sched_timeout(NULL, NULL);
		lck_mtx_unlock(rnh_lock);
	}
}