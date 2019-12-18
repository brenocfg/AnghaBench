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
struct ar9300_base_eep_hdr {int miscConfiguration; } ;
struct ar9300_eeprom {struct ar9300_base_eep_hdr baseEepHeader; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_65NM_CH0_BIAS1 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_BIAS2 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_BIAS4 ; 
 int BIT (int /*<<< orphan*/ ) ; 
 unsigned long REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ar9003_hw_drive_strength_apply(struct ath_hw *ah)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	int drive_strength;
	unsigned long reg;

	drive_strength = pBase->miscConfiguration & BIT(0);
	if (!drive_strength)
		return;

	reg = REG_READ(ah, AR_PHY_65NM_CH0_BIAS1);
	reg &= ~0x00ffffc0;
	reg |= 0x5 << 21;
	reg |= 0x5 << 18;
	reg |= 0x5 << 15;
	reg |= 0x5 << 12;
	reg |= 0x5 << 9;
	reg |= 0x5 << 6;
	REG_WRITE(ah, AR_PHY_65NM_CH0_BIAS1, reg);

	reg = REG_READ(ah, AR_PHY_65NM_CH0_BIAS2);
	reg &= ~0xffffffe0;
	reg |= 0x5 << 29;
	reg |= 0x5 << 26;
	reg |= 0x5 << 23;
	reg |= 0x5 << 20;
	reg |= 0x5 << 17;
	reg |= 0x5 << 14;
	reg |= 0x5 << 11;
	reg |= 0x5 << 8;
	reg |= 0x5 << 5;
	REG_WRITE(ah, AR_PHY_65NM_CH0_BIAS2, reg);

	reg = REG_READ(ah, AR_PHY_65NM_CH0_BIAS4);
	reg &= ~0xff800000;
	reg |= 0x5 << 29;
	reg |= 0x5 << 26;
	reg |= 0x5 << 23;
	REG_WRITE(ah, AR_PHY_65NM_CH0_BIAS4, reg);
}