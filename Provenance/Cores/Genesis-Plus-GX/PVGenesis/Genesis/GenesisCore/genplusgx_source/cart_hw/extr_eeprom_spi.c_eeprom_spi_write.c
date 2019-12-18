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
struct TYPE_4__ {int cycles; int out; unsigned char opcode; int state; unsigned char clk; unsigned char buffer; unsigned char addr; int status; unsigned char cs; } ;
struct TYPE_3__ {unsigned char* sram; } ;

/* Variables and functions */
 int BIT_CLK ; 
 int BIT_CS ; 
 unsigned char BIT_DATA ; 
 int BIT_HOLD ; 
#define  GET_ADDRESS 131 
#define  GET_OPCODE 130 
 int PAGE_MASK ; 
#define  READ_BYTE 129 
 int SIZE_MASK ; 
 void* STANDBY ; 
#define  WRITE_BYTE 128 
 TYPE_2__ spi_eeprom ; 
 TYPE_1__ sram ; 

void eeprom_spi_write(unsigned char data)
{
  /* Make sure !HOLD is high */
  if (data & (1 << BIT_HOLD))
  {
    /* Check !CS state */
    if (data & (1 << BIT_CS))
    {
      /* !CS high -> end of current operation */
      spi_eeprom.cycles = 0;
      spi_eeprom.out = 1;
      spi_eeprom.opcode = 0;
      spi_eeprom.state = GET_OPCODE;
    }
    else
    {
      /* !CS low -> process current operation */
      switch (spi_eeprom.state)
      {
        case GET_OPCODE:
        {
          /* latch data on CLK positive edge */
          if ((data & (1 << BIT_CLK)) && !spi_eeprom.clk)
          {
            /* 8-bit opcode buffer */
            spi_eeprom.opcode |= ((data >> BIT_DATA) & 1);
            spi_eeprom.cycles++;

            /* last bit ? */
            if (spi_eeprom.cycles == 8)
            {
              /* reset cycles count */
              spi_eeprom.cycles = 0;

              /* Decode instruction */
              switch (spi_eeprom.opcode)
              {
                case 0x01:
                {
                  /* WRITE STATUS */
                  spi_eeprom.buffer = 0;
                  spi_eeprom.state = WRITE_BYTE;
                  break;
                }

                case 0x02:
                {
                  /* WRITE BYTE */
                  spi_eeprom.addr = 0;
                  spi_eeprom.state = GET_ADDRESS;
                  break;
                }

                case 0x03:
                {
                  /* READ BYTE */
                  spi_eeprom.addr = 0;
                  spi_eeprom.state = GET_ADDRESS;
                  break;
                }

                case 0x04:
                {
                  /* WRITE DISABLE */
                  spi_eeprom.status &= ~0x02;
                  spi_eeprom.state = STANDBY;
                  break;
                }

                case 0x05:
                {
                  /* READ STATUS */
                  spi_eeprom.buffer = spi_eeprom.status;
                  spi_eeprom.state = READ_BYTE;
                  break;
                }

                case 0x06:
                {
                  /* WRITE ENABLE */
                  spi_eeprom.status |= 0x02;
                  spi_eeprom.state = STANDBY;
                  break;
                }

                default:
                {
                  /* specific instructions (not supported) */
                  spi_eeprom.state = STANDBY;
                  break;
                }
              }
            }
            else
            {
              /* shift opcode value */
              spi_eeprom.opcode = spi_eeprom.opcode << 1;
            }
          }
          break;
        }

        case GET_ADDRESS:
        {
          /* latch data on CLK positive edge */
          if ((data & (1 << BIT_CLK)) && !spi_eeprom.clk)
          {
            /* 16-bit address */
            spi_eeprom.addr |= ((data >> BIT_DATA) & 1);
            spi_eeprom.cycles++;

            /* last bit ? */
            if (spi_eeprom.cycles == 16)
            {
              /* reset cycles count */
              spi_eeprom.cycles = 0;

              /* mask unused address bits */
              spi_eeprom.addr &= SIZE_MASK;

              /* operation type */
              if (spi_eeprom.opcode & 0x01)
              {
                /* READ operation */
                spi_eeprom.buffer = sram.sram[spi_eeprom.addr];
                spi_eeprom.state = READ_BYTE;
              }
              else
              {
                /* WRITE operation */
                spi_eeprom.buffer = 0;
                spi_eeprom.state = WRITE_BYTE;
              }
            }
            else
            {
              /* shift address value */
              spi_eeprom.addr = spi_eeprom.addr << 1;
            }
          }
          break;
        }

        case WRITE_BYTE:
        {
          /* latch data on CLK positive edge */
          if ((data & (1 << BIT_CLK)) && !spi_eeprom.clk)
          {
            /* 8-bit data buffer */
            spi_eeprom.buffer |= ((data >> BIT_DATA) & 1);
            spi_eeprom.cycles++;

            /* last bit ? */
            if (spi_eeprom.cycles == 8)
            {
              /* reset cycles count */
              spi_eeprom.cycles = 0;

              /* write data to destination */
              if (spi_eeprom.opcode & 0x01)
              {
                /* update status register */
                spi_eeprom.status = (spi_eeprom.status & 0x02) | (spi_eeprom.buffer & 0x0c);

                /* wait for operation end */
                spi_eeprom.state = STANDBY;
              }
              else
              {
                /* Memory Array (write-protected) */
                if (spi_eeprom.status & 2)
                {
                  /* check array protection bits (BP0, BP1) */
                  switch ((spi_eeprom.status >> 2) & 0x03)
                  {
                    case 0x01:
                    {
                      /* $C000-$FFFF (sector #3) is protected */
                      if (spi_eeprom.addr < 0xC000)
                      {
                        sram.sram[spi_eeprom.addr] = spi_eeprom.buffer;
                      }
                      break;
                    }

                    case 0x02:
                    {
                      /* $8000-$FFFF (sectors #2 and #3) is protected */
                      if (spi_eeprom.addr < 0x8000)
                      {
                        sram.sram[spi_eeprom.addr] = spi_eeprom.buffer;
                      }
                      break;
                    }

                    case 0x03:
                    {
                      /* $0000-$FFFF (all sectors) is protected */
                      break;
                    }

                    default:
                    {
                      /* no sectors protected */
                      sram.sram[spi_eeprom.addr] = spi_eeprom.buffer;
                      break;
                    }
                  }
                }

                /* reset data buffer */
                spi_eeprom.buffer = 0;

                /* increase array address (sequential writes are limited within the same page) */
                spi_eeprom.addr = (spi_eeprom.addr & ~PAGE_MASK) | ((spi_eeprom.addr + 1) & PAGE_MASK);
              }
            }
            else
            {
              /* shift data buffer value */
              spi_eeprom.buffer = spi_eeprom.buffer << 1;
            }
          }
          break;
        }

        case READ_BYTE:
        {
          /* output data on CLK positive edge */
          if ((data & (1 << BIT_CLK)) && !spi_eeprom.clk)
          {
            /* read out bits */
            spi_eeprom.out = (spi_eeprom.buffer >> (7 - spi_eeprom.cycles)) & 1;
            spi_eeprom.cycles++;

            /* last bit ? */
            if (spi_eeprom.cycles == 8)
            {
              /* reset cycles count */
              spi_eeprom.cycles = 0;

              /* read from memory array ? */
              if (spi_eeprom.opcode == 0x03)
              {
                /* read next array byte */
                spi_eeprom.addr = (spi_eeprom.addr + 1) & SIZE_MASK;
                spi_eeprom.buffer = sram.sram[spi_eeprom.addr];
              }
            }
          }
          break;
        }

        default:
        {
          /* wait for !CS low->high transition */
          break;
        }
      }
    }
  }

  /* update input lines */
  spi_eeprom.cs  = (data >> BIT_CS) & 1;
  spi_eeprom.clk = (data >> BIT_CLK) & 1;
}