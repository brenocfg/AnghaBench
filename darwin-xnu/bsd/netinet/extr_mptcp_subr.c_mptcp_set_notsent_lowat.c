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
struct mptses {struct mptcb* mpte_mptcb; TYPE_1__* mpte_mppcb; } ;
struct mptcb {int mpt_notsent_lowat; } ;
struct TYPE_2__ {int mpp_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int MPP_ATTACHED ; 

int
mptcp_set_notsent_lowat(struct mptses *mpte, int optval)
{
	struct mptcb *mp_tp = NULL;
	int error = 0;

	if (mpte->mpte_mppcb->mpp_flags & MPP_ATTACHED)
		mp_tp = mpte->mpte_mptcb;

	if (mp_tp)
		mp_tp->mpt_notsent_lowat = optval;
	else
		error = EINVAL;

	return (error);
}