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
struct pfr_ktable {scalar_t__* pfrkt_refcnt; int pfrkt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 size_t PFR_REFCNT_RULE ; 
 int PFR_TFLAG_REFERENCED ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_setflags_ktable (struct pfr_ktable*,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

void
pfr_detach_table(struct pfr_ktable *kt)
{
	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (kt->pfrkt_refcnt[PFR_REFCNT_RULE] <= 0)
		printf("pfr_detach_table: refcount = %d.\n",
		    kt->pfrkt_refcnt[PFR_REFCNT_RULE]);
	else if (!--kt->pfrkt_refcnt[PFR_REFCNT_RULE])
		pfr_setflags_ktable(kt, kt->pfrkt_flags&~PFR_TFLAG_REFERENCED);
}