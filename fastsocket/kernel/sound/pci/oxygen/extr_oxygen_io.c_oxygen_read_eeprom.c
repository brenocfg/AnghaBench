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
typedef  int /*<<< orphan*/  u16 ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int OXYGEN_EEPROM_BUSY ; 
 int /*<<< orphan*/  OXYGEN_EEPROM_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_EEPROM_DATA ; 
 unsigned int OXYGEN_EEPROM_DIR_READ ; 
 int /*<<< orphan*/  OXYGEN_EEPROM_STATUS ; 
 int /*<<< orphan*/  oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

u16 oxygen_read_eeprom(struct oxygen *chip, unsigned int index)
{
	unsigned int timeout;

	oxygen_write8(chip, OXYGEN_EEPROM_CONTROL,
		      index | OXYGEN_EEPROM_DIR_READ);
	for (timeout = 0; timeout < 100; ++timeout) {
		udelay(1);
		if (!(oxygen_read8(chip, OXYGEN_EEPROM_STATUS)
		      & OXYGEN_EEPROM_BUSY))
			break;
	}
	return oxygen_read16(chip, OXYGEN_EEPROM_DATA);
}