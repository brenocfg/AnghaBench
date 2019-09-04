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
typedef  scalar_t__ uint8_t ;
struct tcpcb {int t_mpflags; scalar_t__ t_local_aid; } ;
struct socket {int /*<<< orphan*/  so_flags; } ;
struct mptcp_subf_auth_entry {scalar_t__ msae_laddr_rand; scalar_t__ msae_raddr_rand; scalar_t__ msae_raddr_id; scalar_t__ msae_laddr_id; } ;
struct mptcb {scalar_t__ mpt_state; int /*<<< orphan*/  mpt_subauth_list; int /*<<< orphan*/  mpt_mpte; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mptcp_subf_auth_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ MPTCPS_CLOSED ; 
 scalar_t__ RandomULong () ; 
 int /*<<< orphan*/  SOF_MP_SEC_SUBFLOW ; 
 int TMPF_JOINED_FLOW ; 
 int TMPF_PREESTABLISHED ; 
 int /*<<< orphan*/  mpt_subauth_zone ; 
 int /*<<< orphan*/  mpte_lock_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msae_next ; 
 struct tcpcb* sototcpcb (struct socket*) ; 
 struct mptcp_subf_auth_entry* zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mptcp_attach_to_subf(struct socket *so, struct mptcb *mp_tp,
    uint8_t addr_id)
{
	struct tcpcb *tp = sototcpcb(so);
	struct mptcp_subf_auth_entry *sauth_entry;
	mpte_lock_assert_held(mp_tp->mpt_mpte);

	/*
	 * The address ID of the first flow is implicitly 0.
	 */
	if (mp_tp->mpt_state == MPTCPS_CLOSED) {
		tp->t_local_aid = 0;
	} else {
		tp->t_local_aid = addr_id;
		tp->t_mpflags |= (TMPF_PREESTABLISHED | TMPF_JOINED_FLOW);
		so->so_flags |= SOF_MP_SEC_SUBFLOW;
	}
	sauth_entry = zalloc(mpt_subauth_zone);
	sauth_entry->msae_laddr_id = tp->t_local_aid;
	sauth_entry->msae_raddr_id = 0;
	sauth_entry->msae_raddr_rand = 0;
try_again:
	sauth_entry->msae_laddr_rand = RandomULong();
	if (sauth_entry->msae_laddr_rand == 0)
		goto try_again;
	LIST_INSERT_HEAD(&mp_tp->mpt_subauth_list, sauth_entry, msae_next);
}