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
typedef  unsigned int uint16 ;

/* Variables and functions */
 unsigned int READ_BYTE (int /*<<< orphan*/ ,int) ; 
 int addr ; 
 int code ; 
 int /*<<< orphan*/ * cram ; 
 scalar_t__ pending ; 
 scalar_t__* reg ; 
 int /*<<< orphan*/  vram ; 
 int /*<<< orphan*/  vsram ; 

__attribute__((used)) static unsigned int vdp_z80_data_r_m5(void)
{
  unsigned int data = 0;

  /* Clear pending flag */
  pending = 0;

  switch (code & 0x0F)
  {
    case 0x00: /* VRAM */
    {
      /* Return low byte from even address & high byte from odd address */
      data = READ_BYTE(vram, addr ^ 1);
      break;
    }

    case 0x04: /* VSRAM */
    {
      /* Return low byte from even address & high byte from odd address */
      data = READ_BYTE(vsram, (addr & 0x7F) ^ 1);
      break;
    }

    case 0x08: /* CRAM */
    {
      /* Read CRAM data */
      data = *(uint16 *)&cram[addr & 0x7E];

      /* Unpack 9-bit CRAM data (BBBGGGRRR) to 16-bit data (BBB0GGG0RRR0) */
      data = ((data & 0x1C0) << 3) | ((data & 0x038) << 2) | ((data & 0x007) << 1);

      /* Return low byte from even address & high byte from odd address */
      if (addr & 1)
      {
        data = data >> 8;
      }

      data &= 0xFF;
      break;
    }
  }

  /* Increment address register */
  addr += reg[15];

  /* Return data */
  return data;
}