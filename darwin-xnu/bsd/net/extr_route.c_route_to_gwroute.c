#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {scalar_t__ rmx_expire; } ;
struct rtentry {int rt_flags; scalar_t__ rt_expire; TYPE_2__ rt_rmx; struct rtentry* rt_parent; TYPE_3__* rt_gateway; struct rtentry* rt_gwroute; TYPE_1__* rt_ifp; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  sa_len; } ;
struct TYPE_5__ {unsigned int if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHOSTDOWN ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int RTF_GATEWAY ; 
 int RTF_REJECT ; 
 int RTF_UP ; 
 int RTF_WASCLONED ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 int /*<<< orphan*/  RT_ADDREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (TYPE_3__*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equal (struct sockaddr*,TYPE_3__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ net_uptime () ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_revalidate_gwroute (struct rtentry*,struct rtentry*) ; 
 int /*<<< orphan*/  rt_set_gwroute (struct rtentry*,int /*<<< orphan*/ ,struct rtentry*) ; 
 struct rtentry* rtalloc1_scoped (struct sockaddr*,int,int /*<<< orphan*/ ,unsigned int) ; 
 struct rtentry* rtalloc1_scoped_locked (struct sockaddr*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtentry*) ; 
 int /*<<< orphan*/  senderr (int /*<<< orphan*/ ) ; 

errno_t
route_to_gwroute(const struct sockaddr *net_dest, struct rtentry *hint0,
    struct rtentry **out_route)
{
	uint64_t timenow;
	struct rtentry *rt = hint0, *hint = hint0;
	errno_t error = 0;
	unsigned int ifindex;
	boolean_t gwroute;

	*out_route = NULL;

	if (rt == NULL)
		return (0);

	/*
	 * Next hop determination.  Because we may involve the gateway route
	 * in addition to the original route, locking is rather complicated.
	 * The general concept is that regardless of whether the route points
	 * to the original route or to the gateway route, this routine takes
	 * an extra reference on such a route.  This extra reference will be
	 * released at the end.
	 *
	 * Care must be taken to ensure that the "hint0" route never gets freed
	 * via rtfree(), since the caller may have stored it inside a struct
	 * route with a reference held for that placeholder.
	 */
	RT_LOCK_SPIN(rt);
	ifindex = rt->rt_ifp->if_index;
	RT_ADDREF_LOCKED(rt);
	if (!(rt->rt_flags & RTF_UP)) {
		RT_REMREF_LOCKED(rt);
		RT_UNLOCK(rt);
		/* route is down, find a new one */
		hint = rt = rtalloc1_scoped((struct sockaddr *)
		    (size_t)net_dest, 1, 0, ifindex);
		if (hint != NULL) {
			RT_LOCK_SPIN(rt);
			ifindex = rt->rt_ifp->if_index;
		} else {
			senderr(EHOSTUNREACH);
		}
	}

	/*
	 * We have a reference to "rt" by now; it will either
	 * be released or freed at the end of this routine.
	 */
	RT_LOCK_ASSERT_HELD(rt);
	if ((gwroute = (rt->rt_flags & RTF_GATEWAY))) {
		struct rtentry *gwrt = rt->rt_gwroute;
		struct sockaddr_storage ss;
		struct sockaddr *gw = (struct sockaddr *)&ss;

		VERIFY(rt == hint);
		RT_ADDREF_LOCKED(hint);

		/* If there's no gateway rt, look it up */
		if (gwrt == NULL) {
			bcopy(rt->rt_gateway, gw, MIN(sizeof (ss),
			    rt->rt_gateway->sa_len));
			RT_UNLOCK(rt);
			goto lookup;
		}
		/* Become a regular mutex */
		RT_CONVERT_LOCK(rt);

		/*
		 * Take gwrt's lock while holding route's lock;
		 * this is okay since gwrt never points back
		 * to "rt", so no lock ordering issues.
		 */
		RT_LOCK_SPIN(gwrt);
		if (!(gwrt->rt_flags & RTF_UP)) {
			rt->rt_gwroute = NULL;
			RT_UNLOCK(gwrt);
			bcopy(rt->rt_gateway, gw, MIN(sizeof (ss),
			    rt->rt_gateway->sa_len));
			RT_UNLOCK(rt);
			rtfree(gwrt);
lookup:
			lck_mtx_lock(rnh_lock);
			gwrt = rtalloc1_scoped_locked(gw, 1, 0, ifindex);

			RT_LOCK(rt);
			/*
			 * Bail out if the route is down, no route
			 * to gateway, circular route, or if the
			 * gateway portion of "rt" has changed.
			 */
			if (!(rt->rt_flags & RTF_UP) || gwrt == NULL ||
			    gwrt == rt || !equal(gw, rt->rt_gateway)) {
				if (gwrt == rt) {
					RT_REMREF_LOCKED(gwrt);
					gwrt = NULL;
				}
				VERIFY(rt == hint);
				RT_REMREF_LOCKED(hint);
				hint = NULL;
				RT_UNLOCK(rt);
				if (gwrt != NULL)
					rtfree_locked(gwrt);
				lck_mtx_unlock(rnh_lock);
				senderr(EHOSTUNREACH);
			}
			VERIFY(gwrt != NULL);
			/*
			 * Set gateway route; callee adds ref to gwrt;
			 * gwrt has an extra ref from rtalloc1() for
			 * this routine.
			 */
			rt_set_gwroute(rt, rt_key(rt), gwrt);
			VERIFY(rt == hint);
			RT_REMREF_LOCKED(rt);	/* hint still holds a refcnt */
			RT_UNLOCK(rt);
			lck_mtx_unlock(rnh_lock);
			rt = gwrt;
		} else {
			RT_ADDREF_LOCKED(gwrt);
			RT_UNLOCK(gwrt);
			VERIFY(rt == hint);
			RT_REMREF_LOCKED(rt);	/* hint still holds a refcnt */
			RT_UNLOCK(rt);
			rt = gwrt;
		}
		VERIFY(rt == gwrt && rt != hint);

		/*
		 * This is an opportunity to revalidate the parent route's
		 * rt_gwroute, in case it now points to a dead route entry.
		 * Parent route won't go away since the clone (hint) holds
		 * a reference to it.  rt == gwrt.
		 */
		RT_LOCK_SPIN(hint);
		if ((hint->rt_flags & (RTF_WASCLONED | RTF_UP)) ==
		    (RTF_WASCLONED | RTF_UP)) {
			struct rtentry *prt = hint->rt_parent;
			VERIFY(prt != NULL);

			RT_CONVERT_LOCK(hint);
			RT_ADDREF(prt);
			RT_UNLOCK(hint);
			rt_revalidate_gwroute(prt, rt);
			RT_REMREF(prt);
		} else {
			RT_UNLOCK(hint);
		}

		/* Clean up "hint" now; see notes above regarding hint0 */
		if (hint == hint0)
			RT_REMREF(hint);
		else
			rtfree(hint);
		hint = NULL;

		/* rt == gwrt; if it is now down, give up */
		RT_LOCK_SPIN(rt);
		if (!(rt->rt_flags & RTF_UP)) {
			RT_UNLOCK(rt);
			senderr(EHOSTUNREACH);
		}
	}

	if (rt->rt_flags & RTF_REJECT) {
		VERIFY(rt->rt_expire == 0 || rt->rt_rmx.rmx_expire != 0);
		VERIFY(rt->rt_expire != 0 || rt->rt_rmx.rmx_expire == 0);
		timenow = net_uptime();
		if (rt->rt_expire == 0 || timenow < rt->rt_expire) {
			RT_UNLOCK(rt);
			senderr(!gwroute ? EHOSTDOWN : EHOSTUNREACH);
		}
	}

	/* Become a regular mutex */
	RT_CONVERT_LOCK(rt);

	/* Caller is responsible for cleaning up "rt" */
	*out_route = rt;
	return (0);

bad:
	/* Clean up route (either it is "rt" or "gwrt") */
	if (rt != NULL) {
		RT_LOCK_SPIN(rt);
		if (rt == hint0) {
			RT_REMREF_LOCKED(rt);
			RT_UNLOCK(rt);
		} else {
			RT_UNLOCK(rt);
			rtfree(rt);
		}
	}
	return (error);
}