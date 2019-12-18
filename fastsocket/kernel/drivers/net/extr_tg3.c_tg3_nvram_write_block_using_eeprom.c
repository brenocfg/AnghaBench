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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct tg3 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBUSY ; 
 int EEPROM_ADDR_ADDR_MASK ; 
 int EEPROM_ADDR_COMPLETE ; 
 int EEPROM_ADDR_DEVID_MASK ; 
 int EEPROM_ADDR_DEVID_SHIFT ; 
 int EEPROM_ADDR_READ ; 
 int EEPROM_ADDR_START ; 
 int EEPROM_ADDR_WRITE ; 
 int /*<<< orphan*/  GRC_EEPROM_ADDR ; 
 int /*<<< orphan*/  GRC_EEPROM_DATA ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int swab32 (int /*<<< orphan*/ ) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_nvram_write_block_using_eeprom(struct tg3 *tp,
				    u32 offset, u32 len, u8 *buf)
{
	int i, j, rc = 0;
	u32 val;

	for (i = 0; i < len; i += 4) {
		u32 addr;
		__be32 data;

		addr = offset + i;

		memcpy(&data, buf + i, 4);

		/*
		 * The SEEPROM interface expects the data to always be opposite
		 * the native endian format.  We accomplish this by reversing
		 * all the operations that would have been performed on the
		 * data from a call to tg3_nvram_read_be32().
		 */
		tw32(GRC_EEPROM_DATA, swab32(be32_to_cpu(data)));

		val = tr32(GRC_EEPROM_ADDR);
		tw32(GRC_EEPROM_ADDR, val | EEPROM_ADDR_COMPLETE);

		val &= ~(EEPROM_ADDR_ADDR_MASK | EEPROM_ADDR_DEVID_MASK |
			EEPROM_ADDR_READ);
		tw32(GRC_EEPROM_ADDR, val |
			(0 << EEPROM_ADDR_DEVID_SHIFT) |
			(addr & EEPROM_ADDR_ADDR_MASK) |
			EEPROM_ADDR_START |
			EEPROM_ADDR_WRITE);

		for (j = 0; j < 1000; j++) {
			val = tr32(GRC_EEPROM_ADDR);

			if (val & EEPROM_ADDR_COMPLETE)
				break;
			msleep(1);
		}
		if (!(val & EEPROM_ADDR_COMPLETE)) {
			rc = -EBUSY;
			break;
		}
	}

	return rc;
}