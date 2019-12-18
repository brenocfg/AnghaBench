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
struct tcpopt {int to_flags; unsigned char* to_tfo; } ;
struct tcpcb {int t_tfo_flags; int /*<<< orphan*/  t_tfo_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_tfo_no_cookie_rcv; int /*<<< orphan*/  tcps_tfo_syn_loss; int /*<<< orphan*/  tcps_tfo_cookie_wrong; int /*<<< orphan*/  tcps_tfo_cookie_rcv; } ;

/* Variables and functions */
 unsigned char TCPOLEN_FASTOPEN_REQ ; 
 unsigned char TFO_COOKIE_LEN_MAX ; 
 int TFO_F_COOKIE_REQ ; 
 int TFO_F_COOKIE_SENT ; 
 int TFO_F_SYN_LOSS ; 
 int /*<<< orphan*/  TFO_S_COOKIE_RCV ; 
 int /*<<< orphan*/  TFO_S_COOKIE_WRONG ; 
 int /*<<< orphan*/  TFO_S_NO_COOKIE_RCV ; 
 int /*<<< orphan*/  TFO_S_SYN_LOSS ; 
 int TOF_TFO ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  tcp_cache_set_cookie (struct tcpcb*,unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  tcp_heuristic_tfo_loss (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_heuristic_tfo_success (struct tcpcb*) ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static void
tcp_tfo_synack(struct tcpcb *tp, struct tcpopt *to)
{
	if (to->to_flags & TOF_TFO) {
		unsigned char len = *to->to_tfo - TCPOLEN_FASTOPEN_REQ;

		/*
		 * If this happens, things have gone terribly wrong. len should
		 * have been checked in tcp_dooptions.
		 */
		VERIFY(len <= TFO_COOKIE_LEN_MAX);

		to->to_tfo++;

		tcp_cache_set_cookie(tp, to->to_tfo, len);
		tcp_heuristic_tfo_success(tp);

		tp->t_tfo_stats |= TFO_S_COOKIE_RCV;
		tcpstat.tcps_tfo_cookie_rcv++;
		if (tp->t_tfo_flags & TFO_F_COOKIE_SENT) {
			tcpstat.tcps_tfo_cookie_wrong++;
			tp->t_tfo_stats |= TFO_S_COOKIE_WRONG;
		}
	} else {
		/*
		 * Thus, no cookie in the response, but we either asked for one
		 * or sent SYN+DATA. Now, we need to check whether we had to
		 * rexmit the SYN. If that's the case, it's better to start
		 * backing of TFO-cookie requests.
		 */
		if (tp->t_tfo_flags & TFO_F_SYN_LOSS) {
			tp->t_tfo_stats |= TFO_S_SYN_LOSS;
			tcpstat.tcps_tfo_syn_loss++;

			tcp_heuristic_tfo_loss(tp);
		} else {
			if (tp->t_tfo_flags & TFO_F_COOKIE_REQ) {
				tp->t_tfo_stats |= TFO_S_NO_COOKIE_RCV;
				tcpstat.tcps_tfo_no_cookie_rcv++;
			}

			tcp_heuristic_tfo_success(tp);
		}
	}
}