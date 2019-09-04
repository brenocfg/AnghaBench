#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct rtentry {int rt_flags; TYPE_1__* rt_ifp; int /*<<< orphan*/  rt_ifa; } ;
struct radix_node_head {struct radix_node* (* rnh_matchaddr ) (struct sockaddr*,struct radix_node_head*) ;} ;
struct radix_node {int rn_flags; } ;
typedef  int boolean_t ;
struct TYPE_4__ {unsigned int if_index; } ;
struct TYPE_3__ {int if_flags; unsigned int if_index; } ;

/* Variables and functions */
 int AF_INET ; 
 scalar_t__ FALSE ; 
 int IFF_LOOPBACK ; 
 unsigned int IFSCOPE_NONE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int RNF_ROOT ; 
 struct rtentry* RT (struct radix_node*) ; 
 int RTF_CONDEMNED ; 
 int RTF_GATEWAY ; 
 int RTF_IFSCOPE ; 
 int /*<<< orphan*/  RT_ADDREF_LOCKED (struct rtentry*) ; 
 scalar_t__ RT_HOST (struct radix_node*) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 scalar_t__ SA_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 unsigned int get_primary_ifscope (int) ; 
 TYPE_2__* lo_ifp ; 
 struct sockaddr* ma_copy (int,struct sockaddr*,struct sockaddr_storage*,unsigned int) ; 
 struct radix_node* node_lookup (struct sockaddr*,struct sockaddr*,unsigned int) ; 
 struct radix_node* node_lookup_default (int) ; 
 int /*<<< orphan*/  rnh_lock ; 
 scalar_t__ rt_ifa_is_dst (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 scalar_t__ rt_validate (struct rtentry*) ; 
 struct sockaddr* sa_copy (struct sockaddr*,struct sockaddr_storage*,unsigned int*) ; 
 struct radix_node* stub1 (struct sockaddr*,struct radix_node_head*) ; 

__attribute__((used)) static struct rtentry *
rt_lookup_common(boolean_t lookup_only, boolean_t coarse, struct sockaddr *dst,
    struct sockaddr *netmask, struct radix_node_head *rnh, unsigned int ifscope)
{
	struct radix_node *rn0, *rn = NULL;
	int af = dst->sa_family;
	struct sockaddr_storage dst_ss;
	struct sockaddr_storage mask_ss;
	boolean_t dontcare;
#if (DEVELOPMENT || DEBUG)
	char dbuf[MAX_SCOPE_ADDR_STR_LEN], gbuf[MAX_IPv6_STR_LEN];
	char s_dst[MAX_IPv6_STR_LEN], s_netmask[MAX_IPv6_STR_LEN];
#endif
	VERIFY(!coarse || ifscope == IFSCOPE_NONE);

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);
#if INET6
	/*
	 * While we have rnh_lock held, see if we need to schedule the timer.
	 */
	if (nd6_sched_timeout_want)
		nd6_sched_timeout(NULL, NULL);
#endif /* INET6 */

	if (!lookup_only)
		netmask = NULL;

	/*
	 * Non-scoped route lookup.
	 */
#if INET6
	if (af != AF_INET && af != AF_INET6) {
#else
	if (af != AF_INET) {
#endif /* !INET6 */
		rn = rnh->rnh_matchaddr(dst, rnh);

		/*
		 * Don't return a root node; also, rnh_matchaddr callback
		 * would have done the necessary work to clear RTPRF_OURS
		 * for certain protocol families.
		 */
		if (rn != NULL && (rn->rn_flags & RNF_ROOT))
			rn = NULL;
		if (rn != NULL) {
			RT_LOCK_SPIN(RT(rn));
			if (!(RT(rn)->rt_flags & RTF_CONDEMNED)) {
				RT_ADDREF_LOCKED(RT(rn));
				RT_UNLOCK(RT(rn));
			} else {
				RT_UNLOCK(RT(rn));
				rn = NULL;
			}
		}
		return (RT(rn));
	}

	/* Transform dst/netmask into the internal routing table form */
	dst = sa_copy(dst, &dst_ss, &ifscope);
	if (netmask != NULL)
		netmask = ma_copy(af, netmask, &mask_ss, ifscope);
	dontcare = (ifscope == IFSCOPE_NONE);

#if (DEVELOPMENT || DEBUG)
	if (rt_verbose) {
		if (af == AF_INET)
			(void) inet_ntop(af, &SIN(dst)->sin_addr.s_addr,
			    s_dst, sizeof (s_dst));
		else
			(void) inet_ntop(af, &SIN6(dst)->sin6_addr,
			    s_dst, sizeof (s_dst));

		if (netmask != NULL && af == AF_INET)
			(void) inet_ntop(af, &SIN(netmask)->sin_addr.s_addr,
			    s_netmask, sizeof (s_netmask));
		if (netmask != NULL && af == AF_INET6)
			(void) inet_ntop(af, &SIN6(netmask)->sin6_addr,
			    s_netmask, sizeof (s_netmask));
		else
			*s_netmask = '\0';
		printf("%s (%d, %d, %s, %s, %u)\n",
		    __func__, lookup_only, coarse, s_dst, s_netmask, ifscope);
	}
#endif

	/*
	 * Scoped route lookup:
	 *
	 * We first perform a non-scoped lookup for the original result.
	 * Afterwards, depending on whether or not the caller has specified
	 * a scope, we perform a more specific scoped search and fallback
	 * to this original result upon failure.
	 */
	rn0 = rn = node_lookup(dst, netmask, IFSCOPE_NONE);

	/*
	 * If the caller did not specify a scope, use the primary scope
	 * derived from the system's non-scoped default route.  If, for
	 * any reason, there is no primary interface, ifscope will be
	 * set to IFSCOPE_NONE; if the above lookup resulted in a route,
	 * we'll do a more-specific search below, scoped to the interface
	 * of that route.
	 */
	if (dontcare)
		ifscope = get_primary_ifscope(af);

	/*
	 * Keep the original result if either of the following is true:
	 *
	 *   1) The interface portion of the route has the same interface
	 *	index as the scope value and it is marked with RTF_IFSCOPE.
	 *   2) The route uses the loopback interface, in which case the
	 *	destination (host/net) is local/loopback.
	 *
	 * Otherwise, do a more specified search using the scope;
	 * we're holding rnh_lock now, so rt_ifp should not change.
	 */
	if (rn != NULL) {
		struct rtentry *rt = RT(rn);
#if (DEVELOPMENT || DEBUG)
		if (rt_verbose) {
			rt_str(rt, dbuf, sizeof (dbuf), gbuf, sizeof (gbuf));
			printf("%s unscoped search %p to %s->%s->%s ifa_ifp %s\n",
			    __func__, rt,
			    dbuf, gbuf,
			    (rt->rt_ifp != NULL) ? rt->rt_ifp->if_xname : "",
			    (rt->rt_ifa->ifa_ifp != NULL) ?
			    rt->rt_ifa->ifa_ifp->if_xname : "");
		}
#endif
		if (!(rt->rt_ifp->if_flags & IFF_LOOPBACK) ||
		    (rt->rt_flags & RTF_GATEWAY)) {
			if (rt->rt_ifp->if_index != ifscope) {
				/*
				 * Wrong interface; keep the original result
				 * only if the caller did not specify a scope,
				 * and do a more specific scoped search using
				 * the scope of the found route.  Otherwise,
				 * start again from scratch.
				 *
				 * For loopback scope we keep the unscoped
				 * route for local addresses
				 */
				rn = NULL;
				if (dontcare)
					ifscope = rt->rt_ifp->if_index;
				else if (ifscope != lo_ifp->if_index ||
				    rt_ifa_is_dst(dst, rt->rt_ifa) == FALSE)
					rn0 = NULL;
			} else if (!(rt->rt_flags & RTF_IFSCOPE)) {
				/*
				 * Right interface, except that this route
				 * isn't marked with RTF_IFSCOPE.  Do a more
				 * specific scoped search.  Keep the original
				 * result and return it it in case the scoped
				 * search fails.
				 */
				rn = NULL;
			}
		}
	}

	/*
	 * Scoped search.  Find the most specific entry having the same
	 * interface scope as the one requested.  The following will result
	 * in searching for the longest prefix scoped match.
	 */
	if (rn == NULL) {
		rn = node_lookup(dst, netmask, ifscope);
#if (DEVELOPMENT || DEBUG)
		if (rt_verbose && rn != NULL) {
			struct rtentry *rt = RT(rn);

			rt_str(rt, dbuf, sizeof (dbuf), gbuf, sizeof (gbuf));
			printf("%s scoped search %p to %s->%s->%s ifa %s\n",
			    __func__, rt,
			    dbuf, gbuf,
			    (rt->rt_ifp != NULL) ? rt->rt_ifp->if_xname : "",
			    (rt->rt_ifa->ifa_ifp != NULL) ?
			    rt->rt_ifa->ifa_ifp->if_xname : "");
		}
#endif
	}
	/*
	 * Use the original result if either of the following is true:
	 *
	 *   1) The scoped search did not yield any result.
	 *   2) The caller insists on performing a coarse-grained lookup.
	 *   3) The result from the scoped search is a scoped default route,
	 *	and the original (non-scoped) result is not a default route,
	 *	i.e. the original result is a more specific host/net route.
	 *   4)	The scoped search yielded a net route but the original
	 *	result is a host route, i.e. the original result is treated
	 *	as a more specific route.
	 */
	if (rn == NULL || coarse || (rn0 != NULL &&
	    ((SA_DEFAULT(rt_key(RT(rn))) && !SA_DEFAULT(rt_key(RT(rn0)))) ||
	    (!RT_HOST(rn) && RT_HOST(rn0)))))
		rn = rn0;

	/*
	 * If we still don't have a route, use the non-scoped default
	 * route as long as the interface portion satistifes the scope.
	 */
	if (rn == NULL && (rn = node_lookup_default(af)) != NULL &&
	    RT(rn)->rt_ifp->if_index != ifscope) {
		rn = NULL;
	}

	if (rn != NULL) {
		/*
		 * Manually clear RTPRF_OURS using rt_validate() and
		 * bump up the reference count after, and not before;
		 * we only get here for AF_INET/AF_INET6.  node_lookup()
		 * has done the check against RNF_ROOT, so we can be sure
		 * that we're not returning a root node here.
		 */
		RT_LOCK_SPIN(RT(rn));
		if (rt_validate(RT(rn))) {
			RT_ADDREF_LOCKED(RT(rn));
			RT_UNLOCK(RT(rn));
		} else {
			RT_UNLOCK(RT(rn));
			rn = NULL;
		}
	}
#if (DEVELOPMENT || DEBUG)
	if (rt_verbose) {
		if (rn == NULL)
			printf("%s %u return NULL\n", __func__, ifscope);
		else {
			struct rtentry *rt = RT(rn);

			rt_str(rt, dbuf, sizeof (dbuf), gbuf, sizeof (gbuf));

			printf("%s %u return %p to %s->%s->%s ifa_ifp %s\n",
			    __func__, ifscope, rt,
			    dbuf, gbuf,
			    (rt->rt_ifp != NULL) ? rt->rt_ifp->if_xname : "",
			    (rt->rt_ifa->ifa_ifp != NULL) ?
			    rt->rt_ifa->ifa_ifp->if_xname : "");
		}
	}
#endif
	return (RT(rn));
}