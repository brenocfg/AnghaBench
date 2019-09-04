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
typedef  int /*<<< orphan*/  u_int8_t ;
struct nd_ifinfo {scalar_t__ initialized; int /*<<< orphan*/  lock; int /*<<< orphan*/  randomid; int /*<<< orphan*/  randomseed1; int /*<<< orphan*/  randomseed0; } ;
struct TYPE_3__ {struct ifnet* tqe_next; } ;
struct ifnet {TYPE_1__ if_link; } ;
typedef  int /*<<< orphan*/  nullbuf ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {struct ifnet* tqh_first; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 TYPE_2__ ifnet_head ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  in6_generate_tmp_iid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ip6_desync_factor ; 
 int ip6_temp_preferred_lifetime ; 
 int ip6_temp_regen_advance ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout (void (*) (void*),int /*<<< orphan*/ ,int) ; 

void
in6_tmpaddrtimer(void *arg)
{
#pragma unused(arg)
	struct ifnet *ifp = NULL;
	struct nd_ifinfo *ndi = NULL;
	u_int8_t nullbuf[8];

	timeout(in6_tmpaddrtimer, (caddr_t)0, (ip6_temp_preferred_lifetime -
	    ip6_desync_factor - ip6_temp_regen_advance) * hz);

	bzero(nullbuf, sizeof (nullbuf));
	ifnet_head_lock_shared();
	for (ifp = ifnet_head.tqh_first; ifp;
	    ifp = ifp->if_link.tqe_next) {
		ndi = ND_IFINFO(ifp);
		if ((NULL == ndi) || (FALSE == ndi->initialized)) {
			continue;
		}
		lck_mtx_lock(&ndi->lock);
		if (bcmp(ndi->randomid, nullbuf, sizeof (nullbuf)) != 0) {
			/*
			 * We've been generating a random ID on this interface.
			 * Create a new one.
			 */
			(void) in6_generate_tmp_iid(ndi->randomseed0,
			    ndi->randomseed1, ndi->randomid);
		}
		lck_mtx_unlock(&ndi->lock);
	}
	ifnet_head_done();
}