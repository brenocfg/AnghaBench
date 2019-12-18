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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int dccps_hc_rx_insert_options; } ;
struct ccid3_hc_rx_sock {scalar_t__ ccid3hcrx_state; unsigned int ccid3hcrx_pinv; scalar_t__ ccid3hcrx_bytes_recv; int /*<<< orphan*/  ccid3hcrx_last_counter; int /*<<< orphan*/  ccid3hcrx_tstamp_last_feedback; int /*<<< orphan*/  ccid3hcrx_x_recv; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum ccid3_fback_type { ____Placeholder_ccid3_fback_type } ccid3_fback_type ;
struct TYPE_2__ {int /*<<< orphan*/  dccph_ccval; } ;

/* Variables and functions */
#define  CCID3_FBACK_INITIAL 130 
#define  CCID3_FBACK_PARAM_CHANGE 129 
#define  CCID3_FBACK_PERIODIC 128 
 int /*<<< orphan*/  DCCP_BUG (char*,long) ; 
 scalar_t__ TFRC_RSTATE_TERM ; 
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,long,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* dccp_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scaled_div32 (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ccid3_hc_rx_send_feedback(struct sock *sk,
				      const struct sk_buff *skb,
				      enum ccid3_fback_type fbtype)
{
	struct ccid3_hc_rx_sock *hcrx = ccid3_hc_rx_sk(sk);
	struct dccp_sock *dp = dccp_sk(sk);
	ktime_t now;
	s64 delta = 0;

	if (unlikely(hcrx->ccid3hcrx_state == TFRC_RSTATE_TERM))
		return;

	now = ktime_get_real();

	switch (fbtype) {
	case CCID3_FBACK_INITIAL:
		hcrx->ccid3hcrx_x_recv = 0;
		hcrx->ccid3hcrx_pinv   = ~0U;   /* see RFC 4342, 8.5 */
		break;
	case CCID3_FBACK_PARAM_CHANGE:
		/*
		 * When parameters change (new loss or p > p_prev), we do not
		 * have a reliable estimate for R_m of [RFC 3448, 6.2] and so
		 * need to  reuse the previous value of X_recv. However, when
		 * X_recv was 0 (due to early loss), this would kill X down to
		 * s/t_mbi (i.e. one packet in 64 seconds).
		 * To avoid such drastic reduction, we approximate X_recv as
		 * the number of bytes since last feedback.
		 * This is a safe fallback, since X is bounded above by X_calc.
		 */
		if (hcrx->ccid3hcrx_x_recv > 0)
			break;
		/* fall through */
	case CCID3_FBACK_PERIODIC:
		delta = ktime_us_delta(now, hcrx->ccid3hcrx_tstamp_last_feedback);
		if (delta <= 0)
			DCCP_BUG("delta (%ld) <= 0", (long)delta);
		else
			hcrx->ccid3hcrx_x_recv =
				scaled_div32(hcrx->ccid3hcrx_bytes_recv, delta);
		break;
	default:
		return;
	}

	ccid3_pr_debug("Interval %ldusec, X_recv=%u, 1/p=%u\n", (long)delta,
		       hcrx->ccid3hcrx_x_recv, hcrx->ccid3hcrx_pinv);

	hcrx->ccid3hcrx_tstamp_last_feedback = now;
	hcrx->ccid3hcrx_last_counter	     = dccp_hdr(skb)->dccph_ccval;
	hcrx->ccid3hcrx_bytes_recv	     = 0;

	dp->dccps_hc_rx_insert_options = 1;
	dccp_send_ack(sk);
}