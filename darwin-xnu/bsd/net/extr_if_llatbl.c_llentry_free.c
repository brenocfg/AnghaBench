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
struct llentry {int la_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LLE_FREE_LOCKED (struct llentry*) ; 
 int LLE_LINKED ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 size_t lltable_drop_entry_queue (struct llentry*) ; 

size_t
llentry_free(struct llentry *lle)
{
	size_t pkts_dropped;

	LLE_WLOCK_ASSERT(lle);

	KASSERT((lle->la_flags & LLE_LINKED) == 0, ("freeing linked lle"));

	pkts_dropped = lltable_drop_entry_queue(lle);

	LLE_FREE_LOCKED(lle);

	return (pkts_dropped);
}