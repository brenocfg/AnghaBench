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
typedef  int /*<<< orphan*/  u32 ;
struct brcms_hardware {int sbclk; int clk; int /*<<< orphan*/  d11core; int /*<<< orphan*/  corerev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int PDBG_RFD ; 
 int /*<<< orphan*/  SICF_PCLKE ; 
 int /*<<< orphan*/  bcma_core_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_core_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_xtal (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_mctrl_reset (struct brcms_hardware*) ; 
 int /*<<< orphan*/  phydebug ; 

__attribute__((used)) static bool brcms_b_radio_read_hwdisabled(struct brcms_hardware *wlc_hw)
{
	bool v, clk, xtal;
	u32 flags = 0;

	xtal = wlc_hw->sbclk;
	if (!xtal)
		brcms_b_xtal(wlc_hw, ON);

	/* may need to take core out of reset first */
	clk = wlc_hw->clk;
	if (!clk) {
		/*
		 * mac no longer enables phyclk automatically when driver
		 * accesses phyreg throughput mac. This can be skipped since
		 * only mac reg is accessed below
		 */
		if (D11REV_GE(wlc_hw->corerev, 18))
			flags |= SICF_PCLKE;

		/*
		 * TODO: test suspend/resume
		 *
		 * AI chip doesn't restore bar0win2 on
		 * hibernation/resume, need sw fixup
		 */

		bcma_core_enable(wlc_hw->d11core, flags);
		brcms_c_mctrl_reset(wlc_hw);
	}

	v = ((bcma_read32(wlc_hw->d11core,
			  D11REGOFFS(phydebug)) & PDBG_RFD) != 0);

	/* put core back into reset */
	if (!clk)
		bcma_core_disable(wlc_hw->d11core, 0);

	if (!xtal)
		brcms_b_xtal(wlc_hw, OFF);

	return v;
}