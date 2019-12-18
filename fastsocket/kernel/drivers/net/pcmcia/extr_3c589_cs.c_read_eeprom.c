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

/* Variables and functions */
 int EEPROM_BUSY ; 
 scalar_t__ EEPROM_READ ; 
 int inw (unsigned int) ; 
 int /*<<< orphan*/  outw (scalar_t__,unsigned int) ; 

__attribute__((used)) static u16 read_eeprom(unsigned int ioaddr, int index)
{
    int i;
    outw(EEPROM_READ + index, ioaddr + 10);
    /* Reading the eeprom takes 162 us */
    for (i = 1620; i >= 0; i--)
	if ((inw(ioaddr + 10) & EEPROM_BUSY) == 0)
	    break;
    return inw(ioaddr + 12);
}