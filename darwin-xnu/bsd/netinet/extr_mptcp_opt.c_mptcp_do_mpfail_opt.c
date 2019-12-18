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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct tcphdr {scalar_t__ th_seq; scalar_t__ th_flags; } ;
struct tcpcb {scalar_t__ rcv_nxt; TYPE_1__* t_inpcb; } ;
struct mptcp_mpfail_opt {int mfail_len; int /*<<< orphan*/  mfail_dsn; } ;
struct mptcb {int /*<<< orphan*/  mpt_ssn_at_csum_fail; int /*<<< orphan*/  mpt_dsn_at_csum_fail; int /*<<< orphan*/  mpt_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcps_invalid_opt; } ;
struct TYPE_3__ {int /*<<< orphan*/  inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTCPF_RECVD_MPFAIL ; 
 scalar_t__ TH_ACK ; 
 scalar_t__ TH_RST ; 
 int mptcp_get_map_for_dsn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mptcp_hton64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptcp_notify_mpfail (int /*<<< orphan*/ ) ; 
 TYPE_2__ tcpstat ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

__attribute__((used)) static void
mptcp_do_mpfail_opt(struct tcpcb *tp, u_char *cp, struct tcphdr *th)
{
	struct mptcb *mp_tp = NULL;
	struct mptcp_mpfail_opt *fail_opt = (struct mptcp_mpfail_opt *)cp;
	u_int32_t mdss_subflow_seqn = 0;
	int error = 0;

	/*
	 * mpfail could make us more vulnerable to attacks. Hence accept
	 * only those that are the next expected sequence number.
	 */
	if (th->th_seq != tp->rcv_nxt) {
		tcpstat.tcps_invalid_opt++;
		return;
	}

	/* A packet without RST, must atleast have the ACK bit set */
	if ((th->th_flags != TH_ACK) && (th->th_flags != TH_RST))
		return;

	if (fail_opt->mfail_len != sizeof (struct mptcp_mpfail_opt))
		return;

	mp_tp = tptomptp(tp);

	mp_tp->mpt_flags |= MPTCPF_RECVD_MPFAIL;
	mp_tp->mpt_dsn_at_csum_fail = mptcp_hton64(fail_opt->mfail_dsn);
	error = mptcp_get_map_for_dsn(tp->t_inpcb->inp_socket,
	    mp_tp->mpt_dsn_at_csum_fail, &mdss_subflow_seqn);
	if (error == 0) {
		mp_tp->mpt_ssn_at_csum_fail = mdss_subflow_seqn;
	}

	mptcp_notify_mpfail(tp->t_inpcb->inp_socket);
}