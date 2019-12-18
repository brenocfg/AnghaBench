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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_family; } ;
struct sockaddr {int dummy; } ;
struct rtentry {int dummy; } ;
struct nd_prefix {int ndpr_stateflags; int ndpr_plen; scalar_t__ ndpr_prproxy_sols_cnt; int /*<<< orphan*/  ndpr_prproxy_sols; struct rtentry* ndpr_rt; struct sockaddr_in6 ndpr_prefix; int /*<<< orphan*/  ndpr_mask; struct ifnet* ndpr_ifp; } ;
struct in6_addr {int dummy; } ;
struct ifnet {unsigned int if_index; } ;
typedef  int /*<<< orphan*/  sa6 ;
typedef  int /*<<< orphan*/  mask6 ;

/* Variables and functions */
 void* AF_INET6 ; 
 int EEXIST ; 
 unsigned int IFSCOPE_NONE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NDPRF_IFSCOPE ; 
 int NDPRF_ONLINK ; 
 int NDPRF_PRPROXY ; 
 int /*<<< orphan*/  NDPR_ADDREF_LOCKED (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_REMREF (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int RB_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ip6_sprintf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6_prproxy_prelist_update (struct nd_prefix*,struct nd_prefix*) ; 
 int /*<<< orphan*/  nd6_prproxy_sols_reap (struct nd_prefix*) ; 
 int /*<<< orphan*/  nd6_rtmsg (int /*<<< orphan*/ ,struct rtentry*) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proxy6_lock ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 
 int rtrequest_scoped (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ,struct rtentry**,unsigned int) ; 

int
nd6_prefix_offlink(struct nd_prefix *pr)
{
	int plen, error = 0, prproxy;
	struct ifnet *ifp = pr->ndpr_ifp;
	struct sockaddr_in6 sa6, mask6, prefix;
	struct rtentry *rt = NULL, *ndpr_rt = NULL;
	unsigned int ifscope;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);

	/* sanity check */
	NDPR_LOCK(pr);
	if ((pr->ndpr_stateflags & NDPRF_ONLINK) == 0) {
		nd6log((LOG_ERR,
		    "nd6_prefix_offlink: %s/%d on %s scoped=%d is already "
		    "off-link\n", ip6_sprintf(&pr->ndpr_prefix.sin6_addr),
		    pr->ndpr_plen, if_name(pr->ndpr_ifp),
		    (pr->ndpr_stateflags & NDPRF_IFSCOPE) ? 1 : 0));
		NDPR_UNLOCK(pr);
		return (EEXIST);
	}

	bzero(&sa6, sizeof (sa6));
	sa6.sin6_family = AF_INET6;
	sa6.sin6_len = sizeof (sa6);
	bcopy(&pr->ndpr_prefix.sin6_addr, &sa6.sin6_addr,
	    sizeof (struct in6_addr));
	bzero(&mask6, sizeof (mask6));
	mask6.sin6_family = AF_INET6;
	mask6.sin6_len = sizeof (sa6);
	bcopy(&pr->ndpr_mask, &mask6.sin6_addr, sizeof (struct in6_addr));
	prefix = pr->ndpr_prefix;
	plen = pr->ndpr_plen;
	if ((ndpr_rt = pr->ndpr_rt) != NULL)
		pr->ndpr_rt = NULL;
	NDPR_ADDREF_LOCKED(pr);		/* keep reference for this routine */
	NDPR_UNLOCK(pr);

	ifscope = (pr->ndpr_stateflags & NDPRF_IFSCOPE) ?
	    ifp->if_index : IFSCOPE_NONE;

	error = rtrequest_scoped(RTM_DELETE, (struct sockaddr *)&sa6,
	    NULL, (struct sockaddr *)&mask6, 0, &rt, ifscope);

	if (rt != NULL) {
		/* report the route deletion to the routing socket. */
		RT_LOCK(rt);
		nd6_rtmsg(RTM_DELETE, rt);
		RT_UNLOCK(rt);
		rtfree(rt);

	} else {
		nd6log((LOG_ERR,
		    "nd6_prefix_offlink: failed to delete route: "
		    "%s/%d on %s, scoped %d, (errno = %d)\n",
		    ip6_sprintf(&sa6.sin6_addr), plen, if_name(ifp),
		    (ifscope != IFSCOPE_NONE), error));
	}

	if (ndpr_rt != NULL)
		rtfree(ndpr_rt);

	lck_mtx_lock(&proxy6_lock);

	NDPR_LOCK(pr);
	prproxy = (pr->ndpr_stateflags & NDPRF_PRPROXY);
	VERIFY(!prproxy || !(pr->ndpr_stateflags & NDPRF_IFSCOPE));
	pr->ndpr_stateflags &= ~(NDPRF_ONLINK | NDPRF_IFSCOPE | NDPRF_PRPROXY);
	if (pr->ndpr_prproxy_sols_cnt > 0) {
		VERIFY(prproxy);
		nd6_prproxy_sols_reap(pr);
		VERIFY(pr->ndpr_prproxy_sols_cnt == 0);
		VERIFY(RB_EMPTY(&pr->ndpr_prproxy_sols));
	}
	NDPR_UNLOCK(pr);

	/*
	 * If this was an upstream prefix, find the downstream ones and do
	 * some cleanups.  If this was a downstream prefix, the prefix route
	 * has been removed from the routing table above, but there may be
	 * other tasks to perform.
	 */
	nd6_prproxy_prelist_update(pr, prproxy ? pr : NULL);

	NDPR_REMREF(pr);	/* release reference for this routine */
	lck_mtx_unlock(&proxy6_lock);

	return (error);
}