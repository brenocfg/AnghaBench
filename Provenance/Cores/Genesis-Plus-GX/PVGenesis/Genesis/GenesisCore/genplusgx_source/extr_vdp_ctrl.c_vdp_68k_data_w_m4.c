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
typedef  unsigned int uint16 ;
struct TYPE_2__ {int /*<<< orphan*/  cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  MARK_BG_DIRTY (int) ; 
 int addr ; 
 int bordrr ; 
 int code ; 
 int /*<<< orphan*/  color_update_m4 (int,unsigned int) ; 
 int /*<<< orphan*/ * cram ; 
 int /*<<< orphan*/  fifo_lastwrite ; 
 scalar_t__ fifo_latency ; 
 int fifo_write_cnt ; 
 TYPE_1__ m68k ; 
 scalar_t__ pending ; 
 int* reg ; 
 int status ; 
 int /*<<< orphan*/  vdp_fifo_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vram ; 

__attribute__((used)) static void vdp_68k_data_w_m4(unsigned int data)
{
  /* Clear pending flag */
  pending = 0;

  /* Restricted VDP writes during active display */
  if (!(status & 8) && (reg[1] & 0x40))
  {
    /* Update VDP FIFO */
    vdp_fifo_update(m68k.cycles);

    /* Clear FIFO empty flag */
    status &= 0xFDFF;

    /* up to 4 words can be stored */
    if (fifo_write_cnt < 4)
    {
      /* Increment FIFO counter */
      fifo_write_cnt++;

      /* Set FIFO full flag if 4 words are stored */
      status |= ((fifo_write_cnt & 4) << 6);
    }
    else
    {
      /* CPU is halted until last FIFO entry has been processed (Chaos Engine, Soldiers of Fortune, Double Clutch) */
      fifo_lastwrite += fifo_latency;
      m68k.cycles = fifo_lastwrite;
    }
  }

  /* Check destination code */
  if (code & 0x02)
  {
    /* CRAM index (32 words) */
    int index = addr & 0x1F;

    /* Pointer to CRAM 9-bit word */
    uint16 *p = (uint16 *)&cram[index << 1];

    /* Pack 16-bit data (xxx000BBGGRR) to 9-bit CRAM data (xxxBBGGRR) */
    data = ((data & 0xE00) >> 3) | (data & 0x3F);

    /* Check if CRAM data is being modified */
    if (data != *p)
    {
      /* Write CRAM data */
      *p = data;

      /* Update color palette */
      color_update_m4(index, data);

      /* Update backdrop color */
      if (index == (0x10 | (bordrr & 0x0F)))
      {
        color_update_m4(0x40, data);
      }
    }
  }
  else
  {
    /* VRAM address (interleaved format) */
    int index = ((addr << 1) & 0x3FC) | ((addr & 0x200) >> 8) | (addr & 0x3C00);

    /* Pointer to VRAM */
    uint16 *p = (uint16 *)&vram[index];

    /* Byte-swap data if A0 is set */
    if (addr & 1)
    {
      data = ((data >> 8) | (data << 8)) & 0xFFFF;
    }

    /* Only write unique data to VRAM */
    if (data != *p)
    {
      int name;

      /* Write data to VRAM */
      *p = data;

      /* Update the pattern cache */
      MARK_BG_DIRTY (index);
    }
  }

  /* Increment address register (TODO: check how address is incremented in Mode 4) */
  addr += (reg[15] + 1);
}