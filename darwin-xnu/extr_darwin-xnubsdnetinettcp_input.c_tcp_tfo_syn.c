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
struct tcpopt {int to_flags; unsigned char* to_tfo; } ;
struct tcpcb {int /*<<< orphan*/  t_tfo_stats; int /*<<< orphan*/  t_tfo_flags; int /*<<< orphan*/  t_inpcb; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_tfo_syn_data_rcv; int /*<<< orphan*/  tcps_tfo_cookie_invalid; int /*<<< orphan*/  tcps_tfo_cookie_req_rcv; } ;

/* Variables and functions */
 int CCAES_BLOCK_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 scalar_t__ OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 unsigned char TCPOLEN_FASTOPEN_REQ ; 
 int TCP_FASTOPEN_SERVER ; 
 int /*<<< orphan*/  TFO_F_COOKIE_VALID ; 
 int /*<<< orphan*/  TFO_F_OFFER_COOKIE ; 
 int /*<<< orphan*/  TFO_S_COOKIEREQ_RECV ; 
 int /*<<< orphan*/  TFO_S_COOKIE_INVALID ; 
 int /*<<< orphan*/  TFO_S_SYNDATA_RCV ; 
 int TOF_TFO ; 
 int TOF_TFOREQ ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,unsigned char*,unsigned char) ; 
 int tcp_fastopen ; 
 scalar_t__ tcp_tfo_backlog ; 
 int /*<<< orphan*/  tcp_tfo_gen_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_tfo_halfcnt ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static boolean_t
tcp_tfo_syn(struct tcpcb *tp, struct tcpopt *to)
{
	u_char out[CCAES_BLOCK_SIZE];
	unsigned char len;

	if (!(to->to_flags & (TOF_TFO | TOF_TFOREQ)) ||
	    !(tcp_fastopen & TCP_FASTOPEN_SERVER))
		return (FALSE);

	if ((to->to_flags & TOF_TFOREQ)) {
		tp->t_tfo_flags |= TFO_F_OFFER_COOKIE;

		tp->t_tfo_stats |= TFO_S_COOKIEREQ_RECV;
		tcpstat.tcps_tfo_cookie_req_rcv++;
		return (FALSE);
	}

	/* Ok, then it must be an offered cookie. We need to check that ... */
	tcp_tfo_gen_cookie(tp->t_inpcb, out, sizeof(out));

	len = *to->to_tfo - TCPOLEN_FASTOPEN_REQ;
	to->to_tfo++;
	if (memcmp(out, to->to_tfo, len)) {
		/* Cookies are different! Let's return and offer a new cookie */
		tp->t_tfo_flags |= TFO_F_OFFER_COOKIE;

		tp->t_tfo_stats |= TFO_S_COOKIE_INVALID;
		tcpstat.tcps_tfo_cookie_invalid++;
		return (FALSE);
	}

	if (OSIncrementAtomic(&tcp_tfo_halfcnt) >= tcp_tfo_backlog) {
		/* Need to decrement again as we just increased it... */
		OSDecrementAtomic(&tcp_tfo_halfcnt);
		return (FALSE);
	}

	tp->t_tfo_flags |= TFO_F_COOKIE_VALID;

	tp->t_tfo_stats |= TFO_S_SYNDATA_RCV;
	tcpstat.tcps_tfo_syn_data_rcv++;

	return (TRUE);
}