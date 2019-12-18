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
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 TYPE_1__ eeprom_93c ; 
 unsigned char eeprom_93c_read () ; 
 unsigned char** z80_readmap ; 

__attribute__((used)) static unsigned char read_mapper_93c46(unsigned int address)
{
  if ((address == 0x8000) && eeprom_93c.enabled)
  {
    return eeprom_93c_read();
  }

  return z80_readmap[address >> 10][address & 0x03FF];
}