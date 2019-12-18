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
struct ccid2_hc_tx_sock {long ccid2hctx_srtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccid2_pr_debug (char*,long) ; 

__attribute__((used)) static void ccid2_change_srtt(struct ccid2_hc_tx_sock *hctx, long val)
{
	ccid2_pr_debug("change SRTT to %ld\n", val);
	hctx->ccid2hctx_srtt = val;
}