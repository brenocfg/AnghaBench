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
struct sock {int dummy; } ;
struct ccid3_hc_tx_sock {scalar_t__ ccid3hctx_state; int ccid3hctx_t_rto; scalar_t__ ccid3hctx_p; int ccid3hctx_x; int ccid3hctx_x_calc; int ccid3hctx_x_recv; int ccid3hctx_t_ipi; int /*<<< orphan*/  ccid3hctx_no_feedback_timer; scalar_t__ ccid3hctx_s; } ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long TFRC_INITIAL_TIMEOUT ; 
 scalar_t__ TFRC_SSTATE_FBACK ; 
 scalar_t__ TFRC_SSTATE_NO_FBACK ; 
 int TFRC_T_MBI ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  ccid3_hc_tx_set_state (struct sock*,scalar_t__) ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_hc_tx_update_x (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,unsigned long long,...) ; 
 int /*<<< orphan*/  ccid3_tx_state_name (scalar_t__) ; 
 int /*<<< orphan*/  ccid3_update_send_interval (struct ccid3_hc_tx_sock*) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 
 scalar_t__ jiffies ; 
 void* max (int,int) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static void ccid3_hc_tx_no_feedback_timer(unsigned long data)
{
	struct sock *sk = (struct sock *)data;
	struct ccid3_hc_tx_sock *hctx = ccid3_hc_tx_sk(sk);
	unsigned long t_nfb = USEC_PER_SEC / 5;

	bh_lock_sock(sk);
	if (sock_owned_by_user(sk)) {
		/* Try again later. */
		/* XXX: set some sensible MIB */
		goto restart_timer;
	}

	ccid3_pr_debug("%s(%p, state=%s) - entry \n", dccp_role(sk), sk,
		       ccid3_tx_state_name(hctx->ccid3hctx_state));

	if (hctx->ccid3hctx_state == TFRC_SSTATE_FBACK)
		ccid3_hc_tx_set_state(sk, TFRC_SSTATE_NO_FBACK);
	else if (hctx->ccid3hctx_state != TFRC_SSTATE_NO_FBACK)
		goto out;

	/*
	 * Determine new allowed sending rate X as per draft rfc3448bis-00, 4.4
	 */
	if (hctx->ccid3hctx_t_rto == 0 ||	/* no feedback received yet */
	    hctx->ccid3hctx_p == 0) {

		/* halve send rate directly */
		hctx->ccid3hctx_x = max(hctx->ccid3hctx_x / 2,
					(((__u64)hctx->ccid3hctx_s) << 6) /
								    TFRC_T_MBI);
		ccid3_update_send_interval(hctx);
	} else {
		/*
		 *  Modify the cached value of X_recv
		 *
		 *  If (X_calc > 2 * X_recv)
		 *    X_recv = max(X_recv / 2, s / (2 * t_mbi));
		 *  Else
		 *    X_recv = X_calc / 4;
		 *
		 *  Note that X_recv is scaled by 2^6 while X_calc is not
		 */
		BUG_ON(hctx->ccid3hctx_p && !hctx->ccid3hctx_x_calc);

		if (hctx->ccid3hctx_x_calc > (hctx->ccid3hctx_x_recv >> 5))
			hctx->ccid3hctx_x_recv =
				max(hctx->ccid3hctx_x_recv / 2,
				    (((__u64)hctx->ccid3hctx_s) << 6) /
							      (2 * TFRC_T_MBI));
		else {
			hctx->ccid3hctx_x_recv = hctx->ccid3hctx_x_calc;
			hctx->ccid3hctx_x_recv <<= 4;
		}
		ccid3_hc_tx_update_x(sk, NULL);
	}
	ccid3_pr_debug("Reduced X to %llu/64 bytes/sec\n",
			(unsigned long long)hctx->ccid3hctx_x);

	/*
	 * Set new timeout for the nofeedback timer.
	 * See comments in packet_recv() regarding the value of t_RTO.
	 */
	if (unlikely(hctx->ccid3hctx_t_rto == 0))	/* no feedback yet */
		t_nfb = TFRC_INITIAL_TIMEOUT;
	else
		t_nfb = max(hctx->ccid3hctx_t_rto, 2 * hctx->ccid3hctx_t_ipi);

restart_timer:
	sk_reset_timer(sk, &hctx->ccid3hctx_no_feedback_timer,
			   jiffies + usecs_to_jiffies(t_nfb));
out:
	bh_unlock_sock(sk);
	sock_put(sk);
}