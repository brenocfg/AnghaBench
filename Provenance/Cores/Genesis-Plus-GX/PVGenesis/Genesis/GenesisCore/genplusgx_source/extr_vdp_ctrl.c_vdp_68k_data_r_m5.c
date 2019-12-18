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
struct TYPE_2__ {int cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_REG_PC ; 
 int MCYCLES_PER_LINE ; 
 int addr ; 
 int code ; 
 int /*<<< orphan*/ * cram ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ m68k ; 
 int /*<<< orphan*/  m68k_get_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ pending ; 
 scalar_t__* reg ; 
 int /*<<< orphan*/  v_counter ; 
 int /*<<< orphan*/ * vram ; 
 int /*<<< orphan*/ * vsram ; 

__attribute__((used)) static unsigned int vdp_68k_data_r_m5(void)
{
  uint16 data = 0;

  /* Clear pending flag */
  pending = 0;

  switch (code & 0x0F)
  {
    case 0x00: /* VRAM */
    {
      /* Read data */
      data = *(uint16 *)&vram[addr & 0xFFFE];

#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] VRAM 0x%x read -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    case 0x04: /* VSRAM */
    {
      /* Read data */
      data = *(uint16 *)&vsram[addr & 0x7E];

#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] VSRAM 0x%x read -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    case 0x08: /* CRAM */
    {
      /* Read data */
      data = *(uint16 *)&cram[addr & 0x7E];

      /* Unpack 9-bit CRAM data (BBBGGGRRR) to 16-bit bus data (BBB0GGG0RRR0) */
      data = ((data & 0x1C0) << 3) | ((data & 0x038) << 2) | ((data & 0x007) << 1);

#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] CRAM 0x%x read -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    case 0x0c: /* undocumented 8-bit VRAM read (cf. http://gendev.spritesmind.net/forum/viewtopic.php?t=790) */
    {
      /* Read data (MSB forced to zero) */
      data = *(uint16 *)&vram[addr & 0xFFFE] & 0xff;

#ifdef LOGVDP
      error("[%d(%d)][%d(%d)] 8-bit VRAM 0x%x read -> 0x%x (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, addr, data, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }

    default:
    {
      /* Invalid code value */
#ifdef LOGERROR
      error("[%d(%d)][%d(%d)] Invalid (%d) 0x%x read (%x)\n", v_counter, m68k.cycles/MCYCLES_PER_LINE-1, m68k.cycles, m68k.cycles%MCYCLES_PER_LINE, code, addr, m68k_get_reg(M68K_REG_PC));
#endif
      break;
    }
  }

  /* Increment address register */
  addr += reg[15];

  /* Return data */
  return data;
}