#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_8__ {int /*<<< orphan*/  cycles; } ;
struct TYPE_5__ {int h; int changed; int y; } ;
struct TYPE_7__ {TYPE_1__ viewport; } ;
struct TYPE_6__ {int overscan; int /*<<< orphan*/  gg_extra; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_GG ; 
 scalar_t__ SYSTEM_SMS ; 
 TYPE_4__ Z80 ; 
 int addr ; 
 unsigned int addr_latch ; 
 int bg_list_index ; 
 TYPE_3__ bitmap ; 
 int bordrr ; 
 int code ; 
 int /*<<< orphan*/  color_update_m4 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/ * cram ; 
 int /*<<< orphan*/ * fifo ; 
 int /*<<< orphan*/  parse_satb ; 
 int /*<<< orphan*/  parse_satb_m4 ; 
 int /*<<< orphan*/  parse_satb_tms ; 
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
 int /*<<< orphan*/  render_bg_m4 ; 
 int /*<<< orphan*/  render_obj ; 
 int /*<<< orphan*/  render_obj_m4 ; 
 int /*<<< orphan*/  render_obj_tms ; 
 int status ; 
 scalar_t__ system_hw ; 
 int /*<<< orphan*/  vc_max ; 
 int /*<<< orphan*/ ** vc_table ; 
 size_t vdp_pal ; 
 int /*<<< orphan*/  vdp_reg_w (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vram ; 

void vdp_sms_ctrl_w(unsigned int data)
{
  if(pending == 0)
  {
    /* Update address register LSB */
    addr = (addr & 0x3F00) | (data & 0xFF);

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

    if (code == 2)
    {
      /* Save current VDP mode */
      int mode, prev = (reg[0] & 0x06) | (reg[1] & 0x18);

      /* Write VDP register 0-15 */
      vdp_reg_w(data & 0x0F, addr_latch, Z80.cycles);

      /* Check VDP mode changes */
      mode = (reg[0] & 0x06) | (reg[1] & 0x18);
      prev ^= mode;
 
      if (prev)
      {
        /* Check for extended modes */
        if (system_hw > SYSTEM_SMS)
        {
          int height;

          if (mode == 0x0E) /* M1=0,M2=1,M3=1,M4=1 */
          {
            /* Mode 4 extended (240 lines) */
            height = 240;

            /* Update vertical counter max value */
            vc_max = vc_table[3][vdp_pal];
          }
          else if (mode == 0x16) /* M1=1,M2=1,M3=0,M4=1 */
          {
            /* Mode 4 extended (224 lines) */
            height = 224;

            /* Update vertical counter max value */
            vc_max = vc_table[1][vdp_pal];
          }
          else
          {
            /* Mode 4 default (224 lines) */
            height = 192;

            /* Default vertical counter max value */
            vc_max = vc_table[0][vdp_pal];
          }

          if (height != bitmap.viewport.h)
          {
            if (status & 8)
            {
              /* viewport changes should be applied on next frame */
              bitmap.viewport.changed |= 2;
            }
            else
            {
              /* update active display */
              bitmap.viewport.h = height;

              /* update vertical overscan */
              if (config.overscan & 1)
              {
                bitmap.viewport.y = (240 + 48*vdp_pal - height) >> 1;
              }
              else
              {
                if ((system_hw == SYSTEM_GG) && !config.gg_extra)
                {
                  /* Display area reduced to 160x144 */
                  bitmap.viewport.y = (144 - height) / 2;
                }
                else
                {
                  bitmap.viewport.y = 0;
                }
              }
            }
          }
        }

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

          default: /* Mode 4 */
          {
            render_bg = render_bg_m4;
            break;
          }
        }

        /* Mode switching */
        if (prev & 0x04)
        {
          int i;

          if (mode & 0x04)
          {
            /* Mode 4 sprites */
            parse_satb = parse_satb_m4;
            render_obj = render_obj_m4;

            /* force BG cache update*/
            bg_list_index = 0x200;
          }
          else
          {
            /* TMS-mode sprites */
            parse_satb = parse_satb_tms;
            render_obj = render_obj_tms;

            /* BG cache is not used */
            bg_list_index = 0;
          }

          /* reinitialize palette */
          for(i = 0; i < 0x20; i ++)
          {
            color_update_m4(i, *(uint16 *)&cram[i << 1]);
          }
          color_update_m4(0x40, *(uint16 *)&cram[(0x10 | (bordrr & 0x0F)) << 1]);
        }
      }
    }
  }
}