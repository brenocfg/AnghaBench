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
struct ccid2_hc_tx_sock {scalar_t__ ccid2hctx_rto; int /*<<< orphan*/  ccid2hctx_rtotimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccid2_start_rto_timer(struct sock *sk)
{
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);

	ccid2_pr_debug("setting RTO timeout=%ld\n", hctx->ccid2hctx_rto);

	BUG_ON(timer_pending(&hctx->ccid2hctx_rtotimer));
	sk_reset_timer(sk, &hctx->ccid2hctx_rtotimer,
		       jiffies + hctx->ccid2hctx_rto);
}