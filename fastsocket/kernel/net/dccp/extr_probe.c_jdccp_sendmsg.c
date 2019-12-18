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
struct msghdr {int dummy; } ;
struct kiocb {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  sport; int /*<<< orphan*/  saddr; } ;
struct ccid3_hc_tx_sock {int ccid3hctx_x_recv; int ccid3hctx_x; int /*<<< orphan*/  ccid3hctx_t_ipi; int /*<<< orphan*/  ccid3hctx_x_calc; int /*<<< orphan*/  ccid3hctx_p; int /*<<< orphan*/  ccid3hctx_rtt; int /*<<< orphan*/  ccid3hctx_s; } ;

/* Variables and functions */
 scalar_t__ DCCPC_CCID3 ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 scalar_t__ ccid_get_current_tx_ccid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  jprobe_return () ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  printl (char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,size_t,...) ; 

__attribute__((used)) static int jdccp_sendmsg(struct kiocb *iocb, struct sock *sk,
			 struct msghdr *msg, size_t size)
{
	const struct inet_sock *inet = inet_sk(sk);
	struct ccid3_hc_tx_sock *hctx = NULL;

	if (ccid_get_current_tx_ccid(dccp_sk(sk)) == DCCPC_CCID3)
		hctx = ccid3_hc_tx_sk(sk);

	if (port == 0 || ntohs(inet->dport) == port ||
	    ntohs(inet->sport) == port) {
		if (hctx)
			printl("%pI4:%u %pI4:%u %d %d %d %d %u "
			       "%llu %llu %d\n",
			       &inet->saddr, ntohs(inet->sport),
			       &inet->daddr, ntohs(inet->dport), size,
			       hctx->ccid3hctx_s, hctx->ccid3hctx_rtt,
			       hctx->ccid3hctx_p, hctx->ccid3hctx_x_calc,
			       hctx->ccid3hctx_x_recv >> 6,
			       hctx->ccid3hctx_x >> 6, hctx->ccid3hctx_t_ipi);
		else
			printl("%pI4:%u %pI4:%u %d\n",
			       &inet->saddr, ntohs(inet->sport),
			       &inet->daddr, ntohs(inet->dport), size);
	}

	jprobe_return();
	return 0;
}