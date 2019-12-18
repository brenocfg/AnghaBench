#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8 ;
typedef  size_t uint16 ;
struct TYPE_4__ {int size_mask; unsigned char sda_out_bit; } ;
struct TYPE_6__ {unsigned char sda; int state; int cycles; int slave_mask; int word_address; TYPE_1__ config; } ;
struct TYPE_5__ {int* sram; } ;

/* Variables and functions */
#define  GET_SLAVE_ADR 133 
#define  GET_WORD_ADR_7BITS 132 
#define  GET_WORD_ADR_HIGH 131 
#define  GET_WORD_ADR_LOW 130 
#define  READ_DATA 129 
#define  WRITE_DATA 128 
 TYPE_3__ eeprom_i2c ; 
 TYPE_2__ sram ; 

__attribute__((used)) static unsigned char eeprom_i2c_out(void)
{
  uint8 sda_out = eeprom_i2c.sda;

  /* EEPROM state */
  switch (eeprom_i2c.state)
  {
    case READ_DATA:
    {
      if (eeprom_i2c.cycles < 9)
      {
        /* Return DATA bits (max 64kBytes) */
        uint16 sram_address = (eeprom_i2c.slave_mask | eeprom_i2c.word_address) & 0xffff;
        sda_out = (sram.sram[sram_address] >> (8 - eeprom_i2c.cycles)) & 1;

        if (eeprom_i2c.cycles == 8)
        {
          /* WORD ADDRESS is incremented (roll up at maximum array size) */
          eeprom_i2c.word_address ++;
          eeprom_i2c.word_address &= eeprom_i2c.config.size_mask;
        }
      }
      break;
    }

    case GET_WORD_ADR_7BITS:
    case GET_SLAVE_ADR:
    case GET_WORD_ADR_HIGH:
    case GET_WORD_ADR_LOW:
    case WRITE_DATA:
    {
      if (eeprom_i2c.cycles == 9) sda_out = 0;
      break;
    }

    default:
    {
      break;
    }
  }

  return (sda_out << eeprom_i2c.config.sda_out_bit);
}