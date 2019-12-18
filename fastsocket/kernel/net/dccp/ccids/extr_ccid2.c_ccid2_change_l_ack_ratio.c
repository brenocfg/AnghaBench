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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_l_ack_ratio; } ;
struct TYPE_2__ {int /*<<< orphan*/  ccid2hctx_cwnd; } ;

/* Variables and functions */
 scalar_t__ DCCPF_ACK_RATIO_MAX ; 
 int /*<<< orphan*/  DCCP_WARN (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*,scalar_t__) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static void ccid2_change_l_ack_ratio(struct sock *sk, u32 val)
{
	struct dccp_sock *dp = dccp_sk(sk);
	u32 max_ratio = DIV_ROUND_UP(ccid2_hc_tx_sk(sk)->ccid2hctx_cwnd, 2);

	/*
	 * Ensure that Ack Ratio does not exceed ceil(cwnd/2), which is (2) from
	 * RFC 4341, 6.1.2. We ignore the statement that Ack Ratio 2 is always
	 * acceptable since this causes starvation/deadlock whenever cwnd < 2.
	 * The same problem arises when Ack Ratio is 0 (ie. Ack Ratio disabled).
	 */
	if (val == 0 || val > max_ratio) {
		DCCP_WARN("Limiting Ack Ratio (%u) to %u\n", val, max_ratio);
		val = max_ratio;
	}
	if (val > DCCPF_ACK_RATIO_MAX)
		val = DCCPF_ACK_RATIO_MAX;

	if (val == dp->dccps_l_ack_ratio)
		return;

	ccid2_pr_debug("changing local ack ratio to %u\n", val);
	dp->dccps_l_ack_ratio = val;
}