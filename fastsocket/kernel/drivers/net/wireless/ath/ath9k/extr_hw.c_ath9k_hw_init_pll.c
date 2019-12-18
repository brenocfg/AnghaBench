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
struct ath_hw {scalar_t__ is_clk_25mhz; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CH0_BB_DPLL1 ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL1_NFRAC ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL1_NINI ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL1_REFDIV ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL2 ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL2_EN_NEGTRIG ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL2_LOCAL_PLL ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL2_OUTDIV ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL2_PLL_PWD ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL3 ; 
 int /*<<< orphan*/  AR_CH0_BB_DPLL3_PHASE_SHIFT ; 
 int AR_CH0_DDR_DPLL2 ; 
 int /*<<< orphan*/  AR_CH0_DDR_DPLL3 ; 
 int /*<<< orphan*/  AR_CH0_DPLL2_KD ; 
 int /*<<< orphan*/  AR_CH0_DPLL2_KI ; 
 int /*<<< orphan*/  AR_CH0_DPLL3_PHASE_SHIFT ; 
 int AR_PHY_PLL_CONTROL ; 
 int AR_PHY_PLL_MODE ; 
 int AR_RTC_DERIVED_CLK ; 
 int AR_RTC_FORCE_DERIVED_CLK ; 
 int AR_RTC_PLL_CONTROL ; 
 int AR_RTC_PLL_CONTROL2 ; 
 int AR_RTC_SLEEP_CLK ; 
 int AR_SLP32_INC ; 
 int AR_SLP32_MODE ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 int RTC_PLL_SETTLE_DELAY ; 
 int ath9k_hw_compute_pll_control (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ath9k_hw_init_pll(struct ath_hw *ah,
			      struct ath9k_channel *chan)
{
	u32 pll;

	if (AR_SREV_9485(ah) || AR_SREV_9565(ah)) {
		/* program BB PLL ki and kd value, ki=0x4, kd=0x40 */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_PLL_PWD, 0x1);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_DPLL2_KD, 0x40);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_DPLL2_KI, 0x4);

		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL1,
			      AR_CH0_BB_DPLL1_REFDIV, 0x5);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL1,
			      AR_CH0_BB_DPLL1_NINI, 0x58);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL1,
			      AR_CH0_BB_DPLL1_NFRAC, 0x0);

		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_OUTDIV, 0x1);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_LOCAL_PLL, 0x1);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_EN_NEGTRIG, 0x1);

		/* program BB PLL phase_shift to 0x6 */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL3,
			      AR_CH0_BB_DPLL3_PHASE_SHIFT, 0x6);

		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_PLL_PWD, 0x0);
		udelay(1000);
	} else if (AR_SREV_9330(ah)) {
		u32 ddr_dpll2, pll_control2, kd;

		if (ah->is_clk_25mhz) {
			ddr_dpll2 = 0x18e82f01;
			pll_control2 = 0xe04a3d;
			kd = 0x1d;
		} else {
			ddr_dpll2 = 0x19e82f01;
			pll_control2 = 0x886666;
			kd = 0x3d;
		}

		/* program DDR PLL ki and kd value */
		REG_WRITE(ah, AR_CH0_DDR_DPLL2, ddr_dpll2);

		/* program DDR PLL phase_shift */
		REG_RMW_FIELD(ah, AR_CH0_DDR_DPLL3,
			      AR_CH0_DPLL3_PHASE_SHIFT, 0x1);

		REG_WRITE(ah, AR_RTC_PLL_CONTROL, 0x1142c);
		udelay(1000);

		/* program refdiv, nint, frac to RTC register */
		REG_WRITE(ah, AR_RTC_PLL_CONTROL2, pll_control2);

		/* program BB PLL kd and ki value */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2, AR_CH0_DPLL2_KD, kd);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2, AR_CH0_DPLL2_KI, 0x06);

		/* program BB PLL phase_shift */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL3,
			      AR_CH0_BB_DPLL3_PHASE_SHIFT, 0x1);
	} else if (AR_SREV_9340(ah) || AR_SREV_9550(ah)) {
		u32 regval, pll2_divint, pll2_divfrac, refdiv;

		REG_WRITE(ah, AR_RTC_PLL_CONTROL, 0x1142c);
		udelay(1000);

		REG_SET_BIT(ah, AR_PHY_PLL_MODE, 0x1 << 16);
		udelay(100);

		if (ah->is_clk_25mhz) {
			pll2_divint = 0x54;
			pll2_divfrac = 0x1eb85;
			refdiv = 3;
		} else {
			if (AR_SREV_9340(ah)) {
				pll2_divint = 88;
				pll2_divfrac = 0;
				refdiv = 5;
			} else {
				pll2_divint = 0x11;
				pll2_divfrac = 0x26666;
				refdiv = 1;
			}
		}

		regval = REG_READ(ah, AR_PHY_PLL_MODE);
		regval |= (0x1 << 16);
		REG_WRITE(ah, AR_PHY_PLL_MODE, regval);
		udelay(100);

		REG_WRITE(ah, AR_PHY_PLL_CONTROL, (refdiv << 27) |
			  (pll2_divint << 18) | pll2_divfrac);
		udelay(100);

		regval = REG_READ(ah, AR_PHY_PLL_MODE);
		if (AR_SREV_9340(ah))
			regval = (regval & 0x80071fff) | (0x1 << 30) |
				 (0x1 << 13) | (0x4 << 26) | (0x18 << 19);
		else
			regval = (regval & 0x80071fff) | (0x3 << 30) |
				 (0x1 << 13) | (0x4 << 26) | (0x60 << 19);
		REG_WRITE(ah, AR_PHY_PLL_MODE, regval);
		REG_WRITE(ah, AR_PHY_PLL_MODE,
			  REG_READ(ah, AR_PHY_PLL_MODE) & 0xfffeffff);
		udelay(1000);
	}

	pll = ath9k_hw_compute_pll_control(ah, chan);
	if (AR_SREV_9565(ah))
		pll |= 0x40000;
	REG_WRITE(ah, AR_RTC_PLL_CONTROL, pll);

	if (AR_SREV_9485(ah) || AR_SREV_9340(ah) || AR_SREV_9330(ah) ||
	    AR_SREV_9550(ah))
		udelay(1000);

	/* Switch the core clock for ar9271 to 117Mhz */
	if (AR_SREV_9271(ah)) {
		udelay(500);
		REG_WRITE(ah, 0x50040, 0x304);
	}

	udelay(RTC_PLL_SETTLE_DELAY);

	REG_WRITE(ah, AR_RTC_SLEEP_CLK, AR_RTC_FORCE_DERIVED_CLK);

	if (AR_SREV_9340(ah) || AR_SREV_9550(ah)) {
		if (ah->is_clk_25mhz) {
			REG_WRITE(ah, AR_RTC_DERIVED_CLK, 0x17c << 1);
			REG_WRITE(ah, AR_SLP32_MODE, 0x0010f3d7);
			REG_WRITE(ah,  AR_SLP32_INC, 0x0001e7ae);
		} else {
			REG_WRITE(ah, AR_RTC_DERIVED_CLK, 0x261 << 1);
			REG_WRITE(ah, AR_SLP32_MODE, 0x0010f400);
			REG_WRITE(ah,  AR_SLP32_INC, 0x0001e800);
		}
		udelay(100);
	}
}