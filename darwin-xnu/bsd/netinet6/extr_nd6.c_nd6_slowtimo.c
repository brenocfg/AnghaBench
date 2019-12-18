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
struct nd_ifinfo {scalar_t__ initialized; scalar_t__ recalctm; int /*<<< orphan*/  lock; scalar_t__ basereachable; int /*<<< orphan*/  reachable; } ;
struct TYPE_3__ {struct ifnet* tqe_next; } ;
struct ifnet {TYPE_1__ if_link; } ;
struct TYPE_4__ {struct ifnet* tqh_first; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ND6_SLOWTIMER_INTERVAL ; 
 int /*<<< orphan*/  ND_COMPUTE_RTIME (scalar_t__) ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 scalar_t__ hz ; 
 TYPE_2__ ifnet_head ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nd6_recalc_reachtm_interval ; 
 int /*<<< orphan*/  timeout (void (*) (void*),int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
nd6_slowtimo(void *arg)
{
#pragma unused(arg)
	struct nd_ifinfo *nd6if = NULL;
	struct ifnet *ifp = NULL;

	ifnet_head_lock_shared();
	for (ifp = ifnet_head.tqh_first; ifp;
	    ifp = ifp->if_link.tqe_next) {
		nd6if = ND_IFINFO(ifp);
		if ((NULL == nd6if) || (FALSE == nd6if->initialized)) {
			continue;
		}

		lck_mtx_lock(&nd6if->lock);
		if (nd6if->basereachable && /* already initialized */
		    (nd6if->recalctm -= ND6_SLOWTIMER_INTERVAL) <= 0) {
			/*
			 * Since reachable time rarely changes by router
			 * advertisements, we SHOULD insure that a new random
			 * value gets recomputed at least once every few hours.
			 * (RFC 4861, 6.3.4)
			 */
			nd6if->recalctm = nd6_recalc_reachtm_interval;
			nd6if->reachable =
			    ND_COMPUTE_RTIME(nd6if->basereachable);
		}
		lck_mtx_unlock(&nd6if->lock);
	}
	ifnet_head_done();
	timeout(nd6_slowtimo, NULL, ND6_SLOWTIMER_INTERVAL * hz);
}