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
 int EEP_BUSY ; 
 int EEP_READ ; 
 scalar_t__ EepromCtrl ; 
 scalar_t__ EepromData ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int
read_eeprom (long ioaddr, int eep_addr)
{
	int i = 1000;
	outw (EEP_READ | (eep_addr & 0xff), ioaddr + EepromCtrl);
	while (i-- > 0) {
		if (!(inw (ioaddr + EepromCtrl) & EEP_BUSY)) {
			return inw (ioaddr + EepromData);
		}
	}
	return 0;
}