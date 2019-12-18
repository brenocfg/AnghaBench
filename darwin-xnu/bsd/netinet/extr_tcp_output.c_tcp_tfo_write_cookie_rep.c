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
struct tcpcb {int /*<<< orphan*/  t_tfo_stats; int /*<<< orphan*/  t_inpcb; } ;
typedef  int /*<<< orphan*/  out ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_tfo_cookie_sent; } ;

/* Variables and functions */
 int CCAES_BLOCK_SIZE ; 
 unsigned int MAX_TCPOPTLEN ; 
 unsigned int TCPOLEN_FASTOPEN_REQ ; 
 int /*<<< orphan*/  TCPOPT_FASTOPEN ; 
 unsigned int TFO_COOKIE_LEN_DEFAULT ; 
 int /*<<< orphan*/  TFO_S_COOKIE_SENT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tcp_tfo_gen_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static unsigned
tcp_tfo_write_cookie_rep(struct tcpcb *tp, unsigned optlen, u_char *opt)
{
	u_char out[CCAES_BLOCK_SIZE];
	unsigned ret = 0;
	u_char *bp;

	if ((MAX_TCPOPTLEN - optlen) <
	    (TCPOLEN_FASTOPEN_REQ + TFO_COOKIE_LEN_DEFAULT))
		return (ret);

	tcp_tfo_gen_cookie(tp->t_inpcb, out, sizeof(out));

	bp = opt + optlen;

	*bp++ = TCPOPT_FASTOPEN;
	*bp++ = 2 + TFO_COOKIE_LEN_DEFAULT;
	memcpy(bp, out, TFO_COOKIE_LEN_DEFAULT);
	ret += 2 + TFO_COOKIE_LEN_DEFAULT;

	tp->t_tfo_stats |= TFO_S_COOKIE_SENT;
	tcpstat.tcps_tfo_cookie_sent++;

	return (ret);
}