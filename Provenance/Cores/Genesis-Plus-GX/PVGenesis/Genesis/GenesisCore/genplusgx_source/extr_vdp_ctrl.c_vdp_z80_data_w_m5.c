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
typedef  int uint16 ;
struct TYPE_2__ {int /*<<< orphan*/  cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  MARK_BG_DIRTY (int) ; 
 unsigned int READ_BYTE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_BYTE (int /*<<< orphan*/ ,int,unsigned int) ; 
 TYPE_1__ Z80 ; 
 int addr ; 
 int bordrr ; 
 int code ; 
 int /*<<< orphan*/  color_update_m5 (int,unsigned int) ; 
 int /*<<< orphan*/ * cram ; 
 int dma_length ; 
 int dma_type ; 
 int dmafill ; 
 scalar_t__ pending ; 
 int* reg ; 
 int /*<<< orphan*/  sat ; 
 int sat_addr_mask ; 
 int sat_base_mask ; 
 int satb ; 
 int /*<<< orphan*/  vdp_dma_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vram ; 
 int /*<<< orphan*/  vsram ; 

__attribute__((used)) static void vdp_z80_data_w_m5(unsigned int data)
{
  /* Clear pending flag */
  pending = 0;

  /* Check destination code */
  switch (code & 0x0F)
  {
    case 0x01:  /* VRAM */
    {
      /* VRAM address (write low byte to even address & high byte to odd address) */
      int index = addr ^ 1;

      /* Intercept writes to Sprite Attribute Table */
      if ((index & sat_base_mask) == satb)
      {
        /* Update internal SAT */
        WRITE_BYTE(sat, index & sat_addr_mask, data);
      }

      /* Only write unique data to VRAM */
      if (data != READ_BYTE(vram, index))
      {
        int name;

        /* Write data */
        WRITE_BYTE(vram, index, data);

        /* Update pattern cache */
        MARK_BG_DIRTY (index);
      }
      break;
    }

    case 0x03:  /* CRAM */
    {
      /* Pointer to CRAM word */
      uint16 *p = (uint16 *)&cram[addr & 0x7E];

      /* Pack 8-bit value into 9-bit CRAM data */
      if (addr & 1)
      {
        /* Write high byte (0000BBB0 -> BBBxxxxxx) */
        data = (*p & 0x3F) | ((data & 0x0E) << 5);
      }
      else
      {
        /* Write low byte (GGG0RRR0 -> xxxGGGRRR) */
        data = (*p & 0x1C0) | ((data & 0x0E) >> 1)| ((data & 0xE0) >> 2);
      }

      /* Check if CRAM data is being modified */
      if (data != *p)
      {
        /* CRAM index (64 words) */
        int index = (addr >> 1) & 0x3F;

        /* Write CRAM data */
        *p = data;

        /* Color entry 0 of each palette is never displayed (transparent pixel) */
        if (index & 0x0F)
        {
          /* Update color palette */
          color_update_m5(index, data);
        }

        /* Update backdrop color */
        if (index == bordrr)
        {
          color_update_m5(0x00, data);
        }
      }
      break;
    }

    case 0x05: /* VSRAM */
    {
      /* Write low byte to even address & high byte to odd address */
      WRITE_BYTE(vsram, (addr & 0x7F) ^ 1, data);
      break;
    }
  }

  /* Increment address register  */
  addr += reg[15];

  /* DMA Fill */
  if (dmafill & 0x100)
  {
    /* Fill data (DMA fill flag is cleared) */
    dmafill = data;

    /* DMA length */
    dma_length = (reg[20] << 8) | reg[19];

    /* Zero DMA length */
    if (!dma_length)
    {
      dma_length = 0x10000;
    }

    /* Process DMA Fill */
    dma_type = 2;
    vdp_dma_update(Z80.cycles);
  }
}