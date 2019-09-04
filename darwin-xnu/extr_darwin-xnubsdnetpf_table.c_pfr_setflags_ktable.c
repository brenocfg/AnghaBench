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
struct pfr_ktable {int pfrkt_flags; struct pfr_ktable* pfrkt_shadow; scalar_t__ pfrkt_cnt; struct pfr_ktable* pfrkt_root; int /*<<< orphan*/ * pfrkt_refcnt; } ;
struct pfr_kentryworkq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 size_t PFR_REFCNT_ANCHOR ; 
 int PFR_TFLAG_ACTIVE ; 
 int PFR_TFLAG_INACTIVE ; 
 int PFR_TFLAG_PERSIST ; 
 int PFR_TFLAG_REFDANCHOR ; 
 int PFR_TFLAG_REFERENCED ; 
 int PFR_TFLAG_SETMASK ; 
 int PFR_TFLAG_USRMASK ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfr_ktable*) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_destroy_ktable (struct pfr_ktable*,int) ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_ktable_cnt ; 
 int /*<<< orphan*/  pfr_ktablehead ; 
 int /*<<< orphan*/  pfr_ktables ; 
 int /*<<< orphan*/  pfr_remove_kentries (struct pfr_ktable*,struct pfr_kentryworkq*) ; 

__attribute__((used)) static void
pfr_setflags_ktable(struct pfr_ktable *kt, int newf)
{
	struct pfr_kentryworkq	addrq;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (!(newf & PFR_TFLAG_REFERENCED) &&
	    !(newf & PFR_TFLAG_PERSIST))
		newf &= ~PFR_TFLAG_ACTIVE;
	if (!(newf & PFR_TFLAG_ACTIVE))
		newf &= ~PFR_TFLAG_USRMASK;
	if (!(newf & PFR_TFLAG_SETMASK)) {
		RB_REMOVE(pfr_ktablehead, &pfr_ktables, kt);
		if (kt->pfrkt_root != NULL)
			if (!--kt->pfrkt_root->pfrkt_refcnt[PFR_REFCNT_ANCHOR])
				pfr_setflags_ktable(kt->pfrkt_root,
				    kt->pfrkt_root->pfrkt_flags &
				    ~PFR_TFLAG_REFDANCHOR);
		pfr_destroy_ktable(kt, 1);
		pfr_ktable_cnt--;
		return;
	}
	if (!(newf & PFR_TFLAG_ACTIVE) && kt->pfrkt_cnt) {
		pfr_enqueue_addrs(kt, &addrq, NULL, 0);
		pfr_remove_kentries(kt, &addrq);
	}
	if (!(newf & PFR_TFLAG_INACTIVE) && kt->pfrkt_shadow != NULL) {
		pfr_destroy_ktable(kt->pfrkt_shadow, 1);
		kt->pfrkt_shadow = NULL;
	}
	kt->pfrkt_flags = newf;
}