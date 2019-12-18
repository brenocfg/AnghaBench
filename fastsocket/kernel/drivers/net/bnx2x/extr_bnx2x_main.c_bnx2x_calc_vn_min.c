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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cmng_enables; } ;
struct cmng_init_input {int* vnic_min_rate; TYPE_1__ flags; } ;
struct bnx2x {int* mf_config; } ;

/* Variables and functions */
 scalar_t__ BNX2X_IS_ETS_ENABLED (struct bnx2x*) ; 
 int BP_MAX_VN_NUM (struct bnx2x*) ; 
 int /*<<< orphan*/  CMNG_FLAGS_PER_PORT_FAIRNESS_VN ; 
 int DEF_MIN_RATE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int FUNC_MF_CFG_FUNC_HIDE ; 
 int FUNC_MF_CFG_MIN_BW_MASK ; 
 int FUNC_MF_CFG_MIN_BW_SHIFT ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int VN_0 ; 

__attribute__((used)) static void bnx2x_calc_vn_min(struct bnx2x *bp,
				      struct cmng_init_input *input)
{
	int all_zero = 1;
	int vn;

	for (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) {
		u32 vn_cfg = bp->mf_config[vn];
		u32 vn_min_rate = ((vn_cfg & FUNC_MF_CFG_MIN_BW_MASK) >>
				   FUNC_MF_CFG_MIN_BW_SHIFT) * 100;

		/* Skip hidden vns */
		if (vn_cfg & FUNC_MF_CFG_FUNC_HIDE)
			vn_min_rate = 0;
		/* If min rate is zero - set it to 1 */
		else if (!vn_min_rate)
			vn_min_rate = DEF_MIN_RATE;
		else
			all_zero = 0;

		input->vnic_min_rate[vn] = vn_min_rate;
	}

	/* if ETS or all min rates are zeros - disable fairness */
	if (BNX2X_IS_ETS_ENABLED(bp)) {
		input->flags.cmng_enables &=
					~CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
		DP(NETIF_MSG_IFUP, "Fairness will be disabled due to ETS\n");
	} else if (all_zero) {
		input->flags.cmng_enables &=
					~CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
		DP(NETIF_MSG_IFUP,
		   "All MIN values are zeroes fairness will be disabled\n");
	} else
		input->flags.cmng_enables |=
					CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
}