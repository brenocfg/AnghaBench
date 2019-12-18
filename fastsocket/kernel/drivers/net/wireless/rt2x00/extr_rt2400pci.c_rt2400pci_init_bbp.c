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
typedef  int u8 ;
typedef  int u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  EEPROM_BBP_REG_ID ; 
 unsigned int EEPROM_BBP_SIZE ; 
 scalar_t__ EEPROM_BBP_START ; 
 int /*<<< orphan*/  EEPROM_BBP_VALUE ; 
 int /*<<< orphan*/  rt2400pci_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2400pci_wait_bbp_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,scalar_t__,int*) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2400pci_init_bbp(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	if (unlikely(rt2400pci_wait_bbp_ready(rt2x00dev)))
		return -EACCES;

	rt2400pci_bbp_write(rt2x00dev, 1, 0x00);
	rt2400pci_bbp_write(rt2x00dev, 3, 0x27);
	rt2400pci_bbp_write(rt2x00dev, 4, 0x08);
	rt2400pci_bbp_write(rt2x00dev, 10, 0x0f);
	rt2400pci_bbp_write(rt2x00dev, 15, 0x72);
	rt2400pci_bbp_write(rt2x00dev, 16, 0x74);
	rt2400pci_bbp_write(rt2x00dev, 17, 0x20);
	rt2400pci_bbp_write(rt2x00dev, 18, 0x72);
	rt2400pci_bbp_write(rt2x00dev, 19, 0x0b);
	rt2400pci_bbp_write(rt2x00dev, 20, 0x00);
	rt2400pci_bbp_write(rt2x00dev, 28, 0x11);
	rt2400pci_bbp_write(rt2x00dev, 29, 0x04);
	rt2400pci_bbp_write(rt2x00dev, 30, 0x21);
	rt2400pci_bbp_write(rt2x00dev, 31, 0x00);

	for (i = 0; i < EEPROM_BBP_SIZE; i++) {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_BBP_START + i, &eeprom);

		if (eeprom != 0xffff && eeprom != 0x0000) {
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2400pci_bbp_write(rt2x00dev, reg_id, value);
		}
	}

	return 0;
}