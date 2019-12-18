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
typedef  int /*<<< orphan*/  uint16 ;

/* Variables and functions */
 int dma_src ; 
 int* reg ; 
 int /*<<< orphan*/  vdp_bus_w (int /*<<< orphan*/ ) ; 
 scalar_t__ work_ram ; 

__attribute__((used)) static void vdp_dma_68k_ram(unsigned int length)
{
  uint16 data;

  /* 68k bus source address */
  uint32 source = (reg[23] << 17) | (dma_src << 1);

  do
  {
    /* access Work-RAM by default  */
    data = *(uint16 *)(work_ram + (source & 0xFFFF));
   
    /* Increment source address */
    source += 2;

    /* 128k DMA window */
    source = (reg[23] << 17) | (source & 0x1FFFF);

    /* Write data word to VRAM, CRAM or VSRAM */
    vdp_bus_w(data);
  }
  while (--length);

  /* Update DMA source address */
  dma_src = (source >> 1) & 0xffff;
}