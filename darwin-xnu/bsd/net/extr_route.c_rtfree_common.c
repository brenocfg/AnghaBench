#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtentry_dbg {int dummy; } ;
struct rtentry {scalar_t__ rt_refcnt; int rt_flags; int /*<<< orphan*/  rt_evhdlr_ctxt; TYPE_2__* rt_llinfo; int /*<<< orphan*/  (* rt_llinfo_free ) (TYPE_2__*) ;struct ifaddr* rt_ifa; struct rtentry* rt_parent; TYPE_1__* rt_nodes; } ;
struct radix_node_head {int /*<<< orphan*/  (* rnh_close ) (struct radix_node*,struct radix_node_head*) ;} ;
struct radix_node {int dummy; } ;
struct ifaddr {int dummy; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {size_t sa_family; } ;
struct TYPE_5__ {int rn_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int RNF_ACTIVE ; 
 int RNF_ROOT ; 
 int RTD_DEBUG ; 
 int RTF_DEAD ; 
 int RTF_IFREF ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_ADDREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  R_Free (TYPE_2__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rtentry_dbg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  eventhandler_lists_ctxt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstat_route_detach (struct rtentry*) ; 
 int /*<<< orphan*/  panic (char*,struct rtentry*,...) ; 
 int /*<<< orphan*/  rnh_lock ; 
 TYPE_2__* rt_key (struct rtentry*) ; 
 struct radix_node_head** rt_tables ; 
 int /*<<< orphan*/  rtd_trash_link ; 
 int rte_debug ; 
 int /*<<< orphan*/  rte_free (struct rtentry*) ; 
 int /*<<< orphan*/  rte_lock_destroy (struct rtentry*) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtentry*) ; 
 int /*<<< orphan*/  rttrash ; 
 int /*<<< orphan*/  rttrash_head ; 
 scalar_t__ rtunref (struct rtentry*) ; 
 int /*<<< orphan*/  stub1 (struct radix_node*,struct radix_node_head*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void
rtfree_common(struct rtentry *rt, boolean_t locked)
{
	struct radix_node_head *rnh;

	LCK_MTX_ASSERT(rnh_lock, locked ?
	    LCK_MTX_ASSERT_OWNED : LCK_MTX_ASSERT_NOTOWNED);

	/*
	 * Atomically decrement the reference count and if it reaches 0,
	 * and there is a close function defined, call the close function.
	 */
	RT_LOCK_SPIN(rt);
	if (rtunref(rt) > 0) {
		RT_UNLOCK(rt);
		return;
	}

	/*
	 * To avoid violating lock ordering, we must drop rt_lock before
	 * trying to acquire the global rnh_lock.  If we are called with
	 * rnh_lock held, then we already have exclusive access; otherwise
	 * we do the lock dance.
	 */
	if (!locked) {
		/*
		 * Note that we check it again below after grabbing rnh_lock,
		 * since it is possible that another thread doing a lookup wins
		 * the race, grabs the rnh_lock first, and bumps up reference
		 * count in which case the route should be left alone as it is
		 * still in use.  It's also possible that another thread frees
		 * the route after we drop rt_lock; to prevent the route from
		 * being freed, we hold an extra reference.
		 */
		RT_ADDREF_LOCKED(rt);
		RT_UNLOCK(rt);
		lck_mtx_lock(rnh_lock);
		RT_LOCK_SPIN(rt);
		if (rtunref(rt) > 0) {
			/* We've lost the race, so abort */
			RT_UNLOCK(rt);
			goto done;
		}
	}

	/*
	 * We may be blocked on other lock(s) as part of freeing
	 * the entry below, so convert from spin to full mutex.
	 */
	RT_CONVERT_LOCK(rt);

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	/* Negative refcnt must never happen */
	if (rt->rt_refcnt != 0) {
		panic("rt %p invalid refcnt %d", rt, rt->rt_refcnt);
		/* NOTREACHED */
	}
	/* Idle refcnt must have been dropped during rtunref() */
	VERIFY(!(rt->rt_flags & RTF_IFREF));

	/*
	 * find the tree for that address family
	 * Note: in the case of igmp packets, there might not be an rnh
	 */
	rnh = rt_tables[rt_key(rt)->sa_family];

	/*
	 * On last reference give the "close method" a chance to cleanup
	 * private state.  This also permits (for IPv4 and IPv6) a chance
	 * to decide if the routing table entry should be purged immediately
	 * or at a later time.  When an immediate purge is to happen the
	 * close routine typically issues RTM_DELETE which clears the RTF_UP
	 * flag on the entry so that the code below reclaims the storage.
	 */
	if (rnh != NULL && rnh->rnh_close != NULL)
		rnh->rnh_close((struct radix_node *)rt, rnh);

	/*
	 * If we are no longer "up" (and ref == 0) then we can free the
	 * resources associated with the route.
	 */
	if (!(rt->rt_flags & RTF_UP)) {
		struct rtentry *rt_parent;
		struct ifaddr *rt_ifa;

		rt->rt_flags |= RTF_DEAD;
		if (rt->rt_nodes->rn_flags & (RNF_ACTIVE | RNF_ROOT)) {
			panic("rt %p freed while in radix tree\n", rt);
			/* NOTREACHED */
		}
		/*
		 * the rtentry must have been removed from the routing table
		 * so it is represented in rttrash; remove that now.
		 */
		(void) OSDecrementAtomic(&rttrash);
		if (rte_debug & RTD_DEBUG) {
			TAILQ_REMOVE(&rttrash_head, (struct rtentry_dbg *)rt,
			    rtd_trash_link);
		}

		/*
		 * release references on items we hold them on..
		 * e.g other routes and ifaddrs.
		 */
		if ((rt_parent = rt->rt_parent) != NULL)
			rt->rt_parent = NULL;

		if ((rt_ifa = rt->rt_ifa) != NULL)
			rt->rt_ifa = NULL;

		/*
		 * Now free any attached link-layer info.
		 */
		if (rt->rt_llinfo != NULL) {
			if (rt->rt_llinfo_free != NULL)
				(*rt->rt_llinfo_free)(rt->rt_llinfo);
			else
				R_Free(rt->rt_llinfo);
			rt->rt_llinfo = NULL;
		}

		/* Destroy eventhandler lists context */
		eventhandler_lists_ctxt_destroy(&rt->rt_evhdlr_ctxt);

		/*
		 * Route is no longer in the tree and refcnt is 0;
		 * we have exclusive access, so destroy it.
		 */
		RT_UNLOCK(rt);
		rte_lock_destroy(rt);

		if (rt_parent != NULL)
			rtfree_locked(rt_parent);

		if (rt_ifa != NULL)
			IFA_REMREF(rt_ifa);

		/*
		 * The key is separately alloc'd so free it (see rt_setgate()).
		 * This also frees the gateway, as they are always malloc'd
		 * together.
		 */
		R_Free(rt_key(rt));

		/*
		 * Free any statistics that may have been allocated
		 */
		nstat_route_detach(rt);

		/*
		 * and the rtentry itself of course
		 */
		rte_free(rt);
	} else {
		/*
		 * The "close method" has been called, but the route is
		 * still in the radix tree with zero refcnt, i.e. "up"
		 * and in the cached state.
		 */
		RT_UNLOCK(rt);
	}
done:
	if (!locked)
		lck_mtx_unlock(rnh_lock);
}