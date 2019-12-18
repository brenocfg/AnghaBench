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
struct ccid2_hc_tx_sock {int ccid2hctx_seqbufc; int /*<<< orphan*/ * ccid2hctx_seqbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccid2_hc_tx_kill_rto_timer (struct sock*) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccid2_hc_tx_exit(struct sock *sk)
{
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);
	int i;

	ccid2_hc_tx_kill_rto_timer(sk);

	for (i = 0; i < hctx->ccid2hctx_seqbufc; i++)
		kfree(hctx->ccid2hctx_seqbuf[i]);
	hctx->ccid2hctx_seqbufc = 0;
}