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
typedef  scalar_t__ u_char ;
struct rtentry {int rt_flags; struct ifnet* rt_ifp; int /*<<< orphan*/  rt_gateway; } ;
struct in6_addr {int dummy; } ;
struct TYPE_6__ {struct in6_addr sin6_addr; } ;
struct route_in6 {struct rtentry* ro_rt; TYPE_3__ ro_dst; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct nd_prefix {int ndpr_stateflags; scalar_t__ ndpr_plen; struct ifnet* ndpr_ifp; TYPE_1__ ndpr_prefix; struct nd_prefix* ndpr_next; int /*<<< orphan*/  ndpr_mask; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;
typedef  int /*<<< orphan*/  pr_addr ;
struct TYPE_5__ {struct nd_prefix* lh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int /*<<< orphan*/  IN6_ARE_MASKED_ADDR_EQUAL (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NDPRF_IFSCOPE ; 
 int NDPRF_ONLINK ; 
 int NDPRF_PRPROXY ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  ROUTE_RELEASE_LOCKED (struct route_in6*) ; 
 int RTF_CLONING ; 
 int RTF_CONDEMNED ; 
 int RTF_PRCLONING ; 
 int RTF_PROXY ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  SA (TYPE_3__*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  in6_are_prefix_equal (int /*<<< orphan*/ *,struct in6_addr*,scalar_t__) ; 
 int /*<<< orphan*/  ip6_sprintf (struct in6_addr*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6log2 (int /*<<< orphan*/ ) ; 
 TYPE_2__ nd_prefix ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 struct rtentry* rtalloc1_scoped_locked (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtentry*) ; 
 int /*<<< orphan*/  rtrequest_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
nd6_proxy_find_fwdroute(struct ifnet *ifp, struct route_in6 *ro6)
{
	struct in6_addr *dst6 = &ro6->ro_dst.sin6_addr;
	struct ifnet *fwd_ifp = NULL;
	struct nd_prefix *pr;
	struct rtentry *rt;

	if ((rt = ro6->ro_rt) != NULL) {
		RT_LOCK(rt);
		if (!(rt->rt_flags & RTF_PROXY) || rt->rt_ifp == ifp) {
			nd6log2((LOG_DEBUG, "%s: found incorrect prefix "
			    "proxy route for dst %s on %s\n", if_name(ifp),
			    ip6_sprintf(dst6),
			    if_name(rt->rt_ifp)));
			RT_UNLOCK(rt);
			/* look it up below */
		} else {
			RT_UNLOCK(rt);
			/*
			 * The route is already marked with RTF_PRPROXY and
			 * it isn't pointing back to the inbound interface;
			 * optimistically return (see notes below).
			 */
			return;
		}
	}

	/*
	 * Find out where we should forward this packet to, by searching
	 * for another interface that is proxying for the prefix.  Our
	 * current implementation assumes that the proxied prefix is shared
	 * to no more than one downstream interfaces (typically a bridge
	 * interface).
	 */
	lck_mtx_lock(nd6_mutex);
	for (pr = nd_prefix.lh_first; pr; pr = pr->ndpr_next) {
		struct in6_addr pr_addr;
		struct nd_prefix *fwd;
		u_char pr_len;

		NDPR_LOCK(pr);
		if (!(pr->ndpr_stateflags & NDPRF_ONLINK) ||
		    !(pr->ndpr_stateflags & NDPRF_PRPROXY) ||
		    !IN6_ARE_MASKED_ADDR_EQUAL(&pr->ndpr_prefix.sin6_addr,
		    dst6, &pr->ndpr_mask)) {
			NDPR_UNLOCK(pr);
			continue;
		}

		VERIFY(!(pr->ndpr_stateflags & NDPRF_IFSCOPE));
		bcopy(&pr->ndpr_prefix.sin6_addr, &pr_addr, sizeof (pr_addr));
		pr_len = pr->ndpr_plen;
		NDPR_UNLOCK(pr);

		for (fwd = nd_prefix.lh_first; fwd; fwd = fwd->ndpr_next) {
			NDPR_LOCK(fwd);
			if (!(fwd->ndpr_stateflags & NDPRF_ONLINK) ||
			    fwd->ndpr_ifp == ifp ||
			    fwd->ndpr_plen != pr_len ||
			    !in6_are_prefix_equal(&fwd->ndpr_prefix.sin6_addr,
			    &pr_addr, pr_len)) {
				NDPR_UNLOCK(fwd);
				continue;
			}

			fwd_ifp = fwd->ndpr_ifp;
			NDPR_UNLOCK(fwd);
			break;
		}
		break;
	}
	lck_mtx_unlock(nd6_mutex);

	lck_mtx_lock(rnh_lock);
	ROUTE_RELEASE_LOCKED(ro6);

	/*
	 * Lookup a forwarding route; delete the route if it's incorrect,
	 * or return to caller if the correct one got created prior to
	 * our acquiring the rnh_lock.
	 */
	if ((rt = rtalloc1_scoped_locked(SA(&ro6->ro_dst), 0,
	    RTF_CLONING | RTF_PRCLONING, IFSCOPE_NONE)) != NULL) {
		RT_LOCK(rt);
		if (rt->rt_ifp != fwd_ifp || !(rt->rt_flags & RTF_PROXY)) {
			rt->rt_flags |= RTF_CONDEMNED;
			RT_UNLOCK(rt);
			(void) rtrequest_locked(RTM_DELETE, rt_key(rt),
			    rt->rt_gateway, rt_mask(rt), rt->rt_flags, NULL);
			rtfree_locked(rt);
			rt = NULL;
		} else {
			nd6log2((LOG_DEBUG, "%s: found prefix proxy route "
			    "for dst %s\n", if_name(rt->rt_ifp),
			    ip6_sprintf(dst6)));
			RT_UNLOCK(rt);
			ro6->ro_rt = rt;	/* refcnt held by rtalloc1 */
			lck_mtx_unlock(rnh_lock);
			return;
		}
	}
	VERIFY(rt == NULL && ro6->ro_rt == NULL);

	/*
	 * Clone a route from the correct parent prefix route and return it.
	 */
	if (fwd_ifp != NULL && (rt = rtalloc1_scoped_locked(SA(&ro6->ro_dst), 1,
	    RTF_PRCLONING, fwd_ifp->if_index)) != NULL) {
		RT_LOCK(rt);
		if (!(rt->rt_flags & RTF_PROXY)) {
			RT_UNLOCK(rt);
			rtfree_locked(rt);
			rt = NULL;
		} else {
			nd6log2((LOG_DEBUG, "%s: allocated prefix proxy "
			    "route for dst %s\n", if_name(rt->rt_ifp),
			    ip6_sprintf(dst6)));
			RT_UNLOCK(rt);
			ro6->ro_rt = rt;	/* refcnt held by rtalloc1 */
		}
	}
	VERIFY(rt != NULL || ro6->ro_rt == NULL);

	if (fwd_ifp == NULL || rt == NULL) {
		nd6log2((LOG_ERR, "%s: failed to find forwarding prefix "
		    "proxy entry for dst %s\n", if_name(ifp),
		    ip6_sprintf(dst6)));
	}
	lck_mtx_unlock(rnh_lock);
}