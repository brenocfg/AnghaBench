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
typedef  unsigned int u_int8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct tcpcb {int /*<<< orphan*/  t_tfo_stats; int /*<<< orphan*/  t_tfo_flags; TYPE_1__* t_inpcb; } ;
struct socket {int so_flags1; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  tcps_tfo_syn_data_sent; int /*<<< orphan*/  tcps_tfo_cookie_req; } ;
struct TYPE_3__ {struct socket* inp_socket; } ;

/* Variables and functions */
 unsigned int MAX_TCPOPTLEN ; 
 int SOF1_DATA_AUTHENTICATED ; 
 unsigned int TCPOLEN_FASTOPEN_REQ ; 
 void* TCPOPT_FASTOPEN ; 
 int /*<<< orphan*/  TFO_F_COOKIE_REQ ; 
 int /*<<< orphan*/  TFO_F_COOKIE_SENT ; 
 int /*<<< orphan*/  TFO_S_COOKIE_REQ ; 
 int /*<<< orphan*/  TFO_S_SYN_DATA_SENT ; 
 int tcp_cache_get_cookie (struct tcpcb*,int /*<<< orphan*/ *,unsigned int*) ; 
 TYPE_2__ tcpstat ; 

__attribute__((used)) static unsigned
tcp_tfo_write_cookie(struct tcpcb *tp, unsigned optlen, int32_t len,
		     u_char *opt)
{
	u_int8_t tfo_len = MAX_TCPOPTLEN - optlen - TCPOLEN_FASTOPEN_REQ;
	struct socket *so = tp->t_inpcb->inp_socket;
	unsigned ret = 0;
	int res;
	u_char *bp;

	if (so->so_flags1 & SOF1_DATA_AUTHENTICATED) {
		/* If there is some data, let's track it */
		if (len > 0) {
			tp->t_tfo_stats |= TFO_S_SYN_DATA_SENT;
			tcpstat.tcps_tfo_syn_data_sent++;
		}

		return (0);
	}

	bp = opt + optlen;

	/*
	 * The cookie will be copied in the appropriate place within the
	 * TCP-option space. That way we avoid the need for an intermediate
	 * variable.
	 */
	res = tcp_cache_get_cookie(tp, bp + TCPOLEN_FASTOPEN_REQ, &tfo_len);
	if (res == 0) {
		*bp++ = TCPOPT_FASTOPEN;
		*bp++ = TCPOLEN_FASTOPEN_REQ;
		ret += TCPOLEN_FASTOPEN_REQ;

		tp->t_tfo_flags |= TFO_F_COOKIE_REQ;

		tp->t_tfo_stats |= TFO_S_COOKIE_REQ;
		tcpstat.tcps_tfo_cookie_req++;
	} else {
		*bp++ = TCPOPT_FASTOPEN;
		*bp++ = TCPOLEN_FASTOPEN_REQ + tfo_len;

		ret += TCPOLEN_FASTOPEN_REQ + tfo_len;

		tp->t_tfo_flags |= TFO_F_COOKIE_SENT;

		/* If there is some data, let's track it */
		if (len > 0) {
			tp->t_tfo_stats |= TFO_S_SYN_DATA_SENT;
			tcpstat.tcps_tfo_syn_data_sent++;
		}
	}

	return (ret);
}