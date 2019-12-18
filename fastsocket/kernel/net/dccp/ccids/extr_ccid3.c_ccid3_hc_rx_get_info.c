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
struct tcp_info {int /*<<< orphan*/  tcpi_rcv_rtt; int /*<<< orphan*/  tcpi_options; int /*<<< orphan*/  tcpi_ca_state; } ;
struct sock {scalar_t__ sk_state; } ;
struct ccid3_hc_rx_sock {int /*<<< orphan*/  ccid3hcrx_rtt; int /*<<< orphan*/  ccid3hcrx_state; } ;

/* Variables and functions */
 scalar_t__ DCCP_LISTEN ; 
 int /*<<< orphan*/  TCPI_OPT_TIMESTAMPS ; 
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 

__attribute__((used)) static void ccid3_hc_rx_get_info(struct sock *sk, struct tcp_info *info)
{
	const struct ccid3_hc_rx_sock *hcrx;

	/* Listen socks doesn't have a private CCID block */
	if (sk->sk_state == DCCP_LISTEN)
		return;

	hcrx = ccid3_hc_rx_sk(sk);
	info->tcpi_ca_state = hcrx->ccid3hcrx_state;
	info->tcpi_options  |= TCPI_OPT_TIMESTAMPS;
	info->tcpi_rcv_rtt  = hcrx->ccid3hcrx_rtt;
}