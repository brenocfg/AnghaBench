#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct sockaddr_in {int sin_len; struct in_addr sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifq_maxlen; } ;
struct in_multi {int inm_reqcnt; int inm_debug; int /*<<< orphan*/  inm_srcs; TYPE_3__* inm_st; TYPE_2__ inm_scq; int /*<<< orphan*/  inm_state; struct ifmultiaddr* inm_ifma; int /*<<< orphan*/ * inm_igi; struct ifnet* inm_ifp; struct in_addr inm_addr; } ;
struct ifnet {int dummy; } ;
struct ifmultiaddr {struct in_multi* ifma_protospec; TYPE_1__* ifma_addr; } ;
typedef  int /*<<< orphan*/  gsin ;
struct TYPE_6__ {void* iss_fmode; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int ENOMEM ; 
 int IFD_ATTACHED ; 
 int IFD_TRASHED ; 
 int /*<<< orphan*/  IFMA_LOCK (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_REMREF (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IFMA_UNLOCK (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  IGI_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IGMP_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  IGMP_MAX_STATE_CHANGES ; 
 int /*<<< orphan*/  IGMP_NOT_MEMBER ; 
 int /*<<< orphan*/  INM_ADDREF (struct in_multi*) ; 
 int /*<<< orphan*/  INM_ADDREF_LOCKED (struct in_multi*) ; 
 int /*<<< orphan*/  INM_LOCK (struct in_multi*) ; 
 int /*<<< orphan*/  INM_UNLOCK (struct in_multi*) ; 
 int /*<<< orphan*/  IN_LOOKUP_MULTI (struct in_addr const*,struct ifnet*,struct in_multi*) ; 
 void* MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int if_addmulti (struct ifnet*,struct sockaddr*,struct ifmultiaddr**) ; 
 int in_hosteq (struct in_addr,struct in_addr const) ; 
 struct in_multi* in_multi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_multi_attach (struct in_multi*) ; 
 int /*<<< orphan*/  in_multihead_lock_done () ; 
 int /*<<< orphan*/  in_multihead_lock_exclusive () ; 
 int /*<<< orphan*/  in_multihead_lock_shared () ; 

__attribute__((used)) static int
in_getmulti(struct ifnet *ifp, const struct in_addr *group,
    struct in_multi **pinm)
{
	struct sockaddr_in	 gsin;
	struct ifmultiaddr	*ifma;
	struct in_multi		*inm;
	int			error;

	in_multihead_lock_shared();
	IN_LOOKUP_MULTI(group, ifp, inm);
	if (inm != NULL) {
		INM_LOCK(inm);
		VERIFY(inm->inm_reqcnt >= 1);
		inm->inm_reqcnt++;
		VERIFY(inm->inm_reqcnt != 0);
		*pinm = inm;
		INM_UNLOCK(inm);
		in_multihead_lock_done();
		/*
		 * We already joined this group; return the inm
		 * with a refcount held (via lookup) for caller.
		 */
		return (0);
	}
	in_multihead_lock_done();

	bzero(&gsin, sizeof(gsin));
	gsin.sin_family = AF_INET;
	gsin.sin_len = sizeof(struct sockaddr_in);
	gsin.sin_addr = *group;

	/*
	 * Check if a link-layer group is already associated
	 * with this network-layer group on the given ifnet.
	 */
	error = if_addmulti(ifp, (struct sockaddr *)&gsin, &ifma);
	if (error != 0)
		return (error);

	/*
	 * See comments in inm_remref() for access to ifma_protospec.
	 */
	in_multihead_lock_exclusive();
	IFMA_LOCK(ifma);
	if ((inm = ifma->ifma_protospec) != NULL) {
		VERIFY(ifma->ifma_addr != NULL);
		VERIFY(ifma->ifma_addr->sa_family == AF_INET);
		INM_ADDREF(inm);	/* for caller */
		IFMA_UNLOCK(ifma);
		INM_LOCK(inm);
		VERIFY(inm->inm_ifma == ifma);
		VERIFY(inm->inm_ifp == ifp);
		VERIFY(in_hosteq(inm->inm_addr, *group));
		if (inm->inm_debug & IFD_ATTACHED) {
			VERIFY(inm->inm_reqcnt >= 1);
			inm->inm_reqcnt++;
			VERIFY(inm->inm_reqcnt != 0);
			*pinm = inm;
			INM_UNLOCK(inm);
			in_multihead_lock_done();
			IFMA_REMREF(ifma);
			/*
			 * We lost the race with another thread doing
			 * in_getmulti(); since this group has already
			 * been joined; return the inm with a refcount
			 * held for caller.
			 */
			return (0);
		}
		/*
		 * We lost the race with another thread doing in_delmulti();
		 * the inm referring to the ifma has been detached, thus we
		 * reattach it back to the in_multihead list and return the
		 * inm with a refcount held for the caller.
		 */
		in_multi_attach(inm);
		VERIFY((inm->inm_debug &
		    (IFD_ATTACHED | IFD_TRASHED)) == IFD_ATTACHED);
		*pinm = inm;
		INM_UNLOCK(inm);
		in_multihead_lock_done();
		IFMA_REMREF(ifma);
		return (0);
	}
	IFMA_UNLOCK(ifma);

	/*
	 * A new in_multi record is needed; allocate and initialize it.
	 * We DO NOT perform an IGMP join as the in_ layer may need to
	 * push an initial source list down to IGMP to support SSM.
	 *
	 * The initial source filter state is INCLUDE, {} as per the RFC.
	 */
	inm = in_multi_alloc(M_WAITOK);
	if (inm == NULL) {
		in_multihead_lock_done();
		IFMA_REMREF(ifma);
		return (ENOMEM);
	}
	INM_LOCK(inm);
	inm->inm_addr = *group;
	inm->inm_ifp = ifp;
	inm->inm_igi = IGMP_IFINFO(ifp);
	VERIFY(inm->inm_igi != NULL);
	IGI_ADDREF(inm->inm_igi);
	inm->inm_ifma = ifma;		/* keep refcount from if_addmulti() */
	inm->inm_state = IGMP_NOT_MEMBER;
	/*
	 * Pending state-changes per group are subject to a bounds check.
	 */
	inm->inm_scq.ifq_maxlen = IGMP_MAX_STATE_CHANGES;
	inm->inm_st[0].iss_fmode = MCAST_UNDEFINED;
	inm->inm_st[1].iss_fmode = MCAST_UNDEFINED;
	RB_INIT(&inm->inm_srcs);
	*pinm = inm;
	in_multi_attach(inm);
	VERIFY((inm->inm_debug & (IFD_ATTACHED | IFD_TRASHED)) == IFD_ATTACHED);
	INM_ADDREF_LOCKED(inm);		/* for caller */
	INM_UNLOCK(inm);

	IFMA_LOCK(ifma);
	VERIFY(ifma->ifma_protospec == NULL);
	ifma->ifma_protospec = inm;
	IFMA_UNLOCK(ifma);
	in_multihead_lock_done();

	return (0);
}