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
struct tcpcb {TYPE_1__* t_inpcb; int /*<<< orphan*/  snd_wnd; } ;
struct mptcb {int mpt_flags; int /*<<< orphan*/  mpt_snduna; int /*<<< orphan*/  mpt_sndwl2; int /*<<< orphan*/  mpt_rcvnxt; int /*<<< orphan*/  mpt_sndwl1; int /*<<< orphan*/  mpt_sndwnd; int /*<<< orphan*/  mpt_mpte; } ;
struct TYPE_2__ {int /*<<< orphan*/  inp_socket; } ;

/* Variables and functions */
 int MPTCPF_FALLBACK_TO_TCP ; 
 int /*<<< orphan*/  mpte_lock_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sowwakeup (int /*<<< orphan*/ ) ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

void
mptcp_update_window_wakeup(struct tcpcb *tp)
{
	struct mptcb *mp_tp = tptomptp(tp);

	mpte_lock_assert_held(mp_tp->mpt_mpte);

	if (mp_tp->mpt_flags & MPTCPF_FALLBACK_TO_TCP) {
		mp_tp->mpt_sndwnd = tp->snd_wnd;
		mp_tp->mpt_sndwl1 = mp_tp->mpt_rcvnxt;
		mp_tp->mpt_sndwl2 = mp_tp->mpt_snduna;
	}

	sowwakeup(tp->t_inpcb->inp_socket);
}