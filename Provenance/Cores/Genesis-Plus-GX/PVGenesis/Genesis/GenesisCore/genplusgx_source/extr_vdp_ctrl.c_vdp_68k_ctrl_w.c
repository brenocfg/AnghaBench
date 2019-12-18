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
struct TYPE_6__ {int /*<<< orphan*/  cycles; } ;
struct TYPE_4__ {int boot; } ;
struct TYPE_5__ {TYPE_1__ cartridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTEM_MCD ; 
 int addr ; 
 unsigned int addr_latch ; 
 unsigned int cached_write ; 
 int code ; 
 int dma_length ; 
 int dma_src ; 
 int dma_type ; 
 int dmafill ; 
 int fifo_latency ; 
 TYPE_3__ m68k ; 
 int pending ; 
 int* reg ; 
 TYPE_2__ scd ; 
 int /*<<< orphan*/  svp ; 
 int /*<<< orphan*/  system_hw ; 
 int /*<<< orphan*/  vdp_dma_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_reg_w (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

void vdp_68k_ctrl_w(unsigned int data)
{
  /* Check pending flag */
  if (pending == 0)
  {
    /* A single long word write instruction could have started DMA with the first word */
    if (dma_length)
    {
      /* 68k is frozen during 68k bus DMA */
      /* Second word should be written after DMA completion */
      /* See Formula One & Kawasaki Superbike Challenge */
      if (dma_type < 2)
      {
        /* Latch second control word for later */
        cached_write = data;
        return;
      }
    }

    /* Check CD0-CD1 bits */
    if ((data & 0xC000) == 0x8000)
    {
      /* VDP register write */
      vdp_reg_w((data >> 8) & 0x1F, data & 0xFF, m68k.cycles);
    }
    else
    {
      /* Set pending flag (Mode 5 only) */
      pending = reg[1] & 4;
    }

    /* Update address and code registers */
    addr = addr_latch | (data & 0x3FFF);
    code = ((code & 0x3C) | ((data >> 14) & 0x03));
  }
  else
  {
    /* Clear pending flag */
    pending = 0;

    /* Save address bits A15 and A14 */
    addr_latch = (data & 3) << 14;

    /* Update address and code registers */
    addr = addr_latch | (addr & 0x3FFF);
    code = ((code & 0x03) | ((data >> 2) & 0x3C));

    /* Detect DMA operation (CD5 bit set) */
    if (code & 0x20)
    {
      /* DMA must be enabled */
      if (reg[1] & 0x10)
      {
        /* DMA type */
        switch (reg[23] >> 6)
        {
          case 2:
          {
            /* DMA Fill will be triggered by next DATA port write */
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
            vdp_dma_update(m68k.cycles);
            break;
          }

          default:
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

            /* Transfer from SVP ROM/RAM ($000000-$3fffff) or CD Word-RAM ($200000-$3fffff/$600000-$7fffff) */
            if (((system_hw == SYSTEM_MCD) && ((reg[23] & 0x70) == ((scd.cartridge.boot >> 1) + 0x10))) || (svp && !(reg[23] & 0x60)))
            {
              /* source data is available with one cycle delay, i.e first word written by VDP is */
              /* previous data being held on 68k bus at that time, then source words are written */
              /* normally to VDP RAM, with only last source word being ignored */
              addr += reg[15];
              dma_length--;
            }

            /* trigger DMA from 68k bus */
            dma_type = (code & 0x06) ? 0 : 1;
            vdp_dma_update(m68k.cycles);
            break;
          }
        }
      }
    }
  }

  /* 
     FIFO emulation (Chaos Engine/Soldier of Fortune, Double Clutch, Sol Deace) 
     --------------------------------------------------------------------------

      CPU access per line is limited during active display:
         H32: 16 access --> 3420/16 = ~214 Mcycles between access
         H40: 18 access --> 3420/18 = ~190 Mcycles between access

      This is an approximation: on real hardware, access slots are fixed.

      Each VRAM access is byte wide, so one VRAM write (word) need twice cycles.

      Note: Invalid code 0x02 (register write) apparently behaves the same as VRAM
      access, although no data is written in this case (fixes Clue menu)
  */
  fifo_latency = (reg[12] & 1) ? 190 : 214;
  fifo_latency <<= ((code & 0x0F) < 0x03);
}