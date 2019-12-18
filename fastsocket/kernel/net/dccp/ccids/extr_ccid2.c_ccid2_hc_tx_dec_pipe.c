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
struct ccid2_hc_tx_sock {scalar_t__ ccid2hctx_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG (char*) ; 
 int /*<<< orphan*/  ccid2_hc_tx_kill_rto_timer (struct sock*) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 

__attribute__((used)) static void ccid2_hc_tx_dec_pipe(struct sock *sk)
{
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);

	if (hctx->ccid2hctx_pipe == 0)
		DCCP_BUG("pipe == 0");
	else
		hctx->ccid2hctx_pipe--;

	if (hctx->ccid2hctx_pipe == 0)
		ccid2_hc_tx_kill_rto_timer(sk);
}