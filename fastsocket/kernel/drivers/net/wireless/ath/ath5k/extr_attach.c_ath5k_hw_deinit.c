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
struct ath5k_hw {int /*<<< orphan*/ * ah_rf_banks; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_STAT_INVALID ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_eeprom_detach (struct ath5k_hw*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void ath5k_hw_deinit(struct ath5k_hw *ah)
{
	__set_bit(ATH_STAT_INVALID, ah->status);

	if (ah->ah_rf_banks != NULL)
		kfree(ah->ah_rf_banks);

	ath5k_eeprom_detach(ah);

	/* assume interrupts are down */
}