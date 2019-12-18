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
struct ccid2_seq {int /*<<< orphan*/  ccid2s_sent; } ;
struct ccid2_hc_tx_sock {unsigned int ccid2hctx_cwnd; int /*<<< orphan*/  ccid2hctx_ssthresh; int /*<<< orphan*/  ccid2hctx_last_cong; } ;
struct TYPE_2__ {int dccps_l_ack_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccid2_change_l_ack_ratio (struct sock*,int) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  max (int,unsigned int) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccid2_congestion_event(struct sock *sk, struct ccid2_seq *seqp)
{
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);

	if (time_before(seqp->ccid2s_sent, hctx->ccid2hctx_last_cong)) {
		ccid2_pr_debug("Multiple losses in an RTT---treating as one\n");
		return;
	}

	hctx->ccid2hctx_last_cong = jiffies;

	hctx->ccid2hctx_cwnd     = hctx->ccid2hctx_cwnd / 2 ? : 1U;
	hctx->ccid2hctx_ssthresh = max(hctx->ccid2hctx_cwnd, 2U);

	/* Avoid spurious timeouts resulting from Ack Ratio > cwnd */
	if (dccp_sk(sk)->dccps_l_ack_ratio > hctx->ccid2hctx_cwnd)
		ccid2_change_l_ack_ratio(sk, hctx->ccid2hctx_cwnd);
}