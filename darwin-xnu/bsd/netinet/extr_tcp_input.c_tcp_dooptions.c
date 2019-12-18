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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_char ;
struct tcpopt {int to_nsacks; int* to_sacks; int* to_tfo; int /*<<< orphan*/  to_flags; int /*<<< orphan*/  to_tsecr; int /*<<< orphan*/  to_tsval; int /*<<< orphan*/  to_requested_s_scale; int /*<<< orphan*/  to_mss; } ;
struct tcphdr {int th_flags; } ;
struct tcpcb {int t_flags; int /*<<< orphan*/  t_state; } ;
typedef  int /*<<< orphan*/  mss ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_sack_rcv_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTOHL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTOHS (int /*<<< orphan*/ ) ; 
 int TCPOLEN_FASTOPEN_REQ ; 
 int TCPOLEN_MAXSEG ; 
 int TCPOLEN_SACK ; 
 int TCPOLEN_SACK_PERMITTED ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOLEN_WINDOW ; 
 int TCPOPT_EOL ; 
#define  TCPOPT_FASTOPEN 134 
#define  TCPOPT_MAXSEG 133 
#define  TCPOPT_MULTIPATH 132 
 int TCPOPT_NOP ; 
#define  TCPOPT_SACK 131 
#define  TCPOPT_SACK_PERMITTED 130 
#define  TCPOPT_TIMESTAMP 129 
#define  TCPOPT_WINDOW 128 
 int /*<<< orphan*/  TCPS_LISTEN ; 
 int /*<<< orphan*/  TCPS_SYN_SENT ; 
 int /*<<< orphan*/  TCP_MAX_WINSHIFT ; 
 int /*<<< orphan*/  TFO_COOKIE_LEN_MAX ; 
 int /*<<< orphan*/  TFO_COOKIE_LEN_MIN ; 
 int TF_REQ_TSTMP ; 
 int TH_SYN ; 
 int /*<<< orphan*/  TOF_MSS ; 
 int /*<<< orphan*/  TOF_SACK ; 
 int /*<<< orphan*/  TOF_SCALE ; 
 int /*<<< orphan*/  TOF_TFO ; 
 int /*<<< orphan*/  TOF_TFOREQ ; 
 int /*<<< orphan*/  TOF_TS ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_do_mptcp_options (struct tcpcb*,int*,struct tcphdr*,struct tcpopt*,int) ; 
 int tcp_do_rfc1323 ; 
 int /*<<< orphan*/  tcp_do_sack ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static void
tcp_dooptions(struct tcpcb *tp, u_char *cp, int cnt, struct tcphdr *th,
    struct tcpopt *to)
{
	u_short mss = 0;
	int opt, optlen;

	for (; cnt > 0; cnt -= optlen, cp += optlen) {
		opt = cp[0];
		if (opt == TCPOPT_EOL)
			break;
		if (opt == TCPOPT_NOP)
			optlen = 1;
		else {
			if (cnt < 2)
				break;
			optlen = cp[1];
			if (optlen < 2 || optlen > cnt)
				break;
		}
		switch (opt) {

		default:
			continue;

		case TCPOPT_MAXSEG:
			if (optlen != TCPOLEN_MAXSEG)
				continue;
			if (!(th->th_flags & TH_SYN))
				continue;
			bcopy((char *) cp + 2, (char *) &mss, sizeof(mss));
			NTOHS(mss);
			to->to_mss = mss;
			to->to_flags |= TOF_MSS;
			break;

		case TCPOPT_WINDOW:
			if (optlen != TCPOLEN_WINDOW)
				continue;
			if (!(th->th_flags & TH_SYN))
				continue;
			to->to_flags |= TOF_SCALE;
			to->to_requested_s_scale = min(cp[2], TCP_MAX_WINSHIFT);
			break;

		case TCPOPT_TIMESTAMP:
			if (optlen != TCPOLEN_TIMESTAMP)
				continue;
			to->to_flags |= TOF_TS;
			bcopy((char *)cp + 2,
			    (char *)&to->to_tsval, sizeof(to->to_tsval));
			NTOHL(to->to_tsval);
			bcopy((char *)cp + 6,
			    (char *)&to->to_tsecr, sizeof(to->to_tsecr));
			NTOHL(to->to_tsecr);
			/* Re-enable sending Timestamps if we received them */
			if (!(tp->t_flags & TF_REQ_TSTMP) &&
			    tcp_do_rfc1323 == 1)
				tp->t_flags |= TF_REQ_TSTMP;
			break;
		case TCPOPT_SACK_PERMITTED:
			if (!tcp_do_sack ||
			    optlen != TCPOLEN_SACK_PERMITTED)
				continue;
			if (th->th_flags & TH_SYN)
				to->to_flags |= TOF_SACK;
			break;
		case TCPOPT_SACK:
			if (optlen <= 2 || (optlen - 2) % TCPOLEN_SACK != 0)
				continue;
			to->to_nsacks = (optlen - 2) / TCPOLEN_SACK;
			to->to_sacks = cp + 2;
			tcpstat.tcps_sack_rcv_blocks++;

			break;
		case TCPOPT_FASTOPEN:
			if (optlen == TCPOLEN_FASTOPEN_REQ) {
				if (tp->t_state != TCPS_LISTEN)
					continue;

				to->to_flags |= TOF_TFOREQ;
			} else {
				if (optlen < TCPOLEN_FASTOPEN_REQ ||
				    (optlen - TCPOLEN_FASTOPEN_REQ) > TFO_COOKIE_LEN_MAX ||
				    (optlen - TCPOLEN_FASTOPEN_REQ) < TFO_COOKIE_LEN_MIN)
					continue;
				if (tp->t_state != TCPS_LISTEN &&
				    tp->t_state != TCPS_SYN_SENT)
					continue;

				to->to_flags |= TOF_TFO;
				to->to_tfo = cp + 1;
			}

			break;
#if MPTCP
		case TCPOPT_MULTIPATH:
			tcp_do_mptcp_options(tp, cp, th, to, optlen);
			break;
#endif /* MPTCP */
		}
	}
}