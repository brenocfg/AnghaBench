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
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_REG_LCPLL_E40_PWRDWN ; 
 int /*<<< orphan*/  MISC_REG_LCPLL_E40_RESETB_ANA ; 
 int /*<<< orphan*/  MISC_REG_LCPLL_E40_RESETB_DIG ; 
 int /*<<< orphan*/  MISC_REG_WC0_RESET ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_warpcore_power_module (struct link_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_warpcore_hw_reset(struct bnx2x_phy *phy,
				    struct link_params *params)
{
	struct bnx2x *bp = params->bp;
	bnx2x_warpcore_power_module(params, 0);
	/* Put Warpcore in low power mode */
	REG_WR(bp, MISC_REG_WC0_RESET, 0x0c0e);

	/* Put LCPLL in low power mode */
	REG_WR(bp, MISC_REG_LCPLL_E40_PWRDWN, 1);
	REG_WR(bp, MISC_REG_LCPLL_E40_RESETB_ANA, 0);
	REG_WR(bp, MISC_REG_LCPLL_E40_RESETB_DIG, 0);
}