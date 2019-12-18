#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {int pcie_waen; } ;
struct TYPE_4__ {scalar_t__ ia_rows; } ;
struct ath_hw {TYPE_1__ config; TYPE_2__ iniPcieSerdes; } ;

/* Variables and functions */
 int AR9280_WA_DEFAULT ; 
 int AR9285_WA_DEFAULT ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL_ENA ; 
 int AR_PCIE_SERDES ; 
 int AR_PCIE_SERDES2 ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285E_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 int AR_WA ; 
 int AR_WA_BIT22 ; 
 int AR_WA_BIT23 ; 
 int AR_WA_BIT6 ; 
 int AR_WA_BIT7 ; 
 int AR_WA_D3_L1_DISABLE ; 
 int AR_WA_DEFAULT ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int INI_RA (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar9002_hw_configpcipowersave(struct ath_hw *ah,
					 bool power_off)
{
	u8 i;
	u32 val;

	/* Nothing to do on restore for 11N */
	if (!power_off /* !restore */) {
		if (AR_SREV_9280_20_OR_LATER(ah)) {
			/*
			 * AR9280 2.0 or later chips use SerDes values from the
			 * initvals.h initialized depending on chipset during
			 * __ath9k_hw_init()
			 */
			for (i = 0; i < ah->iniPcieSerdes.ia_rows; i++) {
				REG_WRITE(ah, INI_RA(&ah->iniPcieSerdes, i, 0),
					  INI_RA(&ah->iniPcieSerdes, i, 1));
			}
		} else {
			ENABLE_REGWRITE_BUFFER(ah);

			REG_WRITE(ah, AR_PCIE_SERDES, 0x9248fc00);
			REG_WRITE(ah, AR_PCIE_SERDES, 0x24924924);

			/* RX shut off when elecidle is asserted */
			REG_WRITE(ah, AR_PCIE_SERDES, 0x28000039);
			REG_WRITE(ah, AR_PCIE_SERDES, 0x53160824);
			REG_WRITE(ah, AR_PCIE_SERDES, 0xe5980579);

			/*
			 * Ignore ah->ah_config.pcie_clock_req setting for
			 * pre-AR9280 11n
			 */
			REG_WRITE(ah, AR_PCIE_SERDES, 0x001defff);

			REG_WRITE(ah, AR_PCIE_SERDES, 0x1aaabe40);
			REG_WRITE(ah, AR_PCIE_SERDES, 0xbe105554);
			REG_WRITE(ah, AR_PCIE_SERDES, 0x000e3007);

			/* Load the new settings */
			REG_WRITE(ah, AR_PCIE_SERDES2, 0x00000000);

			REGWRITE_BUFFER_FLUSH(ah);
		}

		udelay(1000);
	}

	if (power_off) {
		/* clear bit 19 to disable L1 */
		REG_CLR_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);

		val = REG_READ(ah, AR_WA);

		/*
		 * Set PCIe workaround bits
		 * In AR9280 and AR9285, bit 14 in WA register (disable L1)
		 * should only  be set when device enters D3 and be
		 * cleared when device comes back to D0.
		 */
		if (ah->config.pcie_waen) {
			if (ah->config.pcie_waen & AR_WA_D3_L1_DISABLE)
				val |= AR_WA_D3_L1_DISABLE;
		} else {
			if (((AR_SREV_9285(ah) ||
			      AR_SREV_9271(ah) ||
			      AR_SREV_9287(ah)) &&
			     (AR9285_WA_DEFAULT & AR_WA_D3_L1_DISABLE)) ||
			    (AR_SREV_9280(ah) &&
			     (AR9280_WA_DEFAULT & AR_WA_D3_L1_DISABLE))) {
				val |= AR_WA_D3_L1_DISABLE;
			}
		}

		if (AR_SREV_9280(ah) || AR_SREV_9285(ah) || AR_SREV_9287(ah)) {
			/*
			 * Disable bit 6 and 7 before entering D3 to
			 * prevent system hang.
			 */
			val &= ~(AR_WA_BIT6 | AR_WA_BIT7);
		}

		if (AR_SREV_9280(ah))
			val |= AR_WA_BIT22;

		if (AR_SREV_9285E_20(ah))
			val |= AR_WA_BIT23;

		REG_WRITE(ah, AR_WA, val);
	} else {
		if (ah->config.pcie_waen) {
			val = ah->config.pcie_waen;
			if (!power_off)
				val &= (~AR_WA_D3_L1_DISABLE);
		} else {
			if (AR_SREV_9285(ah) ||
			    AR_SREV_9271(ah) ||
			    AR_SREV_9287(ah)) {
				val = AR9285_WA_DEFAULT;
				if (!power_off)
					val &= (~AR_WA_D3_L1_DISABLE);
			}
			else if (AR_SREV_9280(ah)) {
				/*
				 * For AR9280 chips, bit 22 of 0x4004
				 * needs to be set.
				 */
				val = AR9280_WA_DEFAULT;
				if (!power_off)
					val &= (~AR_WA_D3_L1_DISABLE);
			} else {
				val = AR_WA_DEFAULT;
			}
		}

		/* WAR for ASPM system hang */
		if (AR_SREV_9285(ah) || AR_SREV_9287(ah))
			val |= (AR_WA_BIT6 | AR_WA_BIT7);

		if (AR_SREV_9285E_20(ah))
			val |= AR_WA_BIT23;

		REG_WRITE(ah, AR_WA, val);

		/* set bit 19 to allow forcing of pcie core into L1 state */
		REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
	}
}