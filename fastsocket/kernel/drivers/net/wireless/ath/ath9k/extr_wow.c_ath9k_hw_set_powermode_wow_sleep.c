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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  AR_CR ; 
 int AR_CR_RXD ; 
 int /*<<< orphan*/  AR_CR_RXE ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 int /*<<< orphan*/  AR_RXDP ; 
 scalar_t__ AR_SREV_9280_20 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_PWR_SAV ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_set_powermode_wow_sleep(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);

	/* set rx disable bit */
	REG_WRITE(ah, AR_CR, AR_CR_RXD);

	if (!ath9k_hw_wait(ah, AR_CR, AR_CR_RXE, 0, AH_WAIT_TIMEOUT)) {
		ath_err(common, "Failed to stop Rx DMA in 10ms AR_CR=0x%08x AR_DIAG_SW=0x%08x\n",
			REG_READ(ah, AR_CR), REG_READ(ah, AR_DIAG_SW));
		return;
	} else {
		if (!AR_SREV_9300_20_OR_LATER(ah))
			REG_WRITE(ah, AR_RXDP, 0x0);
	}

	/* AR9280 WoW has sleep issue, do not set it to sleep */
	if (AR_SREV_9280_20(ah))
		return;

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_ON_INT);
}