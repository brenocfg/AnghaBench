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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct rtentry {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ nd6_is_new_addr_neighbor (struct sockaddr_in6*,struct ifnet*) ; 
 struct rtentry* nd6_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifnet*,int) ; 
 int /*<<< orphan*/  nd6_mutex ; 

int
nd6_is_addr_neighbor(struct sockaddr_in6 *addr, struct ifnet *ifp,
    int rt_locked)
{
	struct rtentry *rt;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);
	lck_mtx_lock(nd6_mutex);
	if (nd6_is_new_addr_neighbor(addr, ifp)) {
		lck_mtx_unlock(nd6_mutex);
		return (1);
	}
	lck_mtx_unlock(nd6_mutex);

	/*
	 * Even if the address matches none of our addresses, it might be
	 * in the neighbor cache.
	 */
	if ((rt = nd6_lookup(&addr->sin6_addr, 0, ifp, rt_locked)) != NULL) {
		RT_LOCK_ASSERT_HELD(rt);
		RT_REMREF_LOCKED(rt);
		RT_UNLOCK(rt);
		return (1);
	}

	return (0);
}