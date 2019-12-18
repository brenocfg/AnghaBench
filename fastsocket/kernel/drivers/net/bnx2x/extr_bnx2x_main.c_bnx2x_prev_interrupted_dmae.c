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
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN ; 
 int /*<<< orphan*/  PGLUE_B_REG_PGLUE_B_INT_STS ; 
 int /*<<< orphan*/  PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_prev_interrupted_dmae(struct bnx2x *bp)
{
	if (!CHIP_IS_E1x(bp)) {
		u32 val = REG_RD(bp, PGLUE_B_REG_PGLUE_B_INT_STS);
		if (val & PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN) {
			DP(BNX2X_MSG_SP,
			   "'was error' bit was found to be set in pglueb upon startup. Clearing\n");
			REG_WR(bp, PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR,
			       1 << BP_FUNC(bp));
		}
	}
}