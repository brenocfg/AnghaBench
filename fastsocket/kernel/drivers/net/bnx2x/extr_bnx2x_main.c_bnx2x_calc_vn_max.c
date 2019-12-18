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
typedef  int u16 ;
struct cmng_init_input {int* vnic_max_rate; } ;
struct TYPE_2__ {int line_speed; } ;
struct bnx2x {int* mf_config; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int) ; 
 int FUNC_MF_CFG_FUNC_HIDE ; 
 scalar_t__ IS_MF_SI (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int bnx2x_extract_max_cfg (struct bnx2x*,int) ; 

__attribute__((used)) static void bnx2x_calc_vn_max(struct bnx2x *bp, int vn,
				    struct cmng_init_input *input)
{
	u16 vn_max_rate;
	u32 vn_cfg = bp->mf_config[vn];

	if (vn_cfg & FUNC_MF_CFG_FUNC_HIDE)
		vn_max_rate = 0;
	else {
		u32 maxCfg = bnx2x_extract_max_cfg(bp, vn_cfg);

		if (IS_MF_SI(bp)) {
			/* maxCfg in percents of linkspeed */
			vn_max_rate = (bp->link_vars.line_speed * maxCfg) / 100;
		} else /* SD modes */
			/* maxCfg is absolute in 100Mb units */
			vn_max_rate = maxCfg * 100;
	}

	DP(NETIF_MSG_IFUP, "vn %d: vn_max_rate %d\n", vn, vn_max_rate);

	input->vnic_max_rate[vn] = vn_max_rate;
}