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
typedef  unsigned int u32 ;
struct tcp_sock {unsigned int snd_cwnd; int bytes_acked; int mss_cache; int snd_cwnd_cnt; int /*<<< orphan*/  snd_cwnd_clamp; } ;

/* Variables and functions */
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err_once (char*) ; 
 int sysctl_tcp_abc ; 
 int sysctl_tcp_max_ssthresh ; 
 scalar_t__ unlikely (int) ; 

void tcp_slow_start(struct tcp_sock *tp)
{
	int cnt; /* increase in packets */
	unsigned int delta = 0;
	u32 snd_cwnd = tp->snd_cwnd;

	if (unlikely(!snd_cwnd)) {
		pr_err_once("snd_cwnd is nul, please report this bug.\n");
		snd_cwnd = 1U;
	}

	/* RFC3465: ABC Slow start
	 * Increase only after a full MSS of bytes is acked
	 *
	 * TCP sender SHOULD increase cwnd by the number of
	 * previously unacknowledged bytes ACKed by each incoming
	 * acknowledgment, provided the increase is not more than L
	 */
	if (sysctl_tcp_abc && tp->bytes_acked < tp->mss_cache)
		return;

	if (sysctl_tcp_max_ssthresh > 0 && tp->snd_cwnd > sysctl_tcp_max_ssthresh)
		cnt = sysctl_tcp_max_ssthresh >> 1;	/* limited slow start */
	else
		cnt = snd_cwnd;				/* exponential increase */

	/* RFC3465: ABC
	 * We MAY increase by 2 if discovered delayed ack
	 */
	if (sysctl_tcp_abc > 1 && tp->bytes_acked >= 2*tp->mss_cache)
		cnt <<= 1;
	tp->bytes_acked = 0;

	tp->snd_cwnd_cnt += cnt;
	while (tp->snd_cwnd_cnt >= snd_cwnd) {
		tp->snd_cwnd_cnt -= snd_cwnd;
		delta++;
	}
	tp->snd_cwnd = min(snd_cwnd + delta, tp->snd_cwnd_clamp);
}