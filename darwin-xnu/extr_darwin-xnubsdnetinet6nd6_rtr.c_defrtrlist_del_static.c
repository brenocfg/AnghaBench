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
struct nd_defrouter {int stateflags; int /*<<< orphan*/  ifp; int /*<<< orphan*/  rtaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int NDDRF_STATIC ; 
 int /*<<< orphan*/  NDDR_REMREF (struct nd_defrouter*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 struct nd_defrouter* defrouter_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defrtrlist_del (struct nd_defrouter*) ; 
 int /*<<< orphan*/  dr_entry ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd_defrouter ; 

int
defrtrlist_del_static(struct nd_defrouter *new)
{
	struct nd_defrouter *dr;

	lck_mtx_lock(nd6_mutex);
	dr = defrouter_lookup(&new->rtaddr, new->ifp);
	if (dr == NULL || !(dr->stateflags & NDDRF_STATIC)) {
		if (dr != NULL)
			NDDR_REMREF(dr);
		dr = NULL;
	} else {
		TAILQ_REMOVE(&nd_defrouter, dr, dr_entry);
		defrtrlist_del(dr);
		NDDR_REMREF(dr);        /* remove list reference */
		NDDR_REMREF(dr);
	}
	lck_mtx_unlock(nd6_mutex);

	return (dr != NULL ? 0 : EINVAL);
}