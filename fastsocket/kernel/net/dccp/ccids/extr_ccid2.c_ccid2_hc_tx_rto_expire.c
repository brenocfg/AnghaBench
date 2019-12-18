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
struct ccid2_hc_tx_sock {int ccid2hctx_rto; int ccid2hctx_ssthresh; int ccid2hctx_cwnd; int ccid2hctx_rpdupack; scalar_t__ ccid2hctx_rpseq; scalar_t__ ccid2hctx_packets_acked; int /*<<< orphan*/  ccid2hctx_seqh; int /*<<< orphan*/  ccid2hctx_seqt; scalar_t__ ccid2hctx_pipe; int /*<<< orphan*/  ccid2hctx_rtotimer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  ccid2_change_l_ack_ratio (struct sock*,int) ; 
 int /*<<< orphan*/  ccid2_hc_tx_check_sanity (struct ccid2_hc_tx_sock*) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*) ; 
 int /*<<< orphan*/  ccid2_start_rto_timer (struct sock*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void ccid2_hc_tx_rto_expire(unsigned long data)
{
	struct sock *sk = (struct sock *)data;
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);
	long s;

	bh_lock_sock(sk);
	if (sock_owned_by_user(sk)) {
		sk_reset_timer(sk, &hctx->ccid2hctx_rtotimer,
			       jiffies + HZ / 5);
		goto out;
	}

	ccid2_pr_debug("RTO_EXPIRE\n");

	ccid2_hc_tx_check_sanity(hctx);

	/* back-off timer */
	hctx->ccid2hctx_rto <<= 1;

	s = hctx->ccid2hctx_rto / HZ;
	if (s > 60)
		hctx->ccid2hctx_rto = 60 * HZ;

	ccid2_start_rto_timer(sk);

	/* adjust pipe, cwnd etc */
	hctx->ccid2hctx_ssthresh = hctx->ccid2hctx_cwnd / 2;
	if (hctx->ccid2hctx_ssthresh < 2)
		hctx->ccid2hctx_ssthresh = 2;
	hctx->ccid2hctx_cwnd	 = 1;
	hctx->ccid2hctx_pipe	 = 0;

	/* clear state about stuff we sent */
	hctx->ccid2hctx_seqt = hctx->ccid2hctx_seqh;
	hctx->ccid2hctx_packets_acked = 0;

	/* clear ack ratio state. */
	hctx->ccid2hctx_rpseq	 = 0;
	hctx->ccid2hctx_rpdupack = -1;
	ccid2_change_l_ack_ratio(sk, 1);
	ccid2_hc_tx_check_sanity(hctx);
out:
	bh_unlock_sock(sk);
	sock_put(sk);
}