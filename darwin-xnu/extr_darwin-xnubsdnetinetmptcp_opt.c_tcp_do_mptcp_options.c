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
typedef  int u_char ;
struct tcpopt {int /*<<< orphan*/  to_flags; } ;
struct tcphdr {int dummy; } ;
struct tcpcb {int dummy; } ;
struct mptcb {int /*<<< orphan*/  mpt_mpte; } ;

/* Variables and functions */
#define  MPO_ADD_ADDR 135 
#define  MPO_CAPABLE 134 
#define  MPO_DSS 133 
#define  MPO_FAIL 132 
#define  MPO_FASTCLOSE 131 
#define  MPO_JOIN 130 
#define  MPO_PRIO 129 
#define  MPO_REMOVE_ADDR 128 
 int /*<<< orphan*/  TOF_MPTCP ; 
 int /*<<< orphan*/  mptcp_do_dss_opt (struct tcpcb*,int*,struct tcphdr*,int) ; 
 int /*<<< orphan*/  mptcp_do_fastclose_opt (struct tcpcb*,int*,struct tcphdr*) ; 
 int /*<<< orphan*/  mptcp_do_mpcapable_opt (struct tcpcb*,int*,struct tcphdr*,int) ; 
 int /*<<< orphan*/  mptcp_do_mpfail_opt (struct tcpcb*,int*,struct tcphdr*) ; 
 int /*<<< orphan*/  mptcp_do_mpjoin_opt (struct tcpcb*,int*,struct tcphdr*,int) ; 
 scalar_t__ mptcp_sanitize_option (struct tcpcb*,int) ; 
 int /*<<< orphan*/  mpte_lock_assert_held (int /*<<< orphan*/ ) ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

void
tcp_do_mptcp_options(struct tcpcb *tp, u_char *cp, struct tcphdr *th,
    struct tcpopt *to, int optlen)
{
	int mptcp_subtype;
	struct mptcb *mp_tp = tptomptp(tp);

	if (mp_tp == NULL)
		return;

	mpte_lock_assert_held(mp_tp->mpt_mpte);

	/* All MPTCP options have atleast 4 bytes */
	if (optlen < 4)
		return;

	mptcp_subtype = (cp[2] >> 4);

	if (mptcp_sanitize_option(tp, mptcp_subtype) == 0)
		return;

	switch (mptcp_subtype) {
		case MPO_CAPABLE:
			mptcp_do_mpcapable_opt(tp, cp, th, optlen);
			break;
		case MPO_JOIN:
			mptcp_do_mpjoin_opt(tp, cp, th, optlen);
			break;
		case MPO_DSS:
			mptcp_do_dss_opt(tp, cp, th, optlen);
			break;
		case MPO_FASTCLOSE:
			mptcp_do_fastclose_opt(tp, cp, th);
			break;
		case MPO_FAIL:
			mptcp_do_mpfail_opt(tp, cp, th);
			break;
		case MPO_ADD_ADDR:	/* fall through */
		case MPO_REMOVE_ADDR:	/* fall through */
		case MPO_PRIO:
			to->to_flags |= TOF_MPTCP;
			break;
		default:
			break;
	}
	return;
}