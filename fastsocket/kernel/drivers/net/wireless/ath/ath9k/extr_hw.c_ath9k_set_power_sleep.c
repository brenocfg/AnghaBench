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
struct ath_hw {int WARegVal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_MSG_EN ; 
 int /*<<< orphan*/  AR_NDP2_TIMER_MODE ; 
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_AHB ; 
 int AR_RC_HOSTIF ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_EN ; 
 int /*<<< orphan*/  AR_RTC_RESET ; 
 int AR_RTC_RESET_EN ; 
 int /*<<< orphan*/  AR_SLP32_INC ; 
 int /*<<< orphan*/  AR_SREV_5416 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9100 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_PWR_SAV ; 
 int /*<<< orphan*/  AR_TIMER_MODE ; 
 int /*<<< orphan*/  AR_WA ; 
 int AR_WA_D3_L1_DISABLE ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ath9k_set_power_sleep(struct ath_hw *ah)
{
	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		REG_CLR_BIT(ah, AR_TIMER_MODE, 0xff);
		REG_CLR_BIT(ah, AR_NDP2_TIMER_MODE, 0xff);
		REG_CLR_BIT(ah, AR_SLP32_INC, 0xfffff);
		/* xxx Required for WLAN only case ? */
		REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_EN, 0);
		udelay(100);
	}

	/*
	 * Clear the RTC force wake bit to allow the
	 * mac to go to sleep.
	 */
	REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN);

	if (ath9k_hw_mci_is_enabled(ah))
		udelay(100);

	if (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_RC, AR_RC_AHB | AR_RC_HOSTIF);

	/* Shutdown chip. Active low */
	if (!AR_SREV_5416(ah) && !AR_SREV_9271(ah)) {
		REG_CLR_BIT(ah, AR_RTC_RESET, AR_RTC_RESET_EN);
		udelay(2);
	}

	/* Clear Bit 14 of AR_WA after putting chip into Full Sleep mode. */
	if (AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_WA, ah->WARegVal & ~AR_WA_D3_L1_DISABLE);
}