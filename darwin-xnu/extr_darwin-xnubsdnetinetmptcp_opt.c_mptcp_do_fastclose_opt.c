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
typedef  int /*<<< orphan*/  u_char ;
struct tcphdr {scalar_t__ th_flags; scalar_t__ th_seq; } ;
struct tcpcb {scalar_t__ rcv_nxt; int t_mpflags; TYPE_1__* t_inpcb; } ;
struct mptcp_fastclose_opt {int mfast_len; scalar_t__ mfast_key; } ;
struct mptcb {scalar_t__ mpt_localkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcps_invalid_opt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * inp_socket; } ;

/* Variables and functions */
 int SO_FILT_HINT_LOCKED ; 
 int SO_FILT_HINT_MUSTRST ; 
 scalar_t__ TH_ACK ; 
 int TMPF_FASTCLOSERCV ; 
 int TMPF_RESET ; 
 int /*<<< orphan*/  soevent (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ tcpstat ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

__attribute__((used)) static void
mptcp_do_fastclose_opt(struct tcpcb *tp, u_char *cp, struct tcphdr *th)
{
	struct mptcb *mp_tp = NULL;
	struct mptcp_fastclose_opt *fc_opt = (struct mptcp_fastclose_opt *)cp;

	if (th->th_flags != TH_ACK)
		return;

	if (fc_opt->mfast_len != sizeof (struct mptcp_fastclose_opt)) {
		tcpstat.tcps_invalid_opt++;
		return;
	}

	mp_tp = tptomptp(tp);
	if (!mp_tp)
		return;

	if (fc_opt->mfast_key != mp_tp->mpt_localkey) {
		tcpstat.tcps_invalid_opt++;
		return;
	}

	/*
	 * fastclose could make us more vulnerable to attacks, hence
	 * accept only those that are at the next expected sequence number.
	 */
	if (th->th_seq != tp->rcv_nxt) {
		tcpstat.tcps_invalid_opt++;
		return;
	}

	/* Reset this flow */
	tp->t_mpflags |= (TMPF_RESET | TMPF_FASTCLOSERCV);

	if (tp->t_inpcb->inp_socket != NULL) {
		soevent(tp->t_inpcb->inp_socket,
		    SO_FILT_HINT_LOCKED | SO_FILT_HINT_MUSTRST);
	}
}