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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint16 ;

/* Variables and functions */
 int /*<<< orphan*/  MARK_BG_DIRTY (unsigned int) ; 
 int /*<<< orphan*/  READ_BYTE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_BYTE (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int addr ; 
 int code ; 
 scalar_t__ dma_src ; 
 unsigned int* reg ; 
 int /*<<< orphan*/  sat ; 
 unsigned int sat_addr_mask ; 
 unsigned int sat_base_mask ; 
 unsigned int satb ; 
 int /*<<< orphan*/  vram ; 

__attribute__((used)) static void vdp_dma_copy(unsigned int length)
{
  /* VRAM read/write operation only */
  if ((code & 0x1E) == 0x10)
  {
    int name;
    uint8 data;
    
    /* VRAM source address */
    uint16 source = dma_src;

    do
    {
      /* Read byte from source address */
      data = READ_BYTE(vram, source);

      /* Intercept writes to Sprite Attribute Table */
      if ((addr & sat_base_mask) == satb)
      {
        /* Update internal SAT */
        WRITE_BYTE(sat, addr & sat_addr_mask, data);
      }

      /* Write byte to VRAM address */
      WRITE_BYTE(vram, addr, data);

      /* Update pattern cache */
      MARK_BG_DIRTY(addr);

      /* Increment source address */
      source++;

      /* Increment VRAM address */
      addr += reg[15];
    }
    while (--length);

    /* Update DMA source address */
    dma_src = source;
  }
  else
  {
    /* DMA source & VRAM addresses are still incremented */
    addr += reg[15] * length;
    dma_src += length;
  }
}