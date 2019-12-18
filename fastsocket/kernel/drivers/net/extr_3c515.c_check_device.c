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

/* Variables and functions */
 int /*<<< orphan*/  CORKSCREW_TOTAL_SIZE ; 
 scalar_t__ EEPROM_Read ; 
 unsigned int Wn0EepromCmd ; 
 unsigned int Wn0EepromData ; 
 int inw (unsigned int) ; 
 int /*<<< orphan*/  outw (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  release_region (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (unsigned int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int check_device(unsigned ioaddr)
{
	int timer;

	if (!request_region(ioaddr, CORKSCREW_TOTAL_SIZE, "3c515"))
		return 0;
	/* Check the resource configuration for a matching ioaddr. */
	if ((inw(ioaddr + 0x2002) & 0x1f0) != (ioaddr & 0x1f0)) {
		release_region(ioaddr, CORKSCREW_TOTAL_SIZE);
		return 0;
	}
	/* Verify by reading the device ID from the EEPROM. */
	outw(EEPROM_Read + 7, ioaddr + Wn0EepromCmd);
	/* Pause for at least 162 us. for the read to take place. */
	for (timer = 4; timer >= 0; timer--) {
		udelay(162);
		if ((inw(ioaddr + Wn0EepromCmd) & 0x0200) == 0)
			break;
	}
	if (inw(ioaddr + Wn0EepromData) != 0x6d50) {
		release_region(ioaddr, CORKSCREW_TOTAL_SIZE);
		return 0;
	}
	return 1;
}