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
 TYPE_1__ Z80 ; 
 int addr ; 
 unsigned int addr_latch ; 
 int code ; 
 int /*<<< orphan*/ * fifo ; 
 int pending ; 
 int* reg ; 
 int /*<<< orphan*/  render_bg ; 
 int /*<<< orphan*/  render_bg_inv ; 
 int /*<<< orphan*/  render_bg_m0 ; 
 int /*<<< orphan*/  render_bg_m1 ; 
 int /*<<< orphan*/  render_bg_m1x ; 
 int /*<<< orphan*/  render_bg_m2 ; 
 int /*<<< orphan*/  render_bg_m3 ; 
 int /*<<< orphan*/  render_bg_m3x ; 
 int /*<<< orphan*/  vdp_reg_w (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vram ; 

void vdp_tms_ctrl_w(unsigned int data)
{
  if(pending == 0)
  {
    /* Latch LSB */
    addr_latch = data;

    /* Set LSB pending flag */
    pending = 1;
  }
  else
  {
    /* Update address and code registers */
    code = (data >> 6) & 3;
    addr = (data << 8 | addr_latch) & 0x3FFF;

    /* Clear pending flag  */
    pending = 0;

    if (code == 0)
    {
      /* Process VRAM read */
      fifo[0] = vram[addr & 0x3FFF];

      /* Increment address register */
      addr = (addr + 1) & 0x3FFF;
      return;
    }

    if (code & 2)
    {
      /* VDP register index (0-7) */
      data &= 0x07;

      /* Write VDP register */
      vdp_reg_w(data, addr_latch, Z80.cycles);
 
      /* Check VDP mode changes */
      if (data < 2)
      {
        int mode = (reg[0] & 0x02) | (reg[1] & 0x18);

        /* Rendering mode */
        switch (mode)
        {
          case 0x00: /* Graphics I */
          {
            render_bg = render_bg_m0;
            break;
          }

          case 0x10: /* Text */
          {
            render_bg = render_bg_m1;
            break;
          }

          case 0x02: /* Graphics II */
          {
            render_bg = render_bg_m2;
            break;
          }

          case 0x12: /* Text (Extended PG) */
          {
            render_bg = render_bg_m1x;
            break;
          }

          case 0x08: /* Multicolor */
          {
            render_bg = render_bg_m3;
            break;
          }

          case 0x18: /* Invalid (1+3) */
          {
            render_bg = render_bg_inv;
            break;
          }

          case 0x0A: /* Multicolor (Extended PG) */
          {
            render_bg = render_bg_m3x;
            break;
          }

          case 0x1A: /* Invalid (1+2+3) */
          {
            render_bg = render_bg_inv;
            break;
          }
        }
      }
    }
  }
}