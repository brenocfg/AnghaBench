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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  map4k; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_EEPROM_4K ; 
 int /*<<< orphan*/  ath9k_hw_usb_gen_fill_eeprom (struct ath_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __ath9k_hw_usb_4k_fill_eeprom(struct ath_hw *ah)
{
	u16 *eep_data = (u16 *)&ah->eeprom.map4k;

	ath9k_hw_usb_gen_fill_eeprom(ah, eep_data, 64, SIZE_EEPROM_4K);

	return true;
}