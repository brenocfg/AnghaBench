#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  T_EEPROM_SPI ;
struct TYPE_5__ {int out; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int custom; int on; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_OPCODE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ spi_eeprom ; 
 TYPE_1__ sram ; 

void eeprom_spi_init()
{
  /* reset eeprom state */
  memset(&spi_eeprom, 0, sizeof(T_EEPROM_SPI));
  spi_eeprom.out = 1;
  spi_eeprom.state = GET_OPCODE;

  /* enable backup RAM */
  sram.custom = 2;
  sram.on = 1;
}