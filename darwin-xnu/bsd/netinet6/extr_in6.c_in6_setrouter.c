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
struct nd_ifinfo {int flags; int /*<<< orphan*/  lock; scalar_t__ initialized; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_eflags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFEF_IPV6_ROUTER ; 
 int IFF_LOOPBACK ; 
 int ND6_IFF_PROXY_PREFIXES ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defrouter_select (struct ifnet*) ; 
 int /*<<< orphan*/  if_allmulti (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int in6_autoconf (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_if_prproxy (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nd6_mutex ; 

__attribute__((used)) static __attribute__((noinline)) int
in6_setrouter(struct ifnet *ifp, int enable)
{
	VERIFY(ifp != NULL);

	if (ifp->if_flags & IFF_LOOPBACK)
		return (ENODEV);

	if (enable) {
		struct nd_ifinfo *ndi = NULL;

		ndi = ND_IFINFO(ifp);
		if (ndi != NULL && ndi->initialized) {
			lck_mtx_lock(&ndi->lock);
			if (ndi->flags & ND6_IFF_PROXY_PREFIXES) {
				/* No proxy if we are an advertising router */
				ndi->flags &= ~ND6_IFF_PROXY_PREFIXES;
				lck_mtx_unlock(&ndi->lock);
				(void) nd6_if_prproxy(ifp, FALSE);
			} else {
				lck_mtx_unlock(&ndi->lock);
			}
		}
	}

	ifnet_lock_exclusive(ifp);
	if (enable) {
		ifp->if_eflags |= IFEF_IPV6_ROUTER;
	} else {
		ifp->if_eflags &= ~IFEF_IPV6_ROUTER;
	}
	ifnet_lock_done(ifp);

	lck_mtx_lock(nd6_mutex);
	defrouter_select(ifp);
	lck_mtx_unlock(nd6_mutex);

	if_allmulti(ifp, enable);

	return (in6_autoconf(ifp, FALSE));
}