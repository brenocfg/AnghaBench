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
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_family; int /*<<< orphan*/  sa_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  rmx_expire; } ;
struct rtfc_arg {int rt_flags; struct rtfc_arg* rt0; struct radix_node_head* rnh; struct rtfc_arg* rt_gwroute; TYPE_3__* rt_ifp; struct rtfc_arg* rt_parent; int /*<<< orphan*/  rt_expire; TYPE_2__ rt_rmx; struct ifaddr* rt_ifa; int /*<<< orphan*/  rt_nodes; struct sockaddr* rt_gateway; int /*<<< orphan*/ * rt_tree_genid; int /*<<< orphan*/  base_uptime; int /*<<< orphan*/  base_calendartime; int /*<<< orphan*/  rt_evhdlr_ctxt; struct sockaddr* rt_genmask; int /*<<< orphan*/  rt_refcnt; } ;
struct rtentry_dbg {int dummy; } ;
struct rtentry {int rt_flags; struct rtentry* rt0; struct radix_node_head* rnh; struct rtentry* rt_gwroute; TYPE_3__* rt_ifp; struct rtentry* rt_parent; int /*<<< orphan*/  rt_expire; TYPE_2__ rt_rmx; struct ifaddr* rt_ifa; int /*<<< orphan*/  rt_nodes; struct sockaddr* rt_gateway; int /*<<< orphan*/ * rt_tree_genid; int /*<<< orphan*/  base_uptime; int /*<<< orphan*/  base_calendartime; int /*<<< orphan*/  rt_evhdlr_ctxt; struct sockaddr* rt_genmask; int /*<<< orphan*/  rt_refcnt; } ;
struct route_event {int dummy; } ;
struct radix_node_head {int /*<<< orphan*/  (* rnh_walktree_from ) (struct radix_node_head*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtfc_arg*) ;struct radix_node* (* rnh_addaddr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radix_node_head*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rnh_walktree ) (struct radix_node_head*,int /*<<< orphan*/ ,void*) ;struct radix_node* (* rnh_deladdr ) (struct sockaddr*,struct sockaddr*,struct radix_node_head*) ;} ;
struct radix_node {int rn_flags; } ;
struct ifaddr {void (* ifa_rtrequest ) (int,struct rtfc_arg*,struct sockaddr*) ;TYPE_3__* ifa_ifp; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_1__ sin_addr; } ;
struct TYPE_7__ {unsigned int if_index; } ;

/* Variables and functions */
#define  AF_INET 131 
 int AF_INET6 ; 
 int /*<<< orphan*/  Bcopy (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Bzero (struct rtfc_arg*,int) ; 
 int EEXIST ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int ENOBUFS ; 
 int ESRCH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFA_ADDREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 unsigned int IFSCOPE_NONE ; 
 int /*<<< orphan*/  IN_LINKLOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int RNF_ACTIVE ; 
 int RNF_ROOT ; 
 int /*<<< orphan*/  ROUTE_ENTRY_DELETED ; 
 int /*<<< orphan*/  ROUTE_LLENTRY_DELETED ; 
 int RTD_DEBUG ; 
 int RTF_CLONING ; 
 int RTF_CONDEMNED ; 
 int RTF_GATEWAY ; 
 int RTF_HOST ; 
 int RTF_IFSCOPE ; 
 int RTF_NOIFREF ; 
 int RTF_PRCLONING ; 
 int RTF_PROXY ; 
 int RTF_REJECT ; 
 int RTF_ROUTER ; 
 int RTF_STATIC ; 
 int RTF_UP ; 
 int RTF_WASCLONED ; 
#define  RTM_ADD 130 
#define  RTM_DELETE 129 
#define  RTM_RESOLVE 128 
 int /*<<< orphan*/  RT_ADDREF_LOCKED (struct rtfc_arg*) ; 
 int /*<<< orphan*/  RT_GENID_SYNC (struct rtfc_arg*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtfc_arg*) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtfc_arg*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtfc_arg*) ; 
 int /*<<< orphan*/  R_Free (struct sockaddr*) ; 
 struct sockaddr* SA (struct rtfc_arg*) ; 
 TYPE_4__* SIN (struct sockaddr*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rtentry_dbg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  eventhandler_lists_ctxt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 struct ifaddr* ifa_ifwithroute_locked (int,struct sockaddr*,struct sockaddr*) ; 
 struct ifaddr* ifa_ifwithroute_scoped_locked (int,struct sockaddr*,struct sockaddr*,unsigned int) ; 
 struct sockaddr* ma_copy (int,struct sockaddr*,struct sockaddr_storage*,unsigned int) ; 
 int /*<<< orphan*/  net_uptime () ; 
 int /*<<< orphan*/  nstat_route_detach (struct rtfc_arg*) ; 
 int /*<<< orphan*/  nstat_route_new_entry (struct rtfc_arg*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  route_event_enqueue_nwk_wq_entry (struct rtfc_arg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_event_init (struct route_event*,struct rtfc_arg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_event_walktree ; 
 int /*<<< orphan*/  route_genid_inet ; 
 int /*<<< orphan*/  routegenid_inet_update () ; 
 int /*<<< orphan*/  rt_clear_idleref (struct rtfc_arg*) ; 
 int /*<<< orphan*/  rt_fixchange ; 
 int /*<<< orphan*/  rt_fixdelete ; 
 struct sockaddr* rt_key (struct rtfc_arg*) ; 
 int /*<<< orphan*/ * rt_mask (struct rtfc_arg*) ; 
 int /*<<< orphan*/  rt_maskedcopy (struct sockaddr*,struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  rt_primary_default (struct rtfc_arg*,struct sockaddr*) ; 
 int /*<<< orphan*/  rt_set_gwroute (struct rtfc_arg*,struct sockaddr*,struct rtfc_arg*) ; 
 int /*<<< orphan*/  rt_setexpire (struct rtfc_arg*,int /*<<< orphan*/ ) ; 
 int rt_setgate (struct rtfc_arg*,struct sockaddr*,struct sockaddr*) ; 
 struct radix_node_head** rt_tables ; 
 struct rtfc_arg* rtalloc1_locked (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 struct rtfc_arg* rtalloc1_scoped_locked (struct sockaddr*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  rtd_trash_link ; 
 struct rtfc_arg* rte_alloc () ; 
 int rte_debug ; 
 int /*<<< orphan*/  rte_free (struct rtfc_arg*) ; 
 int /*<<< orphan*/  rte_lock_destroy (struct rtfc_arg*) ; 
 int /*<<< orphan*/  rte_lock_init (struct rtfc_arg*) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtfc_arg*) ; 
 int /*<<< orphan*/  rtrequest_locked (int const,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsetifa (struct rtfc_arg*,struct ifaddr*) ; 
 int /*<<< orphan*/  rttrash ; 
 int /*<<< orphan*/  rttrash_head ; 
 struct sockaddr* sa_copy (struct sockaddr*,struct sockaddr_storage*,unsigned int*) ; 
 int /*<<< orphan*/  set_primary_ifscope (int,unsigned int) ; 
 unsigned int sin6_get_ifscope (struct sockaddr*) ; 
 unsigned int sin_get_ifscope (struct sockaddr*) ; 
 struct radix_node* stub1 (struct sockaddr*,struct sockaddr*,struct radix_node_head*) ; 
 int /*<<< orphan*/  stub2 (struct radix_node_head*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtfc_arg*) ; 
 int /*<<< orphan*/  stub3 (struct radix_node_head*,int /*<<< orphan*/ ,void*) ; 
 struct radix_node* stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radix_node_head*,int /*<<< orphan*/ ) ; 
 struct radix_node* stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct radix_node_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct radix_node_head*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtfc_arg*) ; 

__attribute__((used)) static int
rtrequest_common_locked(int req, struct sockaddr *dst0,
    struct sockaddr *gateway, struct sockaddr *netmask, int flags,
    struct rtentry **ret_nrt, unsigned int ifscope)
{
	int error = 0;
	struct rtentry *rt;
	struct radix_node *rn;
	struct radix_node_head *rnh;
	struct ifaddr *ifa = NULL;
	struct sockaddr *ndst, *dst = dst0;
	struct sockaddr_storage ss, mask;
	struct timeval caltime;
	int af = dst->sa_family;
	void (*ifa_rtrequest)(int, struct rtentry *, struct sockaddr *);

#define	senderr(x) { error = x; goto bad; }

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);
	/*
	 * Find the correct routing tree to use for this Address Family
	 */
	if ((rnh = rt_tables[af]) == NULL)
		senderr(ESRCH);
	/*
	 * If we are adding a host route then we don't want to put
	 * a netmask in the tree
	 */
	if (flags & RTF_HOST)
		netmask = NULL;

	/*
	 * If Scoped Routing is enabled, use a local copy of the destination
	 * address to store the scope ID into.  This logic is repeated below
	 * in the RTM_RESOLVE handler since the caller does not normally
	 * specify such a flag during a resolve, as well as for the handling
	 * of IPv4 link-local address; instead, it passes in the route used for
	 * cloning for which the scope info is derived from.  Note also that
	 * in the case of RTM_DELETE, the address passed in by the caller
	 * might already contain the scope ID info when it is the key itself,
	 * thus making RTF_IFSCOPE unnecessary; one instance where it is
	 * explicitly set is inside route_output() as part of handling a
	 * routing socket request.
	 */
#if INET6
	if (req != RTM_RESOLVE && ((af == AF_INET) || (af == AF_INET6))) {
#else
	if (req != RTM_RESOLVE && af == AF_INET) {
#endif /* !INET6 */
		/* Transform dst into the internal routing table form */
		dst = sa_copy(dst, &ss, &ifscope);

		/* Transform netmask into the internal routing table form */
		if (netmask != NULL)
			netmask = ma_copy(af, netmask, &mask, ifscope);

		if (ifscope != IFSCOPE_NONE)
			flags |= RTF_IFSCOPE;
	} else if ((flags & RTF_IFSCOPE) &&
	    (af != AF_INET && af != AF_INET6)) {
		senderr(EINVAL);
	}

	if (ifscope == IFSCOPE_NONE)
		flags &= ~RTF_IFSCOPE;

	switch (req) {
	case RTM_DELETE: {
		struct rtentry *gwrt = NULL;
		boolean_t was_router = FALSE;
		uint32_t old_rt_refcnt = 0;
		/*
		 * Remove the item from the tree and return it.
		 * Complain if it is not there and do no more processing.
		 */
		if ((rn = rnh->rnh_deladdr(dst, netmask, rnh)) == NULL)
			senderr(ESRCH);
		if (rn->rn_flags & (RNF_ACTIVE | RNF_ROOT)) {
			panic("rtrequest delete");
			/* NOTREACHED */
		}
		rt = (struct rtentry *)rn;

		RT_LOCK(rt);
		old_rt_refcnt = rt->rt_refcnt;
		rt->rt_flags &= ~RTF_UP;
		/*
		 * Release any idle reference count held on the interface
		 * as this route is no longer externally visible.
		 */
		rt_clear_idleref(rt);
		/*
		 * Take an extra reference to handle the deletion of a route
		 * entry whose reference count is already 0; e.g. an expiring
		 * cloned route entry or an entry that was added to the table
		 * with 0 reference. If the caller is interested in this route,
		 * we will return it with the reference intact. Otherwise we
		 * will decrement the reference via rtfree_locked() and then
		 * possibly deallocate it.
		 */
		RT_ADDREF_LOCKED(rt);

		/*
		 * For consistency, in case the caller didn't set the flag.
		 */
		rt->rt_flags |= RTF_CONDEMNED;

		/*
		 * Clear RTF_ROUTER if it's set.
		 */
		if (rt->rt_flags & RTF_ROUTER) {
			was_router = TRUE;
			VERIFY(rt->rt_flags & RTF_HOST);
			rt->rt_flags &= ~RTF_ROUTER;
		}

		/*
		 * Enqueue work item to invoke callback for this route entry
		 *
		 * If the old count is 0, it implies that last reference is being
		 * removed and there's no one listening for this route event.
		 */
		if (old_rt_refcnt != 0)
			route_event_enqueue_nwk_wq_entry(rt, NULL,
			    ROUTE_ENTRY_DELETED, NULL, TRUE);

		/*
		 * Now search what's left of the subtree for any cloned
		 * routes which might have been formed from this node.
		 */
		if ((rt->rt_flags & (RTF_CLONING | RTF_PRCLONING)) &&
		    rt_mask(rt)) {
			RT_UNLOCK(rt);
			rnh->rnh_walktree_from(rnh, dst, rt_mask(rt),
			    rt_fixdelete, rt);
			RT_LOCK(rt);
		}

		if (was_router) {
			struct route_event rt_ev;
			route_event_init(&rt_ev, rt, NULL, ROUTE_LLENTRY_DELETED);
			RT_UNLOCK(rt);
			(void) rnh->rnh_walktree(rnh,
			    route_event_walktree, (void *)&rt_ev);
			RT_LOCK(rt);
		}

		/*
		 * Remove any external references we may have.
		 */
		if ((gwrt = rt->rt_gwroute) != NULL)
			rt->rt_gwroute = NULL;

		/*
		 * give the protocol a chance to keep things in sync.
		 */
		if ((ifa = rt->rt_ifa) != NULL) {
			IFA_LOCK_SPIN(ifa);
			ifa_rtrequest = ifa->ifa_rtrequest;
			IFA_UNLOCK(ifa);
			if (ifa_rtrequest != NULL)
				ifa_rtrequest(RTM_DELETE, rt, NULL);
			/* keep reference on rt_ifa */
			ifa = NULL;
		}

		/*
		 * one more rtentry floating around that is not
		 * linked to the routing table.
		 */
		(void) OSIncrementAtomic(&rttrash);
		if (rte_debug & RTD_DEBUG) {
			TAILQ_INSERT_TAIL(&rttrash_head,
			    (struct rtentry_dbg *)rt, rtd_trash_link);
		}

		/*
		 * If this is the (non-scoped) default route, clear
		 * the interface index used for the primary ifscope.
		 */
		if (rt_primary_default(rt, rt_key(rt))) {
			set_primary_ifscope(rt_key(rt)->sa_family,
			    IFSCOPE_NONE);
		}

#if NECP
		/*
		 * If this is a change in a default route, update
		 * necp client watchers to re-evaluate
		 */
		if (SA_DEFAULT(rt_key(rt))) {
			if (rt->rt_ifp != NULL) {
				ifnet_touch_lastupdown(rt->rt_ifp);
			}
			necp_update_all_clients();
		}
#endif /* NECP */

		RT_UNLOCK(rt);

		/*
		 * This might result in another rtentry being freed if
		 * we held its last reference.  Do this after the rtentry
		 * lock is dropped above, as it could lead to the same
		 * lock being acquired if gwrt is a clone of rt.
		 */
		if (gwrt != NULL)
			rtfree_locked(gwrt);

		/*
		 * If the caller wants it, then it can have it,
		 * but it's up to it to free the rtentry as we won't be
		 * doing it.
		 */
		if (ret_nrt != NULL) {
			/* Return the route to caller with reference intact */
			*ret_nrt = rt;
		} else {
			/* Dereference or deallocate the route */
			rtfree_locked(rt);
		}
		if (af == AF_INET)
			routegenid_inet_update();
#if INET6
		else if (af == AF_INET6)
			routegenid_inet6_update();
#endif /* INET6 */
		break;
	}
	case RTM_RESOLVE:
		if (ret_nrt == NULL || (rt = *ret_nrt) == NULL)
			senderr(EINVAL);
		/*
		 * According to the UNIX conformance tests, we need to return
		 * ENETUNREACH when the parent route is RTF_REJECT.
		 * However, there isn't any point in cloning RTF_REJECT
		 * routes, so we immediately return an error.
		 */
		if (rt->rt_flags & RTF_REJECT) {
			if (rt->rt_flags & RTF_HOST) {
				senderr(EHOSTUNREACH);
			} else {
				senderr(ENETUNREACH);
			}
		}
		/*
		 * If cloning, we have the parent route given by the caller
		 * and will use its rt_gateway, rt_rmx as part of the cloning
		 * process below.  Since rnh_lock is held at this point, the
		 * parent's rt_ifa and rt_gateway will not change, and its
		 * relevant rt_flags will not change as well.  The only thing
		 * that could change are the metrics, and thus we hold the
		 * parent route's rt_lock later on during the actual copying
		 * of rt_rmx.
		 */
		ifa = rt->rt_ifa;
		IFA_ADDREF(ifa);
		flags = rt->rt_flags &
		    ~(RTF_CLONING | RTF_PRCLONING | RTF_STATIC);
		flags |= RTF_WASCLONED;
		gateway = rt->rt_gateway;
		if ((netmask = rt->rt_genmask) == NULL)
			flags |= RTF_HOST;

#if INET6
		if (af != AF_INET && af != AF_INET6)
#else
		if (af != AF_INET)
#endif /* !INET6 */
			goto makeroute;

		/*
		 * When scoped routing is enabled, cloned entries are
		 * always scoped according to the interface portion of
		 * the parent route.  The exception to this are IPv4
		 * link local addresses, or those routes that are cloned
		 * from a RTF_PROXY route.  For the latter, the clone
		 * gets to keep the RTF_PROXY flag.
		 */
		if ((af == AF_INET &&
		    IN_LINKLOCAL(ntohl(SIN(dst)->sin_addr.s_addr))) ||
		    (rt->rt_flags & RTF_PROXY)) {
			ifscope = IFSCOPE_NONE;
			flags &= ~RTF_IFSCOPE;
			/*
			 * These types of cloned routes aren't currently
			 * eligible for idle interface reference counting.
			 */
			flags |= RTF_NOIFREF;
		} else {
			if (flags & RTF_IFSCOPE) {
				ifscope = (af == AF_INET) ?
				    sin_get_ifscope(rt_key(rt)) :
				    sin6_get_ifscope(rt_key(rt));
			} else {
				ifscope = rt->rt_ifp->if_index;
				flags |= RTF_IFSCOPE;
			}
			VERIFY(ifscope != IFSCOPE_NONE);
		}

		/*
		 * Transform dst into the internal routing table form,
		 * clearing out the scope ID field if ifscope isn't set.
		 */
		dst = sa_copy(dst, &ss, (ifscope == IFSCOPE_NONE) ?
		    NULL : &ifscope);

		/* Transform netmask into the internal routing table form */
		if (netmask != NULL)
			netmask = ma_copy(af, netmask, &mask, ifscope);

		goto makeroute;

	case RTM_ADD:
		if ((flags & RTF_GATEWAY) && !gateway) {
			panic("rtrequest: RTF_GATEWAY but no gateway");
			/* NOTREACHED */
		}
		if (flags & RTF_IFSCOPE) {
			ifa = ifa_ifwithroute_scoped_locked(flags, dst0,
			    gateway, ifscope);
		} else {
			ifa = ifa_ifwithroute_locked(flags, dst0, gateway);
		}
		if (ifa == NULL)
			senderr(ENETUNREACH);
makeroute:
		/*
		 * We land up here for both RTM_RESOLVE and RTM_ADD
		 * when we decide to create a route.
		 */
		if ((rt = rte_alloc()) == NULL)
			senderr(ENOBUFS);
		Bzero(rt, sizeof(*rt));
		rte_lock_init(rt);
		eventhandler_lists_ctxt_init(&rt->rt_evhdlr_ctxt);
		getmicrotime(&caltime);
		rt->base_calendartime = caltime.tv_sec;
		rt->base_uptime = net_uptime();
		RT_LOCK(rt);
		rt->rt_flags = RTF_UP | flags;

		/*
		 * Point the generation ID to the tree's.
		 */
		switch (af) {
		case AF_INET:
			rt->rt_tree_genid = &route_genid_inet;
			break;
#if INET6
		case AF_INET6:
			rt->rt_tree_genid = &route_genid_inet6;
			break;
#endif /* INET6 */
		default:
			break;
		}

		/*
		 * Add the gateway. Possibly re-malloc-ing the storage for it
		 * also add the rt_gwroute if possible.
		 */
		if ((error = rt_setgate(rt, dst, gateway)) != 0) {
			int tmp = error;
			RT_UNLOCK(rt);
			nstat_route_detach(rt);
			rte_lock_destroy(rt);
			rte_free(rt);
			senderr(tmp);
		}

		/*
		 * point to the (possibly newly malloc'd) dest address.
		 */
		ndst = rt_key(rt);

		/*
		 * make sure it contains the value we want (masked if needed).
		 */
		if (netmask)
			rt_maskedcopy(dst, ndst, netmask);
		else
			Bcopy(dst, ndst, dst->sa_len);

		/*
		 * Note that we now have a reference to the ifa.
		 * This moved from below so that rnh->rnh_addaddr() can
		 * examine the ifa and  ifa->ifa_ifp if it so desires.
		 */
		rtsetifa(rt, ifa);
		rt->rt_ifp = rt->rt_ifa->ifa_ifp;

		/* XXX mtu manipulation will be done in rnh_addaddr -- itojun */

		rn = rnh->rnh_addaddr((caddr_t)ndst, (caddr_t)netmask,
		    rnh, rt->rt_nodes);
		if (rn == 0) {
			struct rtentry *rt2;
			/*
			 * Uh-oh, we already have one of these in the tree.
			 * We do a special hack: if the route that's already
			 * there was generated by the protocol-cloning
			 * mechanism, then we just blow it away and retry
			 * the insertion of the new one.
			 */
			if (flags & RTF_IFSCOPE) {
				rt2 = rtalloc1_scoped_locked(dst0, 0,
				    RTF_CLONING | RTF_PRCLONING, ifscope);
			} else {
				rt2 = rtalloc1_locked(dst, 0,
				    RTF_CLONING | RTF_PRCLONING);
			}
			if (rt2 && rt2->rt_parent) {
				/*
				 * rnh_lock is held here, so rt_key and
				 * rt_gateway of rt2 will not change.
				 */
				(void) rtrequest_locked(RTM_DELETE, rt_key(rt2),
				    rt2->rt_gateway, rt_mask(rt2),
				    rt2->rt_flags, 0);
				rtfree_locked(rt2);
				rn = rnh->rnh_addaddr((caddr_t)ndst,
				    (caddr_t)netmask, rnh, rt->rt_nodes);
			} else if (rt2) {
				/* undo the extra ref we got */
				rtfree_locked(rt2);
			}
		}

		/*
		 * If it still failed to go into the tree,
		 * then un-make it (this should be a function)
		 */
		if (rn == NULL) {
			/* Clear gateway route */
			rt_set_gwroute(rt, rt_key(rt), NULL);
			if (rt->rt_ifa) {
				IFA_REMREF(rt->rt_ifa);
				rt->rt_ifa = NULL;
			}
			R_Free(rt_key(rt));
			RT_UNLOCK(rt);
			nstat_route_detach(rt);
			rte_lock_destroy(rt);
			rte_free(rt);
			senderr(EEXIST);
		}

		rt->rt_parent = NULL;

		/*
		 * If we got here from RESOLVE, then we are cloning so clone
		 * the rest, and note that we are a clone (and increment the
		 * parent's references).  rnh_lock is still held, which prevents
		 * a lookup from returning the newly-created route.  Hence
		 * holding and releasing the parent's rt_lock while still
		 * holding the route's rt_lock is safe since the new route
		 * is not yet externally visible.
		 */
		if (req == RTM_RESOLVE) {
			RT_LOCK_SPIN(*ret_nrt);
			VERIFY((*ret_nrt)->rt_expire == 0 ||
			    (*ret_nrt)->rt_rmx.rmx_expire != 0);
			VERIFY((*ret_nrt)->rt_expire != 0 ||
			    (*ret_nrt)->rt_rmx.rmx_expire == 0);
			rt->rt_rmx = (*ret_nrt)->rt_rmx;
			rt_setexpire(rt, (*ret_nrt)->rt_expire);
			if ((*ret_nrt)->rt_flags &
			    (RTF_CLONING | RTF_PRCLONING)) {
				rt->rt_parent = (*ret_nrt);
				RT_ADDREF_LOCKED(*ret_nrt);
			}
			RT_UNLOCK(*ret_nrt);
		}

		/*
		 * if this protocol has something to add to this then
		 * allow it to do that as well.
		 */
		IFA_LOCK_SPIN(ifa);
		ifa_rtrequest = ifa->ifa_rtrequest;
		IFA_UNLOCK(ifa);
		if (ifa_rtrequest != NULL)
			ifa_rtrequest(req, rt, SA(ret_nrt ? *ret_nrt : NULL));
		IFA_REMREF(ifa);
		ifa = NULL;

		/*
		 * If this is the (non-scoped) default route, record
		 * the interface index used for the primary ifscope.
		 */
		if (rt_primary_default(rt, rt_key(rt))) {
			set_primary_ifscope(rt_key(rt)->sa_family,
			    rt->rt_ifp->if_index);
		}

#if NECP
		/*
		 * If this is a change in a default route, update
		 * necp client watchers to re-evaluate
		 */
		if (SA_DEFAULT(rt_key(rt))) {
			if (rt->rt_ifp != NULL) {
				ifnet_touch_lastupdown(rt->rt_ifp);
			}
			necp_update_all_clients();
		}
#endif /* NECP */

		/*
		 * actually return a resultant rtentry and
		 * give the caller a single reference.
		 */
		if (ret_nrt) {
			*ret_nrt = rt;
			RT_ADDREF_LOCKED(rt);
		}

		if (af == AF_INET)
			routegenid_inet_update();
#if INET6
		else if (af == AF_INET6)
			routegenid_inet6_update();
#endif /* INET6 */

		RT_GENID_SYNC(rt);

		/*
		 * We repeat the same procedures from rt_setgate() here
		 * because they weren't completed when we called it earlier,
		 * since the node was embryonic.
		 */
		if ((rt->rt_flags & RTF_GATEWAY) && rt->rt_gwroute != NULL)
			rt_set_gwroute(rt, rt_key(rt), rt->rt_gwroute);

		if (req == RTM_ADD &&
		    !(rt->rt_flags & RTF_HOST) && rt_mask(rt) != NULL) {
			struct rtfc_arg arg;
			arg.rnh = rnh;
			arg.rt0 = rt;
			RT_UNLOCK(rt);
			rnh->rnh_walktree_from(rnh, rt_key(rt), rt_mask(rt),
			    rt_fixchange, &arg);
		} else {
			RT_UNLOCK(rt);
		}

		nstat_route_new_entry(rt);
		break;
	}
bad:
	if (ifa)
		IFA_REMREF(ifa);
	return (error);
}