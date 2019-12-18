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
struct ath_hw {int WARegVal; int reset_power_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_EN ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_WA ; 
#define  ATH9K_RESET_COLD 130 
#define  ATH9K_RESET_POWER_ON 129 
#define  ATH9K_RESET_WARM 128 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int ath9k_hw_set_reset (struct ath_hw*,int) ; 
 int ath9k_hw_set_reset_power_on (struct ath_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool ath9k_hw_set_reset_reg(struct ath_hw *ah, u32 type)
{
	bool ret = false;

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	}

	REG_WRITE(ah, AR_RTC_FORCE_WAKE,
		  AR_RTC_FORCE_WAKE_EN | AR_RTC_FORCE_WAKE_ON_INT);

	if (!ah->reset_power_on)
		type = ATH9K_RESET_POWER_ON;

	switch (type) {
	case ATH9K_RESET_POWER_ON:
		ret = ath9k_hw_set_reset_power_on(ah);
		if (ret)
			ah->reset_power_on = true;
		break;
	case ATH9K_RESET_WARM:
	case ATH9K_RESET_COLD:
		ret = ath9k_hw_set_reset(ah, type);
		break;
	default:
		break;
	}

	return ret;
}