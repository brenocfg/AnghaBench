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
struct lltable {int /*<<< orphan*/  llt_af; struct ifnet* llt_ifp; } ;
struct llentry {int la_flags; int /*<<< orphan*/  lle_timer; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {size_t dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_AFDATA_WLOCK_ASSERT (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LLE_LINKED ; 
 int /*<<< orphan*/  LLE_REMREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 TYPE_1__ arpstat ; 
 scalar_t__ callout_stop (int /*<<< orphan*/ *) ; 
 size_t llentry_free (struct llentry*) ; 
 int /*<<< orphan*/  lltable_unlink_entry (struct lltable*,struct llentry*) ; 

__attribute__((used)) static void
in_lltable_free_entry(struct lltable *llt, struct llentry *lle)
{
	struct ifnet *ifp;
	size_t pkts_dropped;

	LLE_WLOCK_ASSERT(lle);
	KASSERT(llt != NULL, ("lltable is NULL"));

	/* Unlink entry from table if not already */
	if ((lle->la_flags & LLE_LINKED) != 0) {
		ifp = llt->llt_ifp;
		IF_AFDATA_WLOCK_ASSERT(ifp, llt->llt_af);
		lltable_unlink_entry(llt, lle);
	}

#if 0
	/* cancel timer */
	if (callout_stop(&lle->lle_timer) > 0)
		LLE_REMREF(lle);
#endif
	/* Drop hold queue */
	pkts_dropped = llentry_free(lle);
	arpstat.dropped += pkts_dropped;
}