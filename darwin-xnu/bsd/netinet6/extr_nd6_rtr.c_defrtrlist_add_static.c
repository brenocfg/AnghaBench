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
struct nd_defrouter {int rtlifetime; int stateflags; int err; int /*<<< orphan*/  ifp; int /*<<< orphan*/  rtaddr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int NDDRF_STATIC ; 
 int /*<<< orphan*/  NDDR_REMREF (struct nd_defrouter*) ; 
 int /*<<< orphan*/  ND_RA_FLAG_RTPREF_MASK ; 
 struct nd_defrouter* defrouter_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nd_defrouter* defrtrlist_update (struct nd_defrouter*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 

int
defrtrlist_add_static(struct nd_defrouter *new)
{
	struct nd_defrouter *dr;
	int err = 0;

	new->rtlifetime = -1;
	new->stateflags |= NDDRF_STATIC;

	/* we only want the preference level */
	new->flags &= ND_RA_FLAG_RTPREF_MASK;

	lck_mtx_lock(nd6_mutex);
	dr = defrouter_lookup(&new->rtaddr, new->ifp);
	if (dr != NULL && !(dr->stateflags & NDDRF_STATIC)) {
		err = EINVAL;
	} else {
		if (dr != NULL)
			NDDR_REMREF(dr);
		dr = defrtrlist_update(new);
		if (dr != NULL)
			err = dr->err;
		else
			err = ENOMEM;
	}
	if (dr != NULL)
		NDDR_REMREF(dr);
	lck_mtx_unlock(nd6_mutex);

	return (err);
}