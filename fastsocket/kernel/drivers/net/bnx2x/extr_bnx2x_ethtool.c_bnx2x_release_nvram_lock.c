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
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int BNX2X_NVRAM_TIMEOUT_COUNT ; 
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_NVRAM ; 
 int MCPR_NVM_SW_ARB_ARB_ARB1 ; 
 int MCPR_NVM_SW_ARB_ARB_REQ_CLR1 ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_SW_ARB ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_release_nvram_lock(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	int count, i;
	u32 val;

	/* adjust timeout for emulation/FPGA */
	count = BNX2X_NVRAM_TIMEOUT_COUNT;
	if (CHIP_REV_IS_SLOW(bp))
		count *= 100;

	/* relinquish nvram interface */
	REG_WR(bp, MCP_REG_MCPR_NVM_SW_ARB,
	       (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << port));

	for (i = 0; i < count*10; i++) {
		val = REG_RD(bp, MCP_REG_MCPR_NVM_SW_ARB);
		if (!(val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port)))
			break;

		udelay(5);
	}

	if (val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port)) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot free access to nvram interface\n");
		return -EBUSY;
	}

	/* release HW lock: protect against other PFs in PF Direct Assignment */
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_NVRAM);
	return 0;
}