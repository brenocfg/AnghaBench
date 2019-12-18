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
typedef  int uint32_t ;
struct socket {int dummy; } ;
struct mptsub {int mpts_evctl; struct mptses* mpts_mpte; } ;
struct mptses {TYPE_1__* mpte_mppcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPP_SHOULD_WORKLOOP ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ mptcp_should_defer_upcall (TYPE_1__*) ; 
 int /*<<< orphan*/  mptcp_subflow_workloop (struct mptses*) ; 
 int /*<<< orphan*/  mpte_lock_assert_held (struct mptses*) ; 

__attribute__((used)) static void
mptcp_subflow_eupcall1(struct socket *so, void *arg, uint32_t events)
{
#pragma unused(so)
	struct mptsub *mpts = arg;
	struct mptses *mpte = mpts->mpts_mpte;

	VERIFY(mpte != NULL);
	mpte_lock_assert_held(mpte);

	if ((mpts->mpts_evctl & events) == events)
		return;

	mpts->mpts_evctl |= events;

	if (mptcp_should_defer_upcall(mpte->mpte_mppcb)) {
		mpte->mpte_mppcb->mpp_flags |= MPP_SHOULD_WORKLOOP;
		return;
	}

	mptcp_subflow_workloop(mpte);
}