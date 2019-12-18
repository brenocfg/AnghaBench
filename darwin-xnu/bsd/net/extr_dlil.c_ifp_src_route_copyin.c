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
struct route {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_cached_route_lock; int /*<<< orphan*/  if_src_route; scalar_t__ if_fwd_cacheok; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTE_RELEASE (struct route*) ; 
 int /*<<< orphan*/  lck_mtx_convert_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  route_copyin (struct route*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ifp_src_route_copyin(struct ifnet *ifp, struct route *src)
{
	lck_mtx_lock_spin(&ifp->if_cached_route_lock);
	lck_mtx_convert_spin(&ifp->if_cached_route_lock);

	if (ifp->if_fwd_cacheok) {
		route_copyin(src, &ifp->if_src_route, sizeof (*src));
	} else {
		ROUTE_RELEASE(src);
	}
	lck_mtx_unlock(&ifp->if_cached_route_lock);
}