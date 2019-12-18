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
typedef  int u16 ;
struct pci_device_id {int subdevice; scalar_t__ driver_data; scalar_t__ vendor; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 scalar_t__ BROKEN_EEPROM_DRIVER_DATA ; 
 int /*<<< orphan*/  OXYGEN_FUNCTION ; 
 int /*<<< orphan*/  OXYGEN_FUNCTION_ENABLE_SPI_4_5 ; 
 int /*<<< orphan*/  oxygen_clear_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oxygen_read_eeprom (struct oxygen*,int) ; 

__attribute__((used)) static const struct pci_device_id *
oxygen_search_pci_id(struct oxygen *chip, const struct pci_device_id ids[])
{
	u16 subdevice;

	/*
	 * Make sure the EEPROM pins are available, i.e., not used for SPI.
	 * (This function is called before we initialize or use SPI.)
	 */
	oxygen_clear_bits8(chip, OXYGEN_FUNCTION,
			   OXYGEN_FUNCTION_ENABLE_SPI_4_5);
	/*
	 * Read the subsystem device ID directly from the EEPROM, because the
	 * chip didn't if the first EEPROM word was overwritten.
	 */
	subdevice = oxygen_read_eeprom(chip, 2);
	/* use default ID if EEPROM is missing */
	if (subdevice == 0xffff && oxygen_read_eeprom(chip, 1) == 0xffff)
		subdevice = 0x8788;
	/*
	 * We use only the subsystem device ID for searching because it is
	 * unique even without the subsystem vendor ID, which may have been
	 * overwritten in the EEPROM.
	 */
	for (; ids->vendor; ++ids)
		if (ids->subdevice == subdevice &&
		    ids->driver_data != BROKEN_EEPROM_DRIVER_DATA)
			return ids;
	return NULL;
}