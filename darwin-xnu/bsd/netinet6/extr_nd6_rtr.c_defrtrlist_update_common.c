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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct nd_ifinfo {scalar_t__ initialized; scalar_t__ ndefrouters; int /*<<< orphan*/  lock; } ;
struct nd_defrouter {scalar_t__ rtlifetime; int stateflags; int /*<<< orphan*/  err; struct ifnet* ifp; int /*<<< orphan*/  base_uptime; int /*<<< orphan*/  base_calendartime; int /*<<< orphan*/  expire; int /*<<< orphan*/  flags; int /*<<< orphan*/  rtaddr; } ;
struct ifnet {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NDDRF_IFSCOPE ; 
 int /*<<< orphan*/  NDDR_ADDREF (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_LOCK (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_REMREF (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_UNLOCK (struct nd_defrouter*) ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 struct nd_defrouter* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct nd_defrouter*,struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 struct nd_defrouter* TAILQ_NEXT (struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct nd_defrouter* defrouter_lookup (int /*<<< orphan*/ *,struct ifnet*) ; 
 int /*<<< orphan*/  defrouter_select (struct ifnet*) ; 
 int /*<<< orphan*/  defrtrlist_del (struct nd_defrouter*) ; 
 int /*<<< orphan*/  dr_entry ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 scalar_t__ ip6_maxifdefrouters ; 
 int /*<<< orphan*/  ip6_sprintf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nd6_defrouter_genid ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6_sched_timeout_want ; 
 int /*<<< orphan*/  nd6log2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_defrouter ; 
 struct nd_defrouter* nddr_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nddr_free (struct nd_defrouter*) ; 
 int /*<<< orphan*/  net_uptime () ; 
 int rtpref (struct nd_defrouter*) ; 

__attribute__((used)) static struct nd_defrouter *
defrtrlist_update_common(struct nd_defrouter *new, boolean_t scoped)
{
	struct nd_defrouter *dr, *n;
	struct ifnet *ifp = new->ifp;
	struct nd_ifinfo *ndi = NULL;
	struct timeval caltime;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);

	if ((dr = defrouter_lookup(&new->rtaddr, ifp)) != NULL) {
		/* entry exists */
		if (new->rtlifetime == 0) {
			TAILQ_REMOVE(&nd_defrouter, dr, dr_entry);
			defrtrlist_del(dr);
			NDDR_REMREF(dr);        /* remove list reference */
			NDDR_REMREF(dr);
			dr = NULL;
		} else {
			int oldpref = rtpref(dr);
			struct nd_defrouter *p = NULL;
			/* override */
			dr->flags = new->flags; /* xxx flag check */
			dr->rtlifetime = new->rtlifetime;
			dr->expire = new->expire;

			/*
			 * If the preference does not change, there's no need
			 * to sort the entries.  If Scoped Routing is enabled,
			 * put the primary/non-scoped router at the top of the
			 * list of routers in the same preference band, unless
			 * it's already at that position.
			 */
			/* same preference and scoped; just return */
			if (rtpref(new) == oldpref && scoped)
				return (dr);

			n = TAILQ_FIRST(&nd_defrouter);
			while (n != NULL) {
				/* preference changed; sort it */
				if (rtpref(new) != oldpref)
					break;

				/* not at the top of band; sort it */
				if (n != dr && rtpref(n) == oldpref &&
						(!p || rtpref(p) > rtpref(n)))
					break;

				p = n;
				n = TAILQ_NEXT(n, dr_entry);
			}

			/* nothing has changed, just return */
			if (n == NULL && (scoped ||
			    !(dr->stateflags & NDDRF_IFSCOPE)))
				return (dr);

			/*
			 * preferred router may be changed, so relocate
			 * this router.
			 * XXX: calling TAILQ_REMOVE directly is a bad manner.
			 * However, since defrtrlist_del() has many side
			 * effects, we intentionally do so here.
			 * defrouter_select() below will handle routing
			 * changes later.
			 */
			TAILQ_REMOVE(&nd_defrouter, dr, dr_entry);
			new->stateflags = dr->stateflags;

			n = dr;
			goto insert;
		}
		return (dr);
	}

	VERIFY(dr == NULL);

	/* entry does not exist */
	if (new->rtlifetime == 0) {
		return (NULL);
	}

	n = nddr_alloc(M_WAITOK);
	if (n == NULL) {
		return (NULL);
	}

	ndi = ND_IFINFO(ifp);
	VERIFY((NULL != ndi) && (TRUE == ndi->initialized));
	lck_mtx_lock(&ndi->lock);
	if (ip6_maxifdefrouters >= 0 &&
	    ndi->ndefrouters >= ip6_maxifdefrouters) {
		lck_mtx_unlock(&ndi->lock);
		nddr_free(n);
		return (NULL);
	}

	NDDR_ADDREF(n);	/* for the nd_defrouter list */
	NDDR_ADDREF(n);	/* for the caller */

	++nd6_defrouter_genid;
	ndi->ndefrouters++;
	VERIFY(ndi->ndefrouters != 0);
	lck_mtx_unlock(&ndi->lock);

	nd6log2((LOG_INFO, "%s: allocating defrouter %s\n", if_name(ifp),
	    ip6_sprintf(&new->rtaddr)));

	getmicrotime(&caltime);
	NDDR_LOCK(n);
	memcpy(&n->rtaddr, &new->rtaddr, sizeof (n->rtaddr));
	n->flags = new->flags;
	n->stateflags = new->stateflags;
	n->rtlifetime = new->rtlifetime;
	n->expire = new->expire;
	n->base_calendartime = caltime.tv_sec;
	n->base_uptime = net_uptime();
	n->ifp = new->ifp;
	n->err = new->err;
	NDDR_UNLOCK(n);
insert:
	/* get nd6_service() to be scheduled as soon as it's convenient */
	++nd6_sched_timeout_want;

	/*
	 * Insert the new router in the Default Router List;
	 * The Default Router List should be in the descending order
	 * of router-preferece.  When Scoped Routing is disabled, routers
	 * with the same preference are sorted in the arriving time order;
	 * otherwise, the first entry in the list of routers having the same
	 * preference is the primary default router, when the interface used
	 * by the entry is the default interface.
	 */

	/* insert at the end of the group */
	for (dr = TAILQ_FIRST(&nd_defrouter); dr;
	    dr = TAILQ_NEXT(dr, dr_entry)) {
		if (rtpref(n) > rtpref(dr) ||
		    (!scoped && rtpref(n) == rtpref(dr)))
			break;
	}
	if (dr)
		TAILQ_INSERT_BEFORE(dr, n, dr_entry);
	else
		TAILQ_INSERT_TAIL(&nd_defrouter, n, dr_entry);

	defrouter_select(ifp);

	return (n);
}