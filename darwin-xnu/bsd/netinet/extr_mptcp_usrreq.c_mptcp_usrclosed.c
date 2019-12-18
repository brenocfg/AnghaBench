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
struct mptses {struct mptcb* mpte_mptcb; } ;
struct mptcb {scalar_t__ mpt_sndnxt; scalar_t__ mpt_sndmax; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPCE_CLOSE ; 
 int /*<<< orphan*/  mptcp_close_fsm (struct mptcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptcp_finish_usrclosed (struct mptses*) ; 

__attribute__((used)) static struct mptses *
mptcp_usrclosed(struct mptses *mpte)
{
	struct mptcb *mp_tp = mpte->mpte_mptcb;

	mptcp_close_fsm(mp_tp, MPCE_CLOSE);

	/* Not everything has been acknowledged - don't close the subflows! */
	if (mp_tp->mpt_sndnxt + 1 != mp_tp->mpt_sndmax)
		return (mpte);

	mptcp_finish_usrclosed(mpte);

	return (mpte);
}