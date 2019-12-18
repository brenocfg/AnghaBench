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
typedef  int u32 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int const ETS_BW_LIMIT_CREDIT_WEIGHT ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1 ; 
 int /*<<< orphan*/  PBF_REG_COS0_WEIGHT ; 
 int /*<<< orphan*/  PBF_REG_COS1_WEIGHT ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_ets_bw_limit_common (struct link_params const*) ; 

void bnx2x_ets_bw_limit(const struct link_params *params, const u32 cos0_bw,
			const u32 cos1_bw)
{
	/* ETS disabled configuration*/
	struct bnx2x *bp = params->bp;
	const u32 total_bw = cos0_bw + cos1_bw;
	u32 cos0_credit_weight = 0;
	u32 cos1_credit_weight = 0;

	DP(NETIF_MSG_LINK, "ETS enabled BW limit configuration\n");

	if ((!total_bw) ||
	    (!cos0_bw) ||
	    (!cos1_bw)) {
		DP(NETIF_MSG_LINK, "Total BW can't be zero\n");
		return;
	}

	cos0_credit_weight = (cos0_bw * ETS_BW_LIMIT_CREDIT_WEIGHT)/
		total_bw;
	cos1_credit_weight = (cos1_bw * ETS_BW_LIMIT_CREDIT_WEIGHT)/
		total_bw;

	bnx2x_ets_bw_limit_common(params);

	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0, cos0_credit_weight);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1, cos1_credit_weight);

	REG_WR(bp, PBF_REG_COS0_WEIGHT, cos0_credit_weight);
	REG_WR(bp, PBF_REG_COS1_WEIGHT, cos1_credit_weight);
}