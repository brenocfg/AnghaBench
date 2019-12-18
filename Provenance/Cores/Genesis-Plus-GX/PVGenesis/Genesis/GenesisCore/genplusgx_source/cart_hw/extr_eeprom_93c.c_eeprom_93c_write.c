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
typedef  void* uint16 ;
struct TYPE_4__ {unsigned char clk; int state; unsigned char opcode; int cycles; unsigned char buffer; int data; int we; int cs; } ;
struct TYPE_3__ {int /*<<< orphan*/  sram; } ;

/* Variables and functions */
 int BIT_CLK ; 
 int BIT_CS ; 
 int BIT_DATA ; 
#define  GET_OPCODE 131 
#define  READ_WORD 130 
 void* WAIT_STANDBY ; 
#define  WAIT_START 129 
#define  WRITE_WORD 128 
 TYPE_2__ eeprom_93c ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ sram ; 

void eeprom_93c_write(unsigned char data)
{
  /* Make sure CS is HIGH */
  if (data & (1 << BIT_CS))
  {
    /* Data latched on CLK postive edge */
    if ((data & (1 << BIT_CLK)) && !eeprom_93c.clk)
    {
      /* Current EEPROM state */
      switch (eeprom_93c.state)
      {
        case WAIT_START:
        {
          /* Wait for START bit */
          if (data & (1 << BIT_DATA))
          {
            eeprom_93c.opcode = 0;
            eeprom_93c.cycles = 0;
            eeprom_93c.state = GET_OPCODE;
          }
          break;
        }

        case GET_OPCODE:
        {
          /* 8-bit buffer (opcode + address) */
          eeprom_93c.opcode |= ((data >> BIT_DATA) & 1) << (7 - eeprom_93c.cycles);
          eeprom_93c.cycles++;

          if (eeprom_93c.cycles == 8)
          {
            /* Decode instruction */
            switch ((eeprom_93c.opcode >> 6) & 3)
            {
              case 1:
              {
                /* WRITE */
                eeprom_93c.buffer = 0;
                eeprom_93c.cycles = 0;
                eeprom_93c.state = WRITE_WORD;
                break;
              }

              case 2:
              {
                /* READ */
                eeprom_93c.buffer = *(uint16 *)(sram.sram + ((eeprom_93c.opcode & 0x3F) << 1));
                eeprom_93c.cycles = 0;
                eeprom_93c.state = READ_WORD;

                /* Force DATA OUT */
                eeprom_93c.data = 0;
                break;
              }

              case 3:
              {
                /* ERASE */
                if (eeprom_93c.we)
                {
                  *(uint16 *)(sram.sram + ((eeprom_93c.opcode & 0x3F) << 1)) = 0xFFFF;
                }

                /* wait for next command */
                eeprom_93c.state = WAIT_STANDBY;
                break;
              }

              default:
              {
                /* special command */
                switch ((eeprom_93c.opcode >> 4) & 3)
                {
                  case 1:
                  {
                    /* WRITE ALL */
                    eeprom_93c.buffer = 0;
                    eeprom_93c.cycles = 0;
                    eeprom_93c.state = WRITE_WORD;
                    break;
                  }

                  case 2:
                  {
                    /* ERASE ALL */
                    if (eeprom_93c.we)
                    {
                      memset(sram.sram, 0xFF, 128);
                    }

                    /* wait for next command */
                    eeprom_93c.state = WAIT_STANDBY;
                    break;
                  }

                  default:
                  {
                    /* WRITE ENABLE/DISABLE */
                    eeprom_93c.we = (eeprom_93c.opcode >> 4) & 1;

                    /* wait for next command */
                    eeprom_93c.state = WAIT_STANDBY;
                    break;
                  }
                }
                break;
              }
            }
          }
          break;
        }

        case WRITE_WORD:
        {
          /* 16-bit data buffer */
          eeprom_93c.buffer |= ((data >> BIT_DATA) & 1) << (15 - eeprom_93c.cycles);
          eeprom_93c.cycles++;

          if (eeprom_93c.cycles == 16)
          {
            /* check EEPROM write protection */
            if (eeprom_93c.we)
            {
              if (eeprom_93c.opcode & 0x40)
              {
                /* write one word */
                *(uint16 *)(sram.sram + ((eeprom_93c.opcode & 0x3F) << 1)) = eeprom_93c.buffer;
              }
              else
              {
                /* write 64 words */
                int i;
                for (i=0; i<64; i++)
                {
                  *(uint16 *)(sram.sram + (i << 1)) = eeprom_93c.buffer;

                }
              }
            }

            /* wait for next command */
            eeprom_93c.state = WAIT_STANDBY;
          }
          break;
        }

        case READ_WORD:
        {
          /* set DATA OUT */
          eeprom_93c.data = ((eeprom_93c.buffer >> (15 - eeprom_93c.cycles)) & 1);
          eeprom_93c.cycles++;

          if (eeprom_93c.cycles == 16)
          {
            /* read next word (93C46B) */
            eeprom_93c.opcode++;
            eeprom_93c.cycles = 0;
            eeprom_93c.buffer = *(uint16 *)(sram.sram + ((eeprom_93c.opcode & 0x3F) << 1));
          }
          break;
        }

        default:
        {
          /* wait for STANDBY mode */
          break;
        }
      }
    }
  }
  else
  {
    /* CS HIGH->LOW transition */
    if (eeprom_93c.cs)
    {
      /* standby mode */
      eeprom_93c.data = 1;
      eeprom_93c.state = WAIT_START;
    }
  }

  /* Update input lines */
  eeprom_93c.cs  = (data >> BIT_CS) & 1;
  eeprom_93c.clk = (data >> BIT_CLK) & 1;
}