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
typedef  long u32 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct dccp_sock {long dccps_syn_rtt; int dccps_hc_tx_insert_options; } ;
struct ccid3_hc_tx_sock {int ccid3hctx_state; scalar_t__ ccid3hctx_s; long ccid3hctx_rtt; scalar_t__ ccid3hctx_x; int /*<<< orphan*/  ccid3hctx_t_ipi; void* ccid3hctx_t_nom; int /*<<< orphan*/  ccid3hctx_last_win_count; int /*<<< orphan*/  ccid3hctx_delta; void* ccid3hctx_t_ld; void* ccid3hctx_t_last_win_count; int /*<<< orphan*/  ccid3hctx_no_feedback_timer; } ;
typedef  int s64 ;
typedef  void* ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  dccpd_ccval; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG (char*,int /*<<< orphan*/ ,struct sock*) ; 
 long DCCP_FALLBACK_RTT ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int EBADMSG ; 
 int EINVAL ; 
 int /*<<< orphan*/  TFRC_INITIAL_TIMEOUT ; 
#define  TFRC_SSTATE_FBACK 131 
#define  TFRC_SSTATE_NO_FBACK 130 
#define  TFRC_SSTATE_NO_SENT 129 
#define  TFRC_SSTATE_TERM 128 
 int /*<<< orphan*/  ccid3_hc_tx_set_state (struct sock*,int) ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_hc_tx_update_win_count (struct ccid3_hc_tx_sock*,void*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,long) ; 
 int /*<<< orphan*/  ccid3_update_send_interval (struct ccid3_hc_tx_sock*) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 scalar_t__ jiffies ; 
 void* ktime_add_us (void*,int /*<<< orphan*/ ) ; 
 void* ktime_get_real () ; 
 int ktime_us_delta (void*,void*) ; 
 scalar_t__ rfc3390_initial_rate (struct sock*) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccid3_hc_tx_send_packet(struct sock *sk, struct sk_buff *skb)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct ccid3_hc_tx_sock *hctx = ccid3_hc_tx_sk(sk);
	ktime_t now = ktime_get_real();
	s64 delay;

	/*
	 * This function is called only for Data and DataAck packets. Sending
	 * zero-sized Data(Ack)s is theoretically possible, but for congestion
	 * control this case is pathological - ignore it.
	 */
	if (unlikely(skb->len == 0))
		return -EBADMSG;

	switch (hctx->ccid3hctx_state) {
	case TFRC_SSTATE_NO_SENT:
		sk_reset_timer(sk, &hctx->ccid3hctx_no_feedback_timer,
			       (jiffies +
				usecs_to_jiffies(TFRC_INITIAL_TIMEOUT)));
		hctx->ccid3hctx_last_win_count	 = 0;
		hctx->ccid3hctx_t_last_win_count = now;

		/* Set t_0 for initial packet */
		hctx->ccid3hctx_t_nom = now;

		hctx->ccid3hctx_s = skb->len;

		/*
		 * Use initial RTT sample when available: recommended by erratum
		 * to RFC 4342. This implements the initialisation procedure of
		 * draft rfc3448bis, section 4.2. Remember, X is scaled by 2^6.
		 */
		if (dp->dccps_syn_rtt) {
			ccid3_pr_debug("SYN RTT = %uus\n", dp->dccps_syn_rtt);
			hctx->ccid3hctx_rtt  = dp->dccps_syn_rtt;
			hctx->ccid3hctx_x    = rfc3390_initial_rate(sk);
			hctx->ccid3hctx_t_ld = now;
		} else {
			/*
			 * Sender does not have RTT sample:
			 * - set fallback RTT (RFC 4340, 3.4) since a RTT value
			 *   is needed in several parts (e.g.  window counter);
			 * - set sending rate X_pps = 1pps as per RFC 3448, 4.2.
			 */
			hctx->ccid3hctx_rtt = DCCP_FALLBACK_RTT;
			hctx->ccid3hctx_x   = hctx->ccid3hctx_s;
			hctx->ccid3hctx_x <<= 6;
		}
		ccid3_update_send_interval(hctx);

		ccid3_hc_tx_set_state(sk, TFRC_SSTATE_NO_FBACK);
		break;
	case TFRC_SSTATE_NO_FBACK:
	case TFRC_SSTATE_FBACK:
		delay = ktime_us_delta(hctx->ccid3hctx_t_nom, now);
		ccid3_pr_debug("delay=%ld\n", (long)delay);
		/*
		 *	Scheduling of packet transmissions [RFC 3448, 4.6]
		 *
		 * if (t_now > t_nom - delta)
		 *       // send the packet now
		 * else
		 *       // send the packet in (t_nom - t_now) milliseconds.
		 */
		if (delay - (s64)hctx->ccid3hctx_delta >= 1000)
			return (u32)delay / 1000L;

		ccid3_hc_tx_update_win_count(hctx, now);
		break;
	case TFRC_SSTATE_TERM:
		DCCP_BUG("%s(%p) - Illegal state TERM", dccp_role(sk), sk);
		return -EINVAL;
	}

	/* prepare to send now (add options etc.) */
	dp->dccps_hc_tx_insert_options = 1;
	DCCP_SKB_CB(skb)->dccpd_ccval = hctx->ccid3hctx_last_win_count;

	/* set the nominal send time for the next following packet */
	hctx->ccid3hctx_t_nom = ktime_add_us(hctx->ccid3hctx_t_nom,
					     hctx->ccid3hctx_t_ipi);
	return 0;
}