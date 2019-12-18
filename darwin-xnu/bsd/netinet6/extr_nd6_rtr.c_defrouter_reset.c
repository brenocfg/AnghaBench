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
struct nd_defrouter {int stateflags; int /*<<< orphan*/  nddr_lock; } ;
typedef  int /*<<< orphan*/  drany ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int NDDRF_INSTALLED ; 
 int /*<<< orphan*/  NDDR_ADDREF_LOCKED (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_LOCK (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_REMREF (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_UNLOCK (struct nd_defrouter*) ; 
 struct nd_defrouter* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct nd_defrouter* TAILQ_NEXT (struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct nd_defrouter*,int) ; 
 int /*<<< orphan*/  defrouter_delreq (struct nd_defrouter*) ; 
 int /*<<< orphan*/  dr_entry ; 
 int /*<<< orphan*/  ifa_mtx_attr ; 
 int /*<<< orphan*/  ifa_mtx_grp ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd_defrouter ; 

void
defrouter_reset(void)
{
	struct nd_defrouter *dr, drany;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);

	dr = TAILQ_FIRST(&nd_defrouter);
	while (dr) {
		NDDR_LOCK(dr);
		if (dr->stateflags & NDDRF_INSTALLED) {
			NDDR_ADDREF_LOCKED(dr);
			NDDR_UNLOCK(dr);
			lck_mtx_unlock(nd6_mutex);
			defrouter_delreq(dr);
			lck_mtx_lock(nd6_mutex);
			NDDR_REMREF(dr);
			dr = TAILQ_FIRST(&nd_defrouter);
		} else {
			NDDR_UNLOCK(dr);
			dr = TAILQ_NEXT(dr, dr_entry);
		}
	}

	/* Nuke primary (non-scoped) default router */
	bzero(&drany, sizeof (drany));
	lck_mtx_init(&drany.nddr_lock, ifa_mtx_grp, ifa_mtx_attr);
	lck_mtx_unlock(nd6_mutex);
	defrouter_delreq(&drany);
	lck_mtx_destroy(&drany.nddr_lock, ifa_mtx_grp);
	lck_mtx_lock(nd6_mutex);
}