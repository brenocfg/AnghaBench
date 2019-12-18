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
struct TYPE_2__ {int* bbram; int /*<<< orphan*/  eeprom; } ;

/* Variables and functions */
 TYPE_1__* hpc3c0 ; 
 unsigned short ip22_eeprom_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ip22_is_fullhouse () ; 

unsigned short ip22_nvram_read(int reg)
{
	if (ip22_is_fullhouse())
		/* IP22 (Indigo2 aka FullHouse) stores env variables into
		 * 93CS56 Microwire Bus EEPROM 2048 Bit (128x16) */
		return ip22_eeprom_read(&hpc3c0->eeprom, reg);
	else {
		unsigned short tmp;
		/* IP24 (Indy aka Guiness) uses DS1386 8K version */
		reg <<= 1;
		tmp = hpc3c0->bbram[reg++] & 0xff;
		return (tmp << 8) | (hpc3c0->bbram[reg] & 0xff);
	}
}