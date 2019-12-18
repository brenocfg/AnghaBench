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
 int /*<<< orphan*/  AH_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_AHB ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_EN ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 int /*<<< orphan*/  AR_RTC_RESET ; 
 int /*<<< orphan*/  AR_RTC_STATUS ; 
 int /*<<< orphan*/  AR_RTC_STATUS_M ; 
 int /*<<< orphan*/  AR_RTC_STATUS_ON ; 
 int /*<<< orphan*/  AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_WA ; 
 int /*<<< orphan*/  ATH9K_RESET_WARM ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_set_reset (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool ath9k_hw_set_reset_power_on(struct ath_hw *ah)
{
	ENABLE_REGWRITE_BUFFER(ah);

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	}

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN |
		  AR_RTC_FORCE_WAKE_ON_INT);

	if (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_RC, AR_RC_AHB);

	REG_WRITE(ah, AR_RTC_RESET, 0);

	REGWRITE_BUFFER_FLUSH(ah);

	if (!AR_SREV_9300_20_OR_LATER(ah))
		udelay(2);

	if (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_RC, 0);

	REG_WRITE(ah, AR_RTC_RESET, 1);

	if (!ath9k_hw_wait(ah,
			   AR_RTC_STATUS,
			   AR_RTC_STATUS_M,
			   AR_RTC_STATUS_ON,
			   AH_WAIT_TIMEOUT)) {
		ath_dbg(ath9k_hw_common(ah), RESET, "RTC not waking up\n");
		return false;
	}

	return ath9k_hw_set_reset(ah, ATH9K_RESET_WARM);
}