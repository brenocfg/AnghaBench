#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;
typedef  int uint16 ;

/* Variables and functions */
 int dma_src ; 
 int io_68k_read (int) ; 
 int* reg ; 
 int /*<<< orphan*/  vdp_bus_w (int) ; 
 scalar_t__ work_ram ; 
 int zstate ; 

__attribute__((used)) static void vdp_dma_68k_io(unsigned int length)
{
  uint16 data;

  /* 68k bus source address */
  uint32 source = (reg[23] << 17) | (dma_src << 1);

  do
  {
    /* Z80 area */
    if (source <= 0xA0FFFF)
    {
      /* Return $FFFF only when the Z80 isn't hogging the Z-bus.
      (e.g. Z80 isn't reset and 68000 has the bus) */
      data = ((zstate ^ 3) ? *(uint16 *)(work_ram + (source & 0xFFFF)) : 0xFFFF);
    }

    /* The I/O chip and work RAM try to drive the data bus which results 
       in both values being combined in random ways when read.
       We return the I/O chip values which seem to have precedence, */
    else if (source <= 0xA1001F)
    {
      data = io_68k_read((source >> 1) & 0x0F);
      data = (data << 8 | data);
    }

    /* All remaining locations access work RAM */
    else
    {
      data = *(uint16 *)(work_ram + (source & 0xFFFF));
    }

    /* Increment source address */
    source += 2;

    /* 128k DMA window */
    source = (reg[23] << 17) | (source & 0x1FFFF);

    /* Write data to VRAM, CRAM or VSRAM */
    vdp_bus_w(data);
  }
  while (--length);

  /* Update DMA source address */
  dma_src = (source >> 1) & 0xffff;
}