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
struct tcp_info {int /*<<< orphan*/  tcpi_rtt; int /*<<< orphan*/  tcpi_rto; } ;
struct sock {scalar_t__ sk_state; } ;
struct ccid3_hc_tx_sock {int /*<<< orphan*/  ccid3hctx_rtt; int /*<<< orphan*/  ccid3hctx_t_rto; } ;

/* Variables and functions */
 scalar_t__ DCCP_LISTEN ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 

__attribute__((used)) static void ccid3_hc_tx_get_info(struct sock *sk, struct tcp_info *info)
{
	struct ccid3_hc_tx_sock *hctx;

	/* Listen socks doesn't have a private CCID block */
	if (sk->sk_state == DCCP_LISTEN)
		return;

	hctx = ccid3_hc_tx_sk(sk);
	info->tcpi_rto = hctx->ccid3hctx_t_rto;
	info->tcpi_rtt = hctx->ccid3hctx_rtt;
}