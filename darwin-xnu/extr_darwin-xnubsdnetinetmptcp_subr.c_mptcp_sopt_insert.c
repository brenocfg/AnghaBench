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
struct mptopt {int /*<<< orphan*/  mpo_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPOF_ATTACHED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mptopt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpo_entry ; 
 int /*<<< orphan*/  mpte_lock_assert_held (struct mptses*) ; 

void
mptcp_sopt_insert(struct mptses *mpte, struct mptopt *mpo)
{
	mpte_lock_assert_held(mpte);	/* same as MP socket lock */
	mpo->mpo_flags |= MPOF_ATTACHED;
	TAILQ_INSERT_TAIL(&mpte->mpte_sopts, mpo, mpo_entry);
}