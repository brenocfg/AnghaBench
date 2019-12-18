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
struct ccid3_hc_tx_sock {int /*<<< orphan*/  ccid3hctx_hist; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_gss; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CRIT (char*) ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_hc_tx_update_s (struct ccid3_hc_tx_sock*,unsigned int) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 scalar_t__ tfrc_tx_hist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccid3_hc_tx_packet_sent(struct sock *sk, int more,
				    unsigned int len)
{
	struct ccid3_hc_tx_sock *hctx = ccid3_hc_tx_sk(sk);

	ccid3_hc_tx_update_s(hctx, len);

	if (tfrc_tx_hist_add(&hctx->ccid3hctx_hist, dccp_sk(sk)->dccps_gss))
		DCCP_CRIT("packet history - out of memory!");
}