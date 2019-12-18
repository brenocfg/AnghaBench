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
struct pfr_ktableworkq {int dummy; } ;
struct pfr_ktable {int /*<<< orphan*/  pfrkt_nflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct pfr_ktable* SLIST_FIRST (struct pfr_ktableworkq*) ; 
 struct pfr_ktable* SLIST_NEXT (struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_setflags_ktable (struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfrkt_workq ; 

__attribute__((used)) static void
pfr_setflags_ktables(struct pfr_ktableworkq *workq)
{
	struct pfr_ktable	*p, *q;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	for (p = SLIST_FIRST(workq); p; p = q) {
		q = SLIST_NEXT(p, pfrkt_workq);
		pfr_setflags_ktable(p, p->pfrkt_nflags);
	}
}