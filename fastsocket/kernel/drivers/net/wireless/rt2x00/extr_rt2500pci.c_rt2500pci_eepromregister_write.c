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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct eeprom_93cx6 {int /*<<< orphan*/  reg_chip_select; int /*<<< orphan*/  reg_data_clock; int /*<<< orphan*/  reg_data_out; int /*<<< orphan*/  reg_data_in; struct rt2x00_dev* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR21 ; 
 int /*<<< orphan*/  CSR21_EEPROM_CHIP_SELECT ; 
 int /*<<< orphan*/  CSR21_EEPROM_DATA_CLOCK ; 
 int /*<<< orphan*/  CSR21_EEPROM_DATA_IN ; 
 int /*<<< orphan*/  CSR21_EEPROM_DATA_OUT ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500pci_eepromregister_write(struct eeprom_93cx6 *eeprom)
{
	struct rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg = 0;

	rt2x00_set_field32(&reg, CSR21_EEPROM_DATA_IN, !!eeprom->reg_data_in);
	rt2x00_set_field32(&reg, CSR21_EEPROM_DATA_OUT, !!eeprom->reg_data_out);
	rt2x00_set_field32(&reg, CSR21_EEPROM_DATA_CLOCK,
			   !!eeprom->reg_data_clock);
	rt2x00_set_field32(&reg, CSR21_EEPROM_CHIP_SELECT,
			   !!eeprom->reg_chip_select);

	rt2x00mmio_register_write(rt2x00dev, CSR21, reg);
}