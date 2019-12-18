#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcpcb {int t_rxtshift; } ;
struct mptsub {int /*<<< orphan*/  mpts_socket; } ;
struct mptses {scalar_t__ mpte_svctype; scalar_t__ mpte_reinjectq; } ;
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ sb_cc; } ;
struct TYPE_4__ {TYPE_1__ so_snd; } ;

/* Variables and functions */
 scalar_t__ MPTCP_SVCTYPE_HANDOVER ; 
 int mptcp_fail_thresh ; 
 TYPE_2__* mptetoso (struct mptses*) ; 
 struct tcpcb* sototcpcb (int /*<<< orphan*/ ) ; 

boolean_t
mptcp_subflow_is_bad(struct mptses *mpte, struct mptsub *mpts)
{
	struct tcpcb *tp = sototcpcb(mpts->mpts_socket);
	int fail_thresh = mptcp_fail_thresh;

	if (mpte->mpte_svctype == MPTCP_SVCTYPE_HANDOVER)
		fail_thresh *= 2;

	return (tp->t_rxtshift >= fail_thresh &&
		(mptetoso(mpte)->so_snd.sb_cc || mpte->mpte_reinjectq));
}