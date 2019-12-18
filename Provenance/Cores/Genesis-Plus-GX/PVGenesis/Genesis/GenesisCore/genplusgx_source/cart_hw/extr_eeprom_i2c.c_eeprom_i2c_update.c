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
typedef  size_t uint16 ;
struct TYPE_4__ {int size_mask; int address_bits; int pagewrite_mask; } ;
struct TYPE_6__ {int state; int cycles; int word_address; int old_sda; int rw; int slave_mask; int sda; int /*<<< orphan*/  scl; int /*<<< orphan*/  old_scl; TYPE_1__ config; } ;
struct TYPE_5__ {int* sram; } ;

/* Variables and functions */
 int /*<<< orphan*/  Detect_START () ; 
 int /*<<< orphan*/  Detect_STOP () ; 
#define  GET_SLAVE_ADR 135 
#define  GET_WORD_ADR_7BITS 134 
#define  GET_WORD_ADR_HIGH 133 
#define  GET_WORD_ADR_LOW 132 
#define  READ_DATA 131 
#define  STAND_BY 130 
#define  WAIT_STOP 129 
#define  WRITE_DATA 128 
 TYPE_3__ eeprom_i2c ; 
 TYPE_2__ sram ; 

__attribute__((used)) static void eeprom_i2c_update(void)
{
  /* EEPROM current state */
  switch (eeprom_i2c.state)
  {
    /* Standby Mode */
    case STAND_BY:
    {
      Detect_START();
      Detect_STOP();
      break;
    }

    /* Suspended Mode */
    case WAIT_STOP:
    {
      Detect_STOP();
      break;
    }

    /* Get Word Address 7 bits: MODE-1 only (24C01)
     * and R/W bit
     */
    case GET_WORD_ADR_7BITS:
    {
      Detect_START();
      Detect_STOP();

      /* look for SCL LOW to HIGH transition */
      if (!eeprom_i2c.old_scl && eeprom_i2c.scl)
      {
        if (eeprom_i2c.cycles == 0) eeprom_i2c.cycles ++;
      }


      /* look for SCL HIGH to LOW transition */
      if (eeprom_i2c.old_scl && !eeprom_i2c.scl && (eeprom_i2c.cycles > 0))
      {
        if (eeprom_i2c.cycles < 8)
        {
          eeprom_i2c.word_address |= (eeprom_i2c.old_sda << (7 - eeprom_i2c.cycles));
        }
        else if (eeprom_i2c.cycles == 8)
        {
          eeprom_i2c.rw = eeprom_i2c.old_sda;
        }
        else
        {  /* ACK CYCLE */
          eeprom_i2c.cycles = 0;
          eeprom_i2c.word_address &= eeprom_i2c.config.size_mask;
          eeprom_i2c.state = eeprom_i2c.rw ? READ_DATA : WRITE_DATA;
        }

        eeprom_i2c.cycles ++;
      }
      break;
    }

    /* Get Slave Address (3bits) : MODE-2 & MODE-3 only (24C01 - 24C512) (0-3bits, depending on the array size)
     * or/and Word Address MSB: MODE-2 only (24C04 - 24C16) (0-3bits, depending on the array size)
     * and R/W bit
     */
    case GET_SLAVE_ADR:
    {
      Detect_START();
      Detect_STOP();

      /* look for SCL LOW to HIGH transition */
      if (!eeprom_i2c.old_scl && eeprom_i2c.scl)
      {
        if (eeprom_i2c.cycles == 0) eeprom_i2c.cycles ++;
      }

      /* look for SCL HIGH to LOW transition */
      if (eeprom_i2c.old_scl && !eeprom_i2c.scl && (eeprom_i2c.cycles > 0))
      {
        if ((eeprom_i2c.cycles > 4) && (eeprom_i2c.cycles <8))
        {
          if ((eeprom_i2c.config.address_bits == 16) ||
            (eeprom_i2c.config.size_mask < (1 << (15 - eeprom_i2c.cycles))))
          {
            /* this is a SLAVE ADDRESS bit */
            eeprom_i2c.slave_mask |= (eeprom_i2c.old_sda << (7 - eeprom_i2c.cycles));
          }
          else
          {
            /* this is a WORD ADDRESS high bit */
            if (eeprom_i2c.old_sda) eeprom_i2c.word_address |= (1 << (15 - eeprom_i2c.cycles));
            else eeprom_i2c.word_address &= ~(1 << (15 - eeprom_i2c.cycles));
          }
        }
        else if (eeprom_i2c.cycles == 8) eeprom_i2c.rw = eeprom_i2c.old_sda;
        else if (eeprom_i2c.cycles > 8)
        {
          /* ACK CYCLE */
          eeprom_i2c.cycles = 0;
          if (eeprom_i2c.config.address_bits == 16)
          {
            /* two ADDRESS bytes */
            eeprom_i2c.state = eeprom_i2c.rw ? READ_DATA : GET_WORD_ADR_HIGH;
            eeprom_i2c.slave_mask <<= 16;
          }
          else
          {
            /* one ADDRESS byte */
            eeprom_i2c.state = eeprom_i2c.rw ? READ_DATA : GET_WORD_ADR_LOW;
            eeprom_i2c.slave_mask <<= 8;
          }
        }

        eeprom_i2c.cycles ++;
      }
      break;
    }

    /* Get Word Address MSB (4-8bits depending on the array size)
     * MODE-3 only (24C32 - 24C512)
     */
    case GET_WORD_ADR_HIGH:
    {
      Detect_START();
      Detect_STOP();

      /* look for SCL HIGH to LOW transition */
      if (eeprom_i2c.old_scl && !eeprom_i2c.scl)
      {
        if (eeprom_i2c.cycles < 9)
        {
          if ((eeprom_i2c.config.size_mask + 1) < (1 << (17 - eeprom_i2c.cycles)))
          {
            /* ignored bit: slave mask should be right-shifted by one  */
            eeprom_i2c.slave_mask >>= 1;
          }
          else
          {
            /* this is a WORD ADDRESS high bit */
            if (eeprom_i2c.old_sda) eeprom_i2c.word_address |= (1 << (16 - eeprom_i2c.cycles));
            else eeprom_i2c.word_address &= ~(1 << (16 - eeprom_i2c.cycles));
          }

          eeprom_i2c.cycles ++;
        }
        else
        {
          /* ACK CYCLE */
          eeprom_i2c.cycles = 1;
          eeprom_i2c.state = GET_WORD_ADR_LOW;
        }
      }
      break;
    }

    /* Get Word Address LSB: 7bits (24C01) or 8bits (24C02-24C512)
     * MODE-2 and MODE-3 only (24C01 - 24C512)
     */
    case GET_WORD_ADR_LOW: 
    {
      Detect_START();
      Detect_STOP();

      /* look for SCL HIGH to LOW transition */
      if (eeprom_i2c.old_scl && !eeprom_i2c.scl)
      {
        if (eeprom_i2c.cycles < 9)
        {
          if ((eeprom_i2c.config.size_mask + 1) < (1 << (9 - eeprom_i2c.cycles)))
          {
            /* ignored bit (X24C01): slave mask should be right-shifted by one  */
            eeprom_i2c.slave_mask >>= 1;
          }
          else
          {
            /* this is a WORD ADDRESS high bit */
            if (eeprom_i2c.old_sda) eeprom_i2c.word_address |= (1 << (8 - eeprom_i2c.cycles));
            else eeprom_i2c.word_address &= ~(1 << (8 - eeprom_i2c.cycles));
          }

          eeprom_i2c.cycles ++;
        }
        else
        {
          /* ACK CYCLE */
          eeprom_i2c.cycles = 1;
          eeprom_i2c.word_address &= eeprom_i2c.config.size_mask;
          eeprom_i2c.state = WRITE_DATA;
        }
      }
      break;
    }

    /*
     * Read Cycle
     */
    case READ_DATA:
    {
      Detect_START();
      Detect_STOP();

      /* look for SCL HIGH to LOW transition */
      if (eeprom_i2c.old_scl && !eeprom_i2c.scl)
      {
        if (eeprom_i2c.cycles < 9) eeprom_i2c.cycles ++;
        else
        {
          eeprom_i2c.cycles = 1;

          /* ACK not received */
          if (eeprom_i2c.old_sda) eeprom_i2c.state = WAIT_STOP;
         }
      }
      break;
    }

    /*
     * Write Cycle
     */
    case WRITE_DATA:
    {
      Detect_START();
      Detect_STOP();

      /* look for SCL HIGH to LOW transition */
      if (eeprom_i2c.old_scl && !eeprom_i2c.scl)
      {
        if (eeprom_i2c.cycles < 9)
        {
          /* Write DATA bits (max 64kBytes) */
          uint16 sram_address = (eeprom_i2c.slave_mask | eeprom_i2c.word_address) & 0xFFFF;
          if (eeprom_i2c.old_sda) sram.sram[sram_address] |= (1 << (8 - eeprom_i2c.cycles));
          else sram.sram[sram_address] &= ~(1 << (8 - eeprom_i2c.cycles));

          if (eeprom_i2c.cycles == 8) 
          {
            /* WORD ADDRESS is incremented (roll up at maximum pagesize) */
            eeprom_i2c.word_address = (eeprom_i2c.word_address & (0xFFFF - eeprom_i2c.config.pagewrite_mask)) | 
                                     ((eeprom_i2c.word_address + 1) & eeprom_i2c.config.pagewrite_mask);
          }

          eeprom_i2c.cycles ++;
        }
        else eeprom_i2c.cycles = 1;  /* ACK cycle */
      }
      break;
    }
  }

  eeprom_i2c.old_scl = eeprom_i2c.scl;
  eeprom_i2c.old_sda = eeprom_i2c.sda;
}