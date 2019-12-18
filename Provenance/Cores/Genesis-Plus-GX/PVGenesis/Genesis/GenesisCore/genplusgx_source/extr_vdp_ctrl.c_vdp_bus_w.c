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
typedef  unsigned int uint16 ;
struct TYPE_4__ {int /*<<< orphan*/  h; } ;
struct TYPE_6__ {TYPE_1__ viewport; } ;
struct TYPE_5__ {int cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_REG_PC ; 
 int /*<<< orphan*/  MARK_BG_DIRTY (int) ; 
 int MCYCLES_PER_LINE ; 
 int addr ; 
 TYPE_3__ bitmap ; 
 int bordrr ; 
 int code ; 
 int /*<<< orphan*/  color_update_m5 (int,unsigned int) ; 
 int /*<<< orphan*/ * cram ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,unsigned int,...) ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  m68k_get_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcycles_vdp ; 
 int* reg ; 
 int /*<<< orphan*/  remap_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sat ; 
 int sat_addr_mask ; 
 int sat_base_mask ; 
 int satb ; 
 int /*<<< orphan*/  v_counter ; 
 int /*<<< orphan*/ * vram ; 
 int /*<<< orphan*/ * vsram ; 

__attribute__((used)) static void vdp_bus_w(unsigned int data)
{
  /* Check destination code */
  switch (code & 0x0F)
  {
    case 0x01:  /* VRAM */
    {
      /* VRAM address */
      int index = addr & 0xFFFE;

      /* Pointer to VRAM */
      uint16 *p = (uint16 *)&vram[index];

      /* Byte-swap data if A0 is set */
      if (addr & 1)
      {
        data = ((data >> 8) | (data << 8)) & 0xFFFF;
      }

      /* Intercept writes to Sprite Attribute Table */
      if ((index & sat_base_mask) == satb)
      {
        /* Update internal SAT */
        *(uint16 *) &sat[index & sat_addr_mask] = data;
      }

      /* Only write unique data to VRAM */
      if (data != *p)
      {
        int name;

        /* Write data to VRAM */
        *p = data;

        /* Update pattern cache */
        MARK_BG_DIRTY (index);
      }

#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] VRAM 0x%x write -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    case 0x03:  /* CRAM */
    {
      /* Pointer to CRAM 9-bit word */
      uint16 *p = (uint16 *)&cram[addr & 0x7E];

      /* Pack 16-bit bus data (BBB0GGG0RRR0) to 9-bit CRAM data (BBBGGGRRR) */
      data = ((data & 0xE00) >> 3) | ((data & 0x0E0) >> 2) | ((data & 0x00E) >> 1);

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

        /* CRAM modified during HBLANK (Striker, Zero the Kamikaze, etc) */
        if ((v_counter < bitmap.viewport.h) && (reg[1]& 0x40) && (m68k.cycles <= (mcycles_vdp + 860)))
        {
          /* Remap current line */
          remap_line(v_counter);
        }
      }
#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] CRAM 0x%x write -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    case 0x05:  /* VSRAM */
    {
      *(uint16 *)&vsram[addr & 0x7E] = data;

      /* 2-cell Vscroll mode */
      if (reg[11] & 0x04)
      {
        /* VSRAM writes during HBLANK (Adventures of Batman & Robin) */
        if ((v_counter < bitmap.viewport.h) && (reg[1]& 0x40) && (m68k.cycles <= (mcycles_vdp + 860)))
        {
          /* Remap current line */
          render_line(v_counter);
        }
      }
#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] VSRAM 0x%x write -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    default:
    {
#ifdef LOGERROR
      error("[%d(%d)][%d(%d)] Invalid (%d) 0x%x write -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, code, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }
  }

  /* Increment address register */
  addr += reg[15];
}