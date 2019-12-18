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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_LLH_CAM_MAX_PF_LINE ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 scalar_t__ BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  IS_MF_AFEX (struct bnx2x*) ; 
 int /*<<< orphan*/  IS_MF_SI (struct bnx2x*) ; 
 int NIG_REG_LLH0_FUNC_MEM ; 
 scalar_t__ NIG_REG_LLH0_FUNC_MEM_ENABLE ; 
 int NIG_REG_LLH1_FUNC_MEM ; 
 scalar_t__ NIG_REG_LLH1_FUNC_MEM_ENABLE ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bnx2x*,int,int*,int) ; 

void bnx2x_set_mac_in_nig(struct bnx2x *bp,
			  bool add, unsigned char *dev_addr, int index)
{
	u32 wb_data[2];
	u32 reg_offset = BP_PORT(bp) ? NIG_REG_LLH1_FUNC_MEM :
			 NIG_REG_LLH0_FUNC_MEM;

	if (!IS_MF_SI(bp) && !IS_MF_AFEX(bp))
		return;

	if (index > BNX2X_LLH_CAM_MAX_PF_LINE)
		return;

	DP(BNX2X_MSG_SP, "Going to %s LLH configuration at entry %d\n",
			 (add ? "ADD" : "DELETE"), index);

	if (add) {
		/* LLH_FUNC_MEM is a u64 WB register */
		reg_offset += 8*index;

		wb_data[0] = ((dev_addr[2] << 24) | (dev_addr[3] << 16) |
			      (dev_addr[4] <<  8) |  dev_addr[5]);
		wb_data[1] = ((dev_addr[0] <<  8) |  dev_addr[1]);

		REG_WR_DMAE(bp, reg_offset, wb_data, 2);
	}

	REG_WR(bp, (BP_PORT(bp) ? NIG_REG_LLH1_FUNC_MEM_ENABLE :
				  NIG_REG_LLH0_FUNC_MEM_ENABLE) + 4*index, add);
}