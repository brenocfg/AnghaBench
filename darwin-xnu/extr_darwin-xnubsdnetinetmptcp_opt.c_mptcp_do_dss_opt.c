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
typedef  int /*<<< orphan*/  u_char ;
struct tcphdr {int dummy; } ;
struct TYPE_2__ {int mpt_dfin; } ;
struct tcpcb {int t_mpflags; TYPE_1__ t_rcv_map; } ;
struct mptcp_dss_copt {scalar_t__ mdss_subtype; int mdss_flags; } ;
struct mptcb {int dummy; } ;

/* Variables and functions */
 int MDSS_F ; 
 scalar_t__ MPO_DSS ; 
 int TMPF_MPTCP_TRUE ; 
 int TMPF_TCP_FALLBACK ; 
 int /*<<< orphan*/  mptcp_do_dss_opt_meat (int /*<<< orphan*/ *,struct tcpcb*,struct tcphdr*) ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

__attribute__((used)) static void
mptcp_do_dss_opt(struct tcpcb *tp, u_char *cp, struct tcphdr *th, int optlen)
{
#pragma unused(optlen)
	struct mptcb *mp_tp = tptomptp(tp);

	if (!mp_tp)
		return;

	/* We may get Data ACKs just during fallback, so don't ignore those */
	if ((tp->t_mpflags & TMPF_MPTCP_TRUE) ||
	    (tp->t_mpflags & TMPF_TCP_FALLBACK)) {
		struct mptcp_dss_copt *dss_rsp = (struct mptcp_dss_copt *)cp;

		if (dss_rsp->mdss_subtype == MPO_DSS) {
			if (dss_rsp->mdss_flags & MDSS_F)
				tp->t_rcv_map.mpt_dfin = 1;

			mptcp_do_dss_opt_meat(cp, tp, th);
		}
	}
}