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
struct tcpcb {int t_mpflags; } ;
struct mptcp_dss_ack_opt {int dummy; } ;
struct mptcb {int mpt_flags; int /*<<< orphan*/  mpt_mpte; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int MPTCPF_CHECKSUM ; 
 int TMPF_JOINED_FLOW ; 
 int TMPF_MPTCP_TRUE ; 
 int TMPF_PREESTABLISHED ; 
 int TMPF_SENT_JOIN ; 
 int /*<<< orphan*/  mpte_lock_assert_held (int /*<<< orphan*/ ) ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

int
mptcp_adj_mss(struct tcpcb *tp, boolean_t mtudisc)
{
	int mss_lower = 0;
	struct mptcb *mp_tp = tptomptp(tp);

#define	MPTCP_COMPUTE_LEN {				\
	mss_lower = sizeof (struct mptcp_dss_ack_opt);	\
	if (mp_tp->mpt_flags & MPTCPF_CHECKSUM)		\
		mss_lower += 2;				\
	else						\
		/* adjust to 32-bit boundary + EOL */	\
		mss_lower += 2;				\
}
	if (mp_tp == NULL)
		return (0);

	mpte_lock_assert_held(mp_tp->mpt_mpte);

	/*
	 * For the first subflow and subsequent subflows, adjust mss for
	 * most common MPTCP option size, for case where tcp_mss is called
	 * during option processing and MTU discovery.
	 */
	if (!mtudisc) {
		if (tp->t_mpflags & TMPF_MPTCP_TRUE &&
		    !(tp->t_mpflags & TMPF_JOINED_FLOW)) {
			MPTCP_COMPUTE_LEN;
		}

		if (tp->t_mpflags & TMPF_PREESTABLISHED &&
		    tp->t_mpflags & TMPF_SENT_JOIN) {
			MPTCP_COMPUTE_LEN;
		}
	} else {
		if (tp->t_mpflags & TMPF_MPTCP_TRUE) {
			MPTCP_COMPUTE_LEN;
		}
	}

	return (mss_lower);
}