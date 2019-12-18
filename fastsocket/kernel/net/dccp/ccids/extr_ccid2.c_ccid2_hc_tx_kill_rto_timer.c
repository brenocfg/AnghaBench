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
struct ccid2_hc_tx_sock {int /*<<< orphan*/  ccid2hctx_rtotimer; } ;

/* Variables and functions */
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*) ; 
 int /*<<< orphan*/  sk_stop_timer (struct sock*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccid2_hc_tx_kill_rto_timer(struct sock *sk)
{
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);

	sk_stop_timer(sk, &hctx->ccid2hctx_rtotimer);
	ccid2_pr_debug("deleted RTO timer\n");
}