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
struct sockaddr {int dummy; } ;
struct rtentry {int rt_flags; struct rtentry* rt_parent; struct rtentry* rt_gwroute; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int RTF_ROUTER ; 
 int RTF_WASCLONED ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 scalar_t__ RT_HOST (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 scalar_t__ SA_DEFAULT (struct sockaddr*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  rnh_lock ; 
 struct sockaddr* rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtentry*) ; 

void
rt_set_gwroute(struct rtentry *rt, struct sockaddr *dst, struct rtentry *gwrt)
{
	boolean_t gwrt_isrouter;

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);
	RT_LOCK_ASSERT_HELD(rt);

	if (gwrt != NULL)
		RT_ADDREF(gwrt);	/* for this routine */

	/*
	 * Get rid of existing gateway route; if rt_gwroute is already
	 * set to gwrt, this is slightly redundant (though safe since
	 * we held an extra ref above) but makes the code simpler.
	 */
	if (rt->rt_gwroute != NULL) {
		struct rtentry *ogwrt = rt->rt_gwroute;

		VERIFY(rt != ogwrt);	/* sanity check */
		rt->rt_gwroute = NULL;
		RT_UNLOCK(rt);
		rtfree_locked(ogwrt);
		RT_LOCK(rt);
		VERIFY(rt->rt_gwroute == NULL);
	}

	/*
	 * And associate the new gateway route.
	 */
	if ((rt->rt_gwroute = gwrt) != NULL) {
		RT_ADDREF(gwrt);	/* for rt */

		if (rt->rt_flags & RTF_WASCLONED) {
			/* rt_parent might be NULL if rt is embryonic */
			gwrt_isrouter = (rt->rt_parent != NULL &&
			    SA_DEFAULT(rt_key(rt->rt_parent)) &&
			    !RT_HOST(rt->rt_parent));
		} else {
			gwrt_isrouter = (SA_DEFAULT(dst) && !RT_HOST(rt));
		}

		/* If gwrt points to a default router, mark it accordingly */
		if (gwrt_isrouter && RT_HOST(gwrt) &&
		    !(gwrt->rt_flags & RTF_ROUTER)) {
			RT_LOCK(gwrt);
			gwrt->rt_flags |= RTF_ROUTER;
			RT_UNLOCK(gwrt);
		}

		RT_REMREF(gwrt);	/* for this routine */
	}
}