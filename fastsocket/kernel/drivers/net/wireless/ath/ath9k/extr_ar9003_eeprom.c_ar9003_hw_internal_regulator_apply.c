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
struct ar9300_base_eep_hdr {int featureEnable; int /*<<< orphan*/  swreg; } ;
struct ar9300_eeprom {struct ar9300_base_eep_hdr baseEepHeader; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {scalar_t__ is_clk_25mhz; TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_PMU1 ; 
 int AR_PHY_PMU1_PWD ; 
 int /*<<< orphan*/  AR_PHY_PMU2 ; 
 int AR_PHY_PMU2_PGM ; 
 int AR_RTC_FORCE_SWREG_PRD ; 
 int /*<<< orphan*/  AR_RTC_REG_CONTROL0 ; 
 int /*<<< orphan*/  AR_RTC_REG_CONTROL1 ; 
 int AR_RTC_REG_CONTROL1_SWREG_PROGRAM ; 
 int /*<<< orphan*/  AR_RTC_SLEEP_CLK ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int BIT (int) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_pmu_set (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ar9003_hw_internal_regulator_apply(struct ath_hw *ah)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	u32 reg_val;

	if (pBase->featureEnable & BIT(4)) {
		if (AR_SREV_9330(ah) || AR_SREV_9485(ah)) {
			int reg_pmu_set;

			reg_pmu_set = REG_READ(ah, AR_PHY_PMU2) & ~AR_PHY_PMU2_PGM;
			REG_WRITE(ah, AR_PHY_PMU2, reg_pmu_set);
			if (!is_pmu_set(ah, AR_PHY_PMU2, reg_pmu_set))
				return;

			if (AR_SREV_9330(ah)) {
				if (ah->is_clk_25mhz) {
					reg_pmu_set = (3 << 1) | (8 << 4) |
						      (3 << 8) | (1 << 14) |
						      (6 << 17) | (1 << 20) |
						      (3 << 24);
				} else {
					reg_pmu_set = (4 << 1)  | (7 << 4) |
						      (3 << 8)  | (1 << 14) |
						      (6 << 17) | (1 << 20) |
						      (3 << 24);
				}
			} else {
				reg_pmu_set = (5 << 1) | (7 << 4) |
					      (2 << 8) | (2 << 14) |
					      (6 << 17) | (1 << 20) |
					      (3 << 24) | (1 << 28);
			}

			REG_WRITE(ah, AR_PHY_PMU1, reg_pmu_set);
			if (!is_pmu_set(ah, AR_PHY_PMU1, reg_pmu_set))
				return;

			reg_pmu_set = (REG_READ(ah, AR_PHY_PMU2) & ~0xFFC00000)
					| (4 << 26);
			REG_WRITE(ah, AR_PHY_PMU2, reg_pmu_set);
			if (!is_pmu_set(ah, AR_PHY_PMU2, reg_pmu_set))
				return;

			reg_pmu_set = (REG_READ(ah, AR_PHY_PMU2) & ~0x00200000)
					| (1 << 21);
			REG_WRITE(ah, AR_PHY_PMU2, reg_pmu_set);
			if (!is_pmu_set(ah, AR_PHY_PMU2, reg_pmu_set))
				return;
		} else if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
			reg_val = le32_to_cpu(pBase->swreg);
			REG_WRITE(ah, AR_PHY_PMU1, reg_val);
		} else {
			/* Internal regulator is ON. Write swreg register. */
			reg_val = le32_to_cpu(pBase->swreg);
			REG_WRITE(ah, AR_RTC_REG_CONTROL1,
				  REG_READ(ah, AR_RTC_REG_CONTROL1) &
				  (~AR_RTC_REG_CONTROL1_SWREG_PROGRAM));
			REG_WRITE(ah, AR_RTC_REG_CONTROL0, reg_val);
			/* Set REG_CONTROL1.SWREG_PROGRAM */
			REG_WRITE(ah, AR_RTC_REG_CONTROL1,
				  REG_READ(ah,
					   AR_RTC_REG_CONTROL1) |
					   AR_RTC_REG_CONTROL1_SWREG_PROGRAM);
		}
	} else {
		if (AR_SREV_9330(ah) || AR_SREV_9485(ah)) {
			REG_RMW_FIELD(ah, AR_PHY_PMU2, AR_PHY_PMU2_PGM, 0);
			while (REG_READ_FIELD(ah, AR_PHY_PMU2,
						AR_PHY_PMU2_PGM))
				udelay(10);

			REG_RMW_FIELD(ah, AR_PHY_PMU1, AR_PHY_PMU1_PWD, 0x1);
			while (!REG_READ_FIELD(ah, AR_PHY_PMU1,
						AR_PHY_PMU1_PWD))
				udelay(10);
			REG_RMW_FIELD(ah, AR_PHY_PMU2, AR_PHY_PMU2_PGM, 0x1);
			while (!REG_READ_FIELD(ah, AR_PHY_PMU2,
						AR_PHY_PMU2_PGM))
				udelay(10);
		} else if (AR_SREV_9462(ah) || AR_SREV_9565(ah))
			REG_RMW_FIELD(ah, AR_PHY_PMU1, AR_PHY_PMU1_PWD, 0x1);
		else {
			reg_val = REG_READ(ah, AR_RTC_SLEEP_CLK) |
				AR_RTC_FORCE_SWREG_PRD;
			REG_WRITE(ah, AR_RTC_SLEEP_CLK, reg_val);
		}
	}

}