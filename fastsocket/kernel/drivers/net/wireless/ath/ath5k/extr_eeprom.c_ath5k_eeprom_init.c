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
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int ath5k_eeprom_init_header (struct ath5k_hw*) ; 
 int ath5k_eeprom_init_modes (struct ath5k_hw*) ; 
 int ath5k_eeprom_read_ctl_info (struct ath5k_hw*) ; 
 int ath5k_eeprom_read_pcal_info (struct ath5k_hw*) ; 
 int ath5k_eeprom_read_spur_chans (struct ath5k_hw*) ; 

int
ath5k_eeprom_init(struct ath5k_hw *ah)
{
	int err;

	err = ath5k_eeprom_init_header(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_init_modes(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_read_pcal_info(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_read_ctl_info(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_read_spur_chans(ah);
	if (err < 0)
		return err;

	return 0;
}