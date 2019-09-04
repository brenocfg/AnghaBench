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
typedef  int uint32_t ;
struct mppcb {int mpp_flags; int /*<<< orphan*/  mpp_pcbe; int /*<<< orphan*/  mpp_socket; } ;

/* Variables and functions */
 int MPP_SET_CELLICON ; 
 int MPP_SHOULD_RWAKEUP ; 
 int MPP_SHOULD_WORKLOOP ; 
 int MPP_SHOULD_WWAKEUP ; 
 int MPP_UNSET_CELLICON ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mptcp_set_cellicon (int /*<<< orphan*/ ) ; 
 scalar_t__ mptcp_should_defer_upcall (struct mppcb*) ; 
 int /*<<< orphan*/  mptcp_subflow_workloop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptcp_unset_cellicon () ; 
 int /*<<< orphan*/  sorwakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sowwakeup (int /*<<< orphan*/ ) ; 

void
mptcp_handle_deferred_upcalls(struct mppcb *mpp, uint32_t flag)
{
	VERIFY(mpp->mpp_flags & flag);
	mpp->mpp_flags &= ~flag;

	if (mptcp_should_defer_upcall(mpp))
		return;

	if (mpp->mpp_flags & MPP_SHOULD_WORKLOOP) {
		mpp->mpp_flags &= ~MPP_SHOULD_WORKLOOP;

		mptcp_subflow_workloop(mpp->mpp_pcbe);
	}

	if (mpp->mpp_flags & MPP_SHOULD_RWAKEUP) {
		mpp->mpp_flags &= ~MPP_SHOULD_RWAKEUP;

		sorwakeup(mpp->mpp_socket);
	}

	if (mpp->mpp_flags & MPP_SHOULD_WWAKEUP) {
		mpp->mpp_flags &= ~MPP_SHOULD_WWAKEUP;

		sowwakeup(mpp->mpp_socket);
	}

	if (mpp->mpp_flags & MPP_SET_CELLICON) {
		mpp->mpp_flags &= ~MPP_SET_CELLICON;

		mptcp_set_cellicon(mpp->mpp_pcbe);
	}

	if (mpp->mpp_flags & MPP_UNSET_CELLICON) {
		mpp->mpp_flags &= ~MPP_UNSET_CELLICON;

		mptcp_unset_cellicon();
	}
}