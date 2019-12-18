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
struct sockaddr_storage {scalar_t__ ss_len; } ;
typedef  struct sockaddr {scalar_t__ sa_family; } const sockaddr ;
struct ifnet {int if_flags; scalar_t__ if_updatemcasts; } ;
struct ifmultiaddr {struct sockaddr const* ifma_addr; struct ifnet* ifma_ifp; struct ifmultiaddr* ifma_ll; } ;
typedef  int /*<<< orphan*/  storage ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 scalar_t__ AF_UNSPEC ; 
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FREE (struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFMA_ADDREF_LOCKED (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_LOCK (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_REMREF (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_UNLOCK (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RTM_NEWMADDR ; 
 int /*<<< orphan*/  SIOCADDMULTI ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct sockaddr const* copy_and_normalize (struct sockaddr const*) ; 
 int dlil_resolve_multi (struct ifnet*,struct sockaddr const*,struct sockaddr const*,int) ; 
 int if_addmulti_doesexist (struct ifnet*,struct sockaddr const*,struct ifmultiaddr**,int) ; 
 int /*<<< orphan*/  if_attach_ifma (struct ifnet*,struct ifmultiaddr*,int) ; 
 struct ifmultiaddr* ifma_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifma_free (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  rt_newmaddrmsg (int /*<<< orphan*/ ,struct ifmultiaddr*) ; 

__attribute__((used)) static int
if_addmulti_common(struct ifnet *ifp, const struct sockaddr *sa,
    struct ifmultiaddr **retifma, int anon)
{
	struct sockaddr_storage storage;
	struct sockaddr *llsa = NULL;
	struct sockaddr *dupsa = NULL;
	int error = 0, ll_firstref = 0, lladdr;
	struct ifmultiaddr *ifma = NULL;
	struct ifmultiaddr *llifma = NULL;

	/* Only AF_UNSPEC/AF_LINK is allowed for an "anonymous" address */
	VERIFY(!anon || sa->sa_family == AF_UNSPEC ||
	    sa->sa_family == AF_LINK);

	/* If sa is a AF_LINK or AF_UNSPEC, duplicate and normalize it */
	if (sa->sa_family == AF_LINK || sa->sa_family == AF_UNSPEC) {
		dupsa = copy_and_normalize(sa);
		if (dupsa == NULL) {
			error = ENOMEM;
			goto cleanup;
		}
		sa = dupsa;
	}

	ifnet_lock_exclusive(ifp);
	if (!(ifp->if_flags & IFF_MULTICAST)) {
		error = EADDRNOTAVAIL;
		ifnet_lock_done(ifp);
		goto cleanup;
	}

	/* If the address is already present, return a new reference to it */
	error = if_addmulti_doesexist(ifp, sa, retifma, anon);
	ifnet_lock_done(ifp);
	if (error == 0)
		goto cleanup;

	/*
	 * The address isn't already present; give the link layer a chance
	 * to accept/reject it, and also find out which AF_LINK address this
	 * maps to, if it isn't one already.
	 */
	error = dlil_resolve_multi(ifp, sa, (struct sockaddr *)&storage,
	    sizeof (storage));
	if (error == 0 && storage.ss_len != 0) {
		llsa = copy_and_normalize((struct sockaddr *)&storage);
		if (llsa == NULL) {
			error = ENOMEM;
			goto cleanup;
		}

		llifma = ifma_alloc(M_WAITOK);
		if (llifma == NULL) {
			error = ENOMEM;
			goto cleanup;
		}
	}

	/* to be similar to FreeBSD */
	if (error == EOPNOTSUPP)
		error = 0;
	else if (error != 0)
		goto cleanup;

	/* Allocate while we aren't holding any locks */
	if (dupsa == NULL) {
		dupsa = copy_and_normalize(sa);
		if (dupsa == NULL) {
			error = ENOMEM;
			goto cleanup;
		}
	}
	ifma = ifma_alloc(M_WAITOK);
	if (ifma == NULL) {
		error = ENOMEM;
		goto cleanup;
	}

	ifnet_lock_exclusive(ifp);
	/*
	 * Check again for the matching multicast.
	 */
	error = if_addmulti_doesexist(ifp, sa, retifma, anon);
	if (error == 0) {
		ifnet_lock_done(ifp);
		goto cleanup;
	}

	if (llifma != NULL) {
		VERIFY(!anon);	/* must not get here if "anonymous" */
		if (if_addmulti_doesexist(ifp, llsa, &ifma->ifma_ll, 0) == 0) {
			FREE(llsa, M_IFADDR);
			llsa = NULL;
			ifma_free(llifma);
			llifma = NULL;
			VERIFY(ifma->ifma_ll->ifma_ifp == ifp);
		} else {
			ll_firstref = 1;
			llifma->ifma_addr = llsa;
			llifma->ifma_ifp = ifp;
			IFMA_LOCK(llifma);
			if_attach_ifma(ifp, llifma, 0);
			/* add extra refcnt for ifma */
			IFMA_ADDREF_LOCKED(llifma);
			IFMA_UNLOCK(llifma);
			ifma->ifma_ll = llifma;
		}
	}

	/* "anonymous" request should not result in network address */
	VERIFY(!anon || ifma->ifma_ll == NULL);

	ifma->ifma_addr = dupsa;
	ifma->ifma_ifp = ifp;
	IFMA_LOCK(ifma);
	if_attach_ifma(ifp, ifma, anon);
	IFMA_ADDREF_LOCKED(ifma);		/* for this routine */
	if (retifma != NULL) {
		*retifma = ifma;
		IFMA_ADDREF_LOCKED(*retifma);	/* for caller */
	}
	lladdr = (ifma->ifma_addr->sa_family == AF_UNSPEC ||
	    ifma->ifma_addr->sa_family == AF_LINK);
	IFMA_UNLOCK(ifma);
	ifnet_lock_done(ifp);

	rt_newmaddrmsg(RTM_NEWMADDR, ifma);
	IFMA_REMREF(ifma);			/* for this routine */

	/*
	 * We are certain we have added something, so call down to the
	 * interface to let them know about it.  Do this only for newly-
	 * added AF_LINK/AF_UNSPEC address in the if_multiaddrs set.
	 */
	if (lladdr || ll_firstref)
		(void) ifnet_ioctl(ifp, 0, SIOCADDMULTI, NULL);

	if (ifp->if_updatemcasts > 0)
		ifp->if_updatemcasts = 0;

	return (0);

cleanup:
	if (ifma != NULL)
		ifma_free(ifma);
	if (dupsa != NULL)
		FREE(dupsa, M_IFADDR);
	if (llifma != NULL)
		ifma_free(llifma);
	if (llsa != NULL)
		FREE(llsa, M_IFADDR);

	return (error);
}