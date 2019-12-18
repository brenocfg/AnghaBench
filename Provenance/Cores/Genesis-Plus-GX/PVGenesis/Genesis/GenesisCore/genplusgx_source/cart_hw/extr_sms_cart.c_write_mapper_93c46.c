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
struct TYPE_2__ {unsigned char enabled; } ;

/* Variables and functions */
 TYPE_1__ eeprom_93c ; 
 int /*<<< orphan*/  eeprom_93c_init () ; 
 int /*<<< orphan*/  eeprom_93c_write (unsigned char) ; 
 int /*<<< orphan*/  mapper_16k_w (unsigned int,unsigned char) ; 
 unsigned char** z80_writemap ; 

__attribute__((used)) static void write_mapper_93c46(unsigned int address, unsigned char data)
{
  /* EEPROM serial input */
  if ((address == 0x8000) && eeprom_93c.enabled)
  {
    eeprom_93c_write(data);
    return;
  }

  /* EEPROM ctrl */
  if (address == 0xFFFC)
  {
    /* enable/disable EEPROM */
    eeprom_93c.enabled = data & 0x08;

    if (data & 0x80)
    {
      /* reset EEPROM */
      eeprom_93c_init();
    }
  }

  /* SEGA mapper compatibility */
  if (address > 0xFFFC)
  {
    mapper_16k_w(address & 3, data);
  }

  z80_writemap[address >> 10][address & 0x03FF] = data;
}