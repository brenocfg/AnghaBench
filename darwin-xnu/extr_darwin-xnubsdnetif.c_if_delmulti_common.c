#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; } ;
struct ifnet {int /*<<< orphan*/  if_multiaddrs; } ;
struct ifmultiaddr {int ifma_flags; scalar_t__ ifma_anoncnt; int ifma_debug; scalar_t__ ifma_reqcnt; TYPE_1__* ifma_addr; struct ifmultiaddr* ifma_ll; struct ifnet* ifma_ifp; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 scalar_t__ AF_UNSPEC ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int IFD_ATTACHED ; 
 int IFMAF_ANONYMOUS ; 
 int /*<<< orphan*/  IFMA_ADDREF_LOCKED (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_LOCK (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_LOCK_ASSERT_HELD (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_REMREF (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_UNLOCK (struct ifmultiaddr*) ; 
 struct ifmultiaddr* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct ifmultiaddr* LIST_NEXT (struct ifmultiaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  RTM_DELMADDR ; 
 int /*<<< orphan*/  SIOCDELMULTI ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct sockaddr* copy_and_normalize (struct sockaddr const*) ; 
 int if_detach_ifma (struct ifnet*,struct ifmultiaddr*,int) ; 
 int /*<<< orphan*/  ifa_equal (struct sockaddr const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ifma_link ; 
 int /*<<< orphan*/  ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  rt_newmaddrmsg (int /*<<< orphan*/ ,struct ifmultiaddr*) ; 

__attribute__((used)) static int
if_delmulti_common(struct ifmultiaddr *ifma, struct ifnet *ifp,
    const struct sockaddr *sa, int anon)
{
	struct sockaddr		*dupsa = NULL;
	int			lastref, ll_lastref = 0, lladdr;
	struct ifmultiaddr	*ll = NULL;

	/* sanity check for callers */
	VERIFY(ifma != NULL || (ifp != NULL && sa != NULL));

	if (ifma != NULL)
		ifp = ifma->ifma_ifp;

	if (sa != NULL &&
	    (sa->sa_family == AF_LINK || sa->sa_family == AF_UNSPEC)) {
		dupsa = copy_and_normalize(sa);
		if (dupsa == NULL)
			return (ENOMEM);
		sa = dupsa;
	}

	ifnet_lock_exclusive(ifp);
	if (ifma == NULL) {
		for (ifma = LIST_FIRST(&ifp->if_multiaddrs); ifma != NULL;
		    ifma = LIST_NEXT(ifma, ifma_link)) {
			IFMA_LOCK(ifma);
			if (!ifa_equal(sa, ifma->ifma_addr) ||
			    (anon && !(ifma->ifma_flags & IFMAF_ANONYMOUS))) {
				VERIFY(!(ifma->ifma_flags & IFMAF_ANONYMOUS) ||
				    ifma->ifma_anoncnt != 0);
				IFMA_UNLOCK(ifma);
				continue;
			}
			/* found; keep it locked */
			break;
		}
		if (ifma == NULL) {
			if (dupsa != NULL)
				FREE(dupsa, M_IFADDR);
			ifnet_lock_done(ifp);
			return (ENOENT);
		}
	} else {
		IFMA_LOCK(ifma);
	}
	IFMA_LOCK_ASSERT_HELD(ifma);
	IFMA_ADDREF_LOCKED(ifma);	/* for this routine */
	lastref = if_detach_ifma(ifp, ifma, anon);
	VERIFY(!lastref || (!(ifma->ifma_debug & IFD_ATTACHED) &&
	    ifma->ifma_reqcnt == 0));
	VERIFY(!anon || ifma->ifma_ll == NULL);
	ll = ifma->ifma_ll;
	lladdr = (ifma->ifma_addr->sa_family == AF_UNSPEC ||
	    ifma->ifma_addr->sa_family == AF_LINK);
	IFMA_UNLOCK(ifma);
	if (lastref && ll != NULL) {
		IFMA_LOCK(ll);
		ll_lastref = if_detach_ifma(ifp, ll, 0);
		IFMA_UNLOCK(ll);
	}
	ifnet_lock_done(ifp);

	if (lastref)
		rt_newmaddrmsg(RTM_DELMADDR, ifma);

	if ((ll == NULL && lastref && lladdr) || ll_lastref) {
		/*
		 * Make sure the interface driver is notified in the
		 * case of a link layer mcast group being left.  Do
		 * this only for a AF_LINK/AF_UNSPEC address that has
		 * been removed from the if_multiaddrs set.
		 */
		ifnet_ioctl(ifp, 0, SIOCDELMULTI, NULL);
	}

	if (lastref)
		IFMA_REMREF(ifma);	/* for if_multiaddrs list */
	if (ll_lastref)
		IFMA_REMREF(ll);	/* for if_multiaddrs list */

	IFMA_REMREF(ifma);		/* for this routine */
	if (dupsa != NULL)
		FREE(dupsa, M_IFADDR);

	return (0);
}