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
struct ccid3_hc_tx_sock {int /*<<< orphan*/  ccid3hctx_hist; int /*<<< orphan*/  ccid3hctx_no_feedback_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFRC_SSTATE_TERM ; 
 int /*<<< orphan*/  ccid3_hc_tx_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_stop_timer (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfrc_tx_hist_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccid3_hc_tx_exit(struct sock *sk)
{
	struct ccid3_hc_tx_sock *hctx = ccid3_hc_tx_sk(sk);

	ccid3_hc_tx_set_state(sk, TFRC_SSTATE_TERM);
	sk_stop_timer(sk, &hctx->ccid3hctx_no_feedback_timer);

	tfrc_tx_hist_purge(&hctx->ccid3hctx_hist);
}