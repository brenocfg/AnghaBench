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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int ia_rows; } ;
struct ath_hw {int /*<<< orphan*/ * analogBank6Data; TYPE_1__* eep_ops; TYPE_2__ iniBank6; } ;
struct ath9k_channel {int dummy; } ;
struct TYPE_3__ {int (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  EEP_DB_2 ; 
 int /*<<< orphan*/  EEP_DB_5 ; 
 int /*<<< orphan*/  EEP_MINOR_REV ; 
 int /*<<< orphan*/  EEP_OB_2 ; 
 int /*<<< orphan*/  EEP_OB_5 ; 
 int /*<<< orphan*/  INI_RA (TYPE_2__*,int,int) ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_WRITE_ARRAY (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ar5008_hw_phy_modify_rx_buffer (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5008_write_bank6 (struct ath_hw*,int*) ; 
 int /*<<< orphan*/  bank0 ; 
 int /*<<< orphan*/  bank1 ; 
 int /*<<< orphan*/  bank2 ; 
 int /*<<< orphan*/  bank3 ; 
 int /*<<< orphan*/  bank7 ; 
 int stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int stub3 (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int stub4 (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int stub5 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ar5008_hw_set_rf_regs(struct ath_hw *ah,
				  struct ath9k_channel *chan,
				  u16 modesIndex)
{
	u32 eepMinorRev;
	u32 ob5GHz = 0, db5GHz = 0;
	u32 ob2GHz = 0, db2GHz = 0;
	int regWrites = 0;
	int i;

	/*
	 * Software does not need to program bank data
	 * for single chip devices, that is AR9280 or anything
	 * after that.
	 */
	if (AR_SREV_9280_20_OR_LATER(ah))
		return true;

	/* Setup rf parameters */
	eepMinorRev = ah->eep_ops->get_eeprom(ah, EEP_MINOR_REV);

	for (i = 0; i < ah->iniBank6.ia_rows; i++)
		ah->analogBank6Data[i] = INI_RA(&ah->iniBank6, i, modesIndex);

	/* Only the 5 or 2 GHz OB/DB need to be set for a mode */
	if (eepMinorRev >= 2) {
		if (IS_CHAN_2GHZ(chan)) {
			ob2GHz = ah->eep_ops->get_eeprom(ah, EEP_OB_2);
			db2GHz = ah->eep_ops->get_eeprom(ah, EEP_DB_2);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       ob2GHz, 3, 197, 0);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       db2GHz, 3, 194, 0);
		} else {
			ob5GHz = ah->eep_ops->get_eeprom(ah, EEP_OB_5);
			db5GHz = ah->eep_ops->get_eeprom(ah, EEP_DB_5);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       ob5GHz, 3, 203, 0);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       db5GHz, 3, 200, 0);
		}
	}

	/* Write Analog registers */
	REG_WRITE_ARRAY(&bank0, 1, regWrites);
	REG_WRITE_ARRAY(&bank1, 1, regWrites);
	REG_WRITE_ARRAY(&bank2, 1, regWrites);
	REG_WRITE_ARRAY(&bank3, modesIndex, regWrites);
	ar5008_write_bank6(ah, &regWrites);
	REG_WRITE_ARRAY(&bank7, 1, regWrites);

	return true;
}