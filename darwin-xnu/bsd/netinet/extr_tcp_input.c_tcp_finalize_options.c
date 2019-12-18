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
struct tcpopt {int to_flags; int /*<<< orphan*/  to_requested_s_scale; int /*<<< orphan*/  to_mss; int /*<<< orphan*/  to_tsval; } ;
struct tcpcb {scalar_t__ request_r_scale; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  requested_s_scale; int /*<<< orphan*/  t_flagsext; int /*<<< orphan*/  ts_recent_age; int /*<<< orphan*/  ts_recent; } ;

/* Variables and functions */
 scalar_t__ SACK_ENABLED (struct tcpcb*) ; 
 int /*<<< orphan*/  TF_RCVD_SCALE ; 
 int /*<<< orphan*/  TF_RCVD_TSTMP ; 
 int /*<<< orphan*/  TF_REQ_SCALE ; 
 int /*<<< orphan*/  TF_SACK_ENABLE ; 
 int /*<<< orphan*/  TF_SACK_PERMIT ; 
 int TOF_MSS ; 
 int TOF_SACK ; 
 int TOF_SCALE ; 
 int TOF_TS ; 
 int /*<<< orphan*/  tcp_mss (struct tcpcb*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tcp_now ; 

__attribute__((used)) static void
tcp_finalize_options(struct tcpcb *tp, struct tcpopt *to, unsigned int ifscope)
{
	if (to->to_flags & TOF_TS) {
		tp->t_flags |= TF_RCVD_TSTMP;
		tp->ts_recent = to->to_tsval;
		tp->ts_recent_age = tcp_now;

	}
	if (to->to_flags & TOF_MSS)
		tcp_mss(tp, to->to_mss, ifscope);
	if (SACK_ENABLED(tp)) {
		if (!(to->to_flags & TOF_SACK))
			tp->t_flagsext &= ~(TF_SACK_ENABLE);
		else
			tp->t_flags |= TF_SACK_PERMIT;
	}
	if (to->to_flags & TOF_SCALE) {
		tp->t_flags |= TF_RCVD_SCALE;
		tp->requested_s_scale = to->to_requested_s_scale;

		/* Re-enable window scaling, if the option is received */
		if (tp->request_r_scale > 0)
			tp->t_flags |= TF_REQ_SCALE;
	}
}