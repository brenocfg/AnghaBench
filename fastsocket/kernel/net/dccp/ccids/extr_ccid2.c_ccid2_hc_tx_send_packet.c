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
struct sk_buff {int dummy; } ;
struct ccid2_hc_tx_sock {scalar_t__ ccid2hctx_pipe; scalar_t__ ccid2hctx_cwnd; } ;

/* Variables and functions */
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 

__attribute__((used)) static int ccid2_hc_tx_send_packet(struct sock *sk, struct sk_buff *skb)
{
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);

	if (hctx->ccid2hctx_pipe < hctx->ccid2hctx_cwnd)
		return 0;

	return 1; /* XXX CCID should dequeue when ready instead of polling */
}