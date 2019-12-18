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
struct nd_ifinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; scalar_t__ initialized; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  ND6_IFF_DAD ; 
 int /*<<< orphan*/  ND6_IFF_IFDISABLED ; 
 int /*<<< orphan*/  ND6_IFF_PERFORMNUD ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_ifreset (struct ifnet*) ; 
 int /*<<< orphan*/  nd6_setmtu (struct ifnet*) ; 
 int /*<<< orphan*/  nd6log0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_if_lock_attr ; 
 int /*<<< orphan*/  nd_if_lock_grp ; 

void
nd6_ifattach(struct ifnet *ifp)
{
	struct nd_ifinfo *ndi = ND_IFINFO(ifp);

	VERIFY(NULL != ndi);
	if (!ndi->initialized) {
		lck_mtx_init(&ndi->lock, nd_if_lock_grp, nd_if_lock_attr);
		ndi->flags = ND6_IFF_PERFORMNUD;
		ndi->flags |= ND6_IFF_DAD;
		ndi->initialized = TRUE;
	}

	lck_mtx_lock(&ndi->lock);

	if (!(ifp->if_flags & IFF_MULTICAST)) {
		ndi->flags |= ND6_IFF_IFDISABLED;
	}

	nd6_ifreset(ifp);
	lck_mtx_unlock(&ndi->lock);
	nd6_setmtu(ifp);

	nd6log0((LOG_INFO, ": ",
	    "%s Reinit'd ND information for interface %s\n",
	    if_name(ifp)));
	return;
}