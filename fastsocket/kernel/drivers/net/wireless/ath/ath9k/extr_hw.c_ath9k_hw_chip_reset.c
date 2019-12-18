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
struct ath_hw {int chip_fullsleep; TYPE_1__* eep_ops; } ;
struct ath9k_channel {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CR ; 
 int AR_CR_RXE ; 
 int /*<<< orphan*/  AR_Q_TXE ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 int ATH9K_RESET_COLD ; 
 int ATH9K_RESET_POWER_ON ; 
 int ATH9K_RESET_WARM ; 
 int /*<<< orphan*/  EEP_OL_PWRCTRL ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_internal_regulator_apply (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_pll (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_set_reset_reg (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_rfmode (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (struct ath_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath9k_hw_chip_reset(struct ath_hw *ah,
				struct ath9k_channel *chan)
{
	int reset_type = ATH9K_RESET_WARM;

	if (AR_SREV_9280(ah)) {
		if (ah->eep_ops->get_eeprom(ah, EEP_OL_PWRCTRL))
			reset_type = ATH9K_RESET_POWER_ON;
		else
			reset_type = ATH9K_RESET_COLD;
	} else if (ah->chip_fullsleep || REG_READ(ah, AR_Q_TXE) ||
		   (REG_READ(ah, AR_CR) & AR_CR_RXE))
		reset_type = ATH9K_RESET_COLD;

	if (!ath9k_hw_set_reset_reg(ah, reset_type))
		return false;

	if (!ath9k_hw_setpower(ah, ATH9K_PM_AWAKE))
		return false;

	ah->chip_fullsleep = false;

	if (AR_SREV_9330(ah))
		ar9003_hw_internal_regulator_apply(ah);
	ath9k_hw_init_pll(ah, chan);
	ath9k_hw_set_rfmode(ah, chan);

	return true;
}