#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcpcb {int t_flags; int t_flagsext; scalar_t__ t_rxtshift; unsigned int t_maxopd; int /*<<< orphan*/  t_tfo_stats; TYPE_1__* t_inpcb; } ;
struct TYPE_5__ {unsigned int sb_cc; } ;
struct socket {int so_flags1; int so_flags; TYPE_2__ so_snd; } ;
struct mptcp_mpcapable_opt_common {int dummy; } ;
typedef  int /*<<< orphan*/  mptcp_key_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  tcps_tfo_heuristics_disable; } ;
struct TYPE_4__ {struct socket* inp_socket; } ;

/* Variables and functions */
 unsigned int MAX_TCPOPTLEN ; 
 scalar_t__ SACK_ENABLED (struct tcpcb*) ; 
 int SOF1_DATA_AUTHENTICATED ; 
 int SOF_MP_SUBFLOW ; 
 unsigned int TCPOLEN_FASTOPEN_REQ ; 
 scalar_t__ TCPOLEN_MAXSEG ; 
 scalar_t__ TCPOLEN_SACK_PERMITTED ; 
 scalar_t__ TCPOLEN_TSTAMP_APPA ; 
 int /*<<< orphan*/  TFO_S_HEURISTICS_DISABLE ; 
 int TF_FASTOPEN ; 
 int TF_FASTOPEN_HEUR ; 
 int TF_NOOPT ; 
 int TF_REQ_SCALE ; 
 int TF_REQ_TSTMP ; 
 scalar_t__ mptcp_enable ; 
 scalar_t__ mptcp_mpcap_retries ; 
 unsigned int tcp_cache_get_cookie_len (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_heuristic_do_tfo (struct tcpcb*) ; 
 TYPE_3__ tcpstat ; 

__attribute__((used)) static int32_t tcp_tfo_check(struct tcpcb *tp, int32_t len)
{
	struct socket *so = tp->t_inpcb->inp_socket;
	unsigned int optlen = 0;
	unsigned int cookie_len;

	if (tp->t_flags & TF_NOOPT)
		goto fallback;

	if ((so->so_flags1 & SOF1_DATA_AUTHENTICATED) &&
	    !(tp->t_flagsext & TF_FASTOPEN_HEUR))
		return (len);

	if (!tcp_heuristic_do_tfo(tp)) {
		tp->t_tfo_stats |= TFO_S_HEURISTICS_DISABLE;
		tcpstat.tcps_tfo_heuristics_disable++;
		goto fallback;
	}

	if (so->so_flags1 & SOF1_DATA_AUTHENTICATED)
		return (len);

	optlen += TCPOLEN_MAXSEG;

	if (tp->t_flags & TF_REQ_SCALE)
		optlen += 4;

#if MPTCP
	if ((so->so_flags & SOF_MP_SUBFLOW) && mptcp_enable &&
	    tp->t_rxtshift <= mptcp_mpcap_retries)
		optlen += sizeof(struct mptcp_mpcapable_opt_common) + sizeof(mptcp_key_t);
#endif /* MPTCP */

	if (tp->t_flags & TF_REQ_TSTMP)
		optlen += TCPOLEN_TSTAMP_APPA;

	if (SACK_ENABLED(tp))
		optlen += TCPOLEN_SACK_PERMITTED;

	/* Now, decide whether to use TFO or not */

	/* Don't even bother trying if there is no space at all... */
	if (MAX_TCPOPTLEN - optlen < TCPOLEN_FASTOPEN_REQ)
		goto fallback;

	cookie_len = tcp_cache_get_cookie_len(tp);
	if (cookie_len == 0)
		/* No cookie, so we request one */
		return (0);

	/* There is not enough space for the cookie, so we cannot do TFO */
	if (MAX_TCPOPTLEN - optlen < cookie_len)
		goto fallback;

	/* Do not send SYN+data if there is more in the queue than MSS */
	if (so->so_snd.sb_cc > (tp->t_maxopd - MAX_TCPOPTLEN))
		goto fallback;

	/* Ok, everything looks good. We can go on and do TFO */
	return (len);

fallback:
	tp->t_flagsext &= ~TF_FASTOPEN;
	return (0);
}