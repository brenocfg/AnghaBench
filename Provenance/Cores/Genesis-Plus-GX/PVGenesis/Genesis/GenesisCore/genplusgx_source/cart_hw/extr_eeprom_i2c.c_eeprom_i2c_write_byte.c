#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int sda_in_adr; unsigned int sda_in_bit; unsigned int scl_adr; unsigned int scl_bit; } ;
struct TYPE_4__ {unsigned int sda; unsigned int scl; TYPE_1__ config; } ;

/* Variables and functions */
 TYPE_2__ eeprom_i2c ; 
 int /*<<< orphan*/  eeprom_i2c_update () ; 
 int /*<<< orphan*/  m68k_unused_8_w (unsigned int,unsigned int) ; 

__attribute__((used)) static void eeprom_i2c_write_byte(unsigned int address, unsigned int data)
{
  int do_update = 0;

  if (address == eeprom_i2c.config.sda_in_adr)
  {
    eeprom_i2c.sda = (data >> eeprom_i2c.config.sda_in_bit) & 1;
    do_update = 1;
  }

  if (address == eeprom_i2c.config.scl_adr)
  {
    eeprom_i2c.scl = (data >> eeprom_i2c.config.scl_bit) & 1;
    do_update = 1;
  }

  if (do_update)
  {
    eeprom_i2c_update();
    return;
  }

  m68k_unused_8_w(address, data);
}