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
typedef  size_t uint32_t ;
struct lltable {size_t (* llt_hash ) (struct llentry*,int /*<<< orphan*/ ) ;struct llentries* lle_head; int /*<<< orphan*/  llt_hsize; int /*<<< orphan*/  llt_af; int /*<<< orphan*/  llt_ifp; } ;
struct llentry {int la_flags; struct llentries* lle_head; struct lltable* lle_tbl; } ;
struct llentries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_AFDATA_WLOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct llentries*,struct llentry*,int /*<<< orphan*/ ) ; 
 int LLE_LINKED ; 
 int /*<<< orphan*/  lle_next ; 
 size_t stub1 (struct llentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
htable_link_entry(struct lltable *llt, struct llentry *lle)
{
	struct llentries *lleh;
	uint32_t hashidx;

	if ((lle->la_flags & LLE_LINKED) != 0)
		return;

	IF_AFDATA_WLOCK_ASSERT(llt->llt_ifp, llt->llt_af);

	hashidx = llt->llt_hash(lle, llt->llt_hsize);
	lleh = &llt->lle_head[hashidx];

	lle->lle_tbl  = llt;
	lle->lle_head = lleh;
	lle->la_flags |= LLE_LINKED;
	LIST_INSERT_HEAD(lleh, lle, lle_next);
}