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
struct socket {int so_flags1; } ;
struct mptcb {scalar_t__ mpt_sndnxt; scalar_t__ mpt_sndmax; scalar_t__ mpt_state; scalar_t__ mpt_sndwnd; scalar_t__ mpt_snduna; TYPE_1__* mpt_mpte; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {scalar_t__ mpte_reinjectq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MPTCPS_CLOSE_WAIT ; 
 scalar_t__ MPTCPS_FIN_WAIT_2 ; 
 scalar_t__ MPTCP_SEQ_GEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ MPTCP_SEQ_LEQ (scalar_t__,scalar_t__) ; 
 int SOF1_PRECONNECT_DATA ; 
 int /*<<< orphan*/  TRUE ; 
 struct socket* mptetoso (TYPE_1__*) ; 

boolean_t
mptcp_can_send_more(struct mptcb *mp_tp, boolean_t ignore_reinject)
{
	struct socket *mp_so = mptetoso(mp_tp->mpt_mpte);

	/*
	 * Always send if there is data in the reinject-queue.
	 */
	if (!ignore_reinject && mp_tp->mpt_mpte->mpte_reinjectq)
		return (TRUE);

	/*
	 * Don't send, if:
	 *
	 * 1. snd_nxt >= snd_max : Means, basically everything has been sent.
	 *    Except when using TFO, we might be doing a 0-byte write.
	 * 2. snd_una + snd_wnd <= snd_nxt: No space in the receiver's window
	 * 3. snd_nxt + 1 == snd_max and we are closing: A DATA_FIN is scheduled.
	 */

	if (!(mp_so->so_flags1 & SOF1_PRECONNECT_DATA) && MPTCP_SEQ_GEQ(mp_tp->mpt_sndnxt, mp_tp->mpt_sndmax))
		return (FALSE);

	if (MPTCP_SEQ_LEQ(mp_tp->mpt_snduna + mp_tp->mpt_sndwnd, mp_tp->mpt_sndnxt))
		return (FALSE);

	if (mp_tp->mpt_sndnxt + 1 == mp_tp->mpt_sndmax && mp_tp->mpt_state > MPTCPS_CLOSE_WAIT)
		return (FALSE);

	if (mp_tp->mpt_state >= MPTCPS_FIN_WAIT_2)
		return (FALSE);

	return (TRUE);
}