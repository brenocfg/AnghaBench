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
struct mptses {int /*<<< orphan*/  mpte_sopts; } ;
struct mptopt {int mpo_flags; } ;

/* Variables and functions */
 int MPOF_ATTACHED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mptopt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mpo_entry ; 
 int /*<<< orphan*/  mpte_lock_assert_held (struct mptses*) ; 

void
mptcp_sopt_remove(struct mptses *mpte, struct mptopt *mpo)
{
	mpte_lock_assert_held(mpte);	/* same as MP socket lock */
	VERIFY(mpo->mpo_flags & MPOF_ATTACHED);
	mpo->mpo_flags &= ~MPOF_ATTACHED;
	TAILQ_REMOVE(&mpte->mpte_sopts, mpo, mpo_entry);
}