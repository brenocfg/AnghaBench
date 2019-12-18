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
struct TYPE_2__ {int /*<<< orphan*/  cycles; } ;

/* Variables and functions */
 TYPE_1__ Z80 ; 
 int addr ; 
 int addr_latch ; 
 int code ; 
 int dma_length ; 
 int dma_src ; 
 int dma_type ; 
 int dmafill ; 
 int /*<<< orphan*/ * fifo ; 
 int pending ; 
 int* reg ; 
 int /*<<< orphan*/  vdp_dma_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_reg_w (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vram ; 

void vdp_z80_ctrl_w(unsigned int data)
{
  switch (pending)
  {
    case 0:
    {
      /* Latch LSB */
      addr_latch = data;

      /* Set LSB pending flag */
      pending = 1;
      return;
    }

    case 1:
    {
      /* Update address and code registers */
      addr = (addr & 0xC000) | ((data & 0x3F) << 8) | addr_latch ;
      code = ((code & 0x3C) | ((data >> 6) & 0x03));

      if ((code & 0x03) == 0x02)
      {
        /* VDP register write */
        vdp_reg_w(data & 0x1F, addr_latch, Z80.cycles);

        /* Clear pending flag  */
        pending = 0;
        return;
      }

      /* Set Mode 5 pending flag  */
      pending = (reg[1] & 4) >> 1;

      if (!pending && !(code & 0x03))
      {
        /* Process VRAM read */
        fifo[0] = vram[addr & 0x3FFF];

        /* Increment address register */
        addr += (reg[15] + 1);
      }
      return;
    }

    case 2:
    {
      /* Latch LSB */
      addr_latch = data;

      /* Set LSB pending flag */
      pending = 3;
      return;
    }

    case 3:
    {
      /* Clear pending flag  */
      pending = 0;

      /* Update address and code registers */
      addr = ((addr_latch & 3) << 14) | (addr & 0x3FFF);
      code = ((code & 0x03) | ((addr_latch >> 2) & 0x3C));

      /* Detect DMA operation (CD5 bit set) */
      if (code & 0x20)
      {
        /* DMA should be enabled */
        if (reg[1] & 0x10)
        {
          /* DMA type */
          switch (reg[23] >> 6)
          {
            case 2:
            {
              /* DMA Fill will be triggered by next write to DATA port */
              dmafill = 0x100;
              break;
            }

            case 3:
            {
              /* DMA length */
              dma_length = (reg[20] << 8) | reg[19];

              /* Zero DMA length */
              if (!dma_length)
              {
                dma_length = 0x10000;
              }

              /* DMA source address */
              dma_src = (reg[22] << 8) | reg[21];

              /* trigger DMA copy */
              dma_type = 3;
              vdp_dma_update(Z80.cycles);
              break;
            }

            default:
            {
              /* DMA from 68k bus does not work when Z80 is in control */
              break;
            }
          }
        }
      }
    }
    return;
  }
}