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
 int dma_length ; 
 int dma_type ; 
 int dmafill ; 
 int /*<<< orphan*/  fifo_lastwrite ; 
 scalar_t__ fifo_latency ; 
 int fifo_write_cnt ; 
 TYPE_1__ m68k ; 
 scalar_t__ pending ; 
 int* reg ; 
 int status ; 
 int /*<<< orphan*/  vdp_bus_w (unsigned int) ; 
 int /*<<< orphan*/  vdp_dma_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_fifo_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdp_68k_data_w_m5(unsigned int data)
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
  
  /* Write data */
  vdp_bus_w(data);

  /* DMA Fill */
  if (dmafill & 0x100)
  {
    /* Fill data = MSB (DMA fill flag is cleared) */
    dmafill = data >> 8;

    /* DMA length */
    dma_length = (reg[20] << 8) | reg[19];

    /* Zero DMA length */
    if (!dma_length)
    {
      dma_length = 0x10000;
    }

    /* Process DMA Fill*/
    dma_type = 2;
    vdp_dma_update(m68k.cycles);
  }
}