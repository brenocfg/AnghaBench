#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  unsigned int uint16 ;
struct TYPE_25__ {int /*<<< orphan*/  emu_status; TYPE_7__* gr; } ;
struct TYPE_26__ {TYPE_8__ ssp1601; } ;
struct TYPE_23__ {unsigned int h; } ;
struct TYPE_24__ {TYPE_6__ byte; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* time_w ) (unsigned int,unsigned int) ;} ;
struct TYPE_20__ {int l; int h; } ;
struct TYPE_21__ {int w; TYPE_3__ byte; } ;
struct TYPE_19__ {int /*<<< orphan*/  base; } ;
struct TYPE_18__ {int /*<<< orphan*/  boot; } ;
struct TYPE_17__ {TYPE_5__ hw; } ;
struct TYPE_16__ {int bios; } ;
struct TYPE_15__ {char* cycles; TYPE_2__* memory_map; int /*<<< orphan*/  pc; } ;
struct TYPE_14__ {int pending; int dmna; TYPE_4__* regs; TYPE_1__ cartridge; int /*<<< orphan*/  prg_ram; } ;

/* Variables and functions */
 size_t SSP_PM0 ; 
 int /*<<< orphan*/  SSP_WAIT_PM0 ; 
 size_t SSP_XST ; 
 int /*<<< orphan*/  SYSTEM_MCD ; 
 TYPE_13__ cart ; 
 TYPE_12__ config ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tmss_w (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gen_zbusreq_w (unsigned int,char*) ; 
 int /*<<< orphan*/  gen_zreset_w (unsigned int,char*) ; 
 int /*<<< orphan*/  io_68k_write (unsigned int,unsigned int) ; 
 TYPE_11__ m68k ; 
 int /*<<< orphan*/  m68k_lockup_w_16 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  m68k_poll_sync (unsigned int) ; 
 int /*<<< orphan*/  m68k_unused_16_w (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s68k_clear_halt () ; 
 int /*<<< orphan*/  s68k_pulse_halt () ; 
 int /*<<< orphan*/  s68k_pulse_reset () ; 
 int /*<<< orphan*/  s68k_update_irq (int) ; 
 TYPE_10__ scd ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int) ; 
 TYPE_9__* svp ; 
 int /*<<< orphan*/  system_hw ; 
 int /*<<< orphan*/  v_counter ; 

void ctrl_io_write_word(unsigned int address, unsigned int data)
{
  switch ((address >> 8) & 0xFF)
  {
    case 0x00:  /* I/O chip */
    {
      if (!(address & 0xE0))
      {
        io_68k_write((address >> 1) & 0x0F, data & 0xFF);
        return;
      }
      m68k_unused_16_w(address, data);
      return;
    }

    case 0x11:  /* Z80 BUSREQ */
    {
      gen_zbusreq_w((data >> 8) & 1, m68k.cycles);
      return;
    }

    case 0x12:  /* Z80 RESET */
    {
      gen_zreset_w((data >> 8) & 1, m68k.cycles);
      return;
    }

    case 0x20:  /* MEGA-CD */
    {
#ifdef LOG_SCD
      error("[%d][%d]write word CD register %X -> 0x%04X (%X)\n", v_counter, m68k.cycles, address, data, m68k.pc);
#endif
      if (system_hw == SYSTEM_MCD)
      {
        /* register index ($A12000-A1203F mirrored up to $A120FF) */
        switch (address & 0x3e)
        {
          case 0x00:  /* SUB-CPU interrupt & control */
          {
            /* RESET bit */
            if (data & 0x01)
            {
              /* trigger reset on 0->1 transition */
              if (!(scd.regs[0x00].byte.l & 0x01))
              {
                /* reset SUB-CPU */
                s68k_pulse_reset();
              }

              /* BUSREQ bit */
              if (data & 0x02)
              {
                /* SUB-CPU bus requested */
                s68k_pulse_halt();
              }
              else
              {
                /* SUB-CPU bus released */
                s68k_clear_halt();
              }
            }
            else
            {
              /* SUB-CPU is halted while !RESET is asserted */
              s68k_pulse_halt();
            }

            /* IFL2 bit */
            if (data & 0x100)
            {
              /* level 2 interrupt enabled ? */
              if (scd.regs[0x32>>1].byte.l & 0x04)
              {
                /* set IFL2 flag */
                scd.regs[0x00].byte.h |= 0x01;

                /* trigger level 2 interrupt */
                scd.pending |= (1 << 2);

                /* update IRQ level */
                s68k_update_irq((scd.pending & scd.regs[0x32>>1].byte.l) >> 1);
              }
            }

            /* update LSB only */
            scd.regs[0x00].byte.l = data & 0xff;
            return;
          }

          case 0x02:  /* Memory Mode */
          {
            m68k_poll_sync(0x02);

            /* PRG-RAM 128k bank mapped to $020000-$03FFFF (resp. $420000-$43FFFF) */
            m68k.memory_map[scd.cartridge.boot + 0x02].base = scd.prg_ram + ((data & 0xc0) << 11);
            m68k.memory_map[scd.cartridge.boot + 0x03].base = m68k.memory_map[scd.cartridge.boot + 0x02].base + 0x10000;

            /* check current mode */
            if (scd.regs[0x03>>1].byte.l & 0x04)
            {
              /* DMNA bit */
              if (data & 0x02)
              {
                /* writing 1 to DMNA in 1M mode will return Word-RAM to SUB-CPU in 2M mode */
                scd.dmna = 1;
              }
              else
              {
                /* writing 0 to DMNA in 1M mode actually set DMNA bit */
                data |= 0x02;

                /* update WP0-7, BK0-1 & DMNA bits */
                scd.regs[0x02>>1].w = (scd.regs[0x02>>1].w & ~0xffc2) | (data & 0xffc2);
                return;
              }
            }
            else
            {
              /* writing 0 in 2M mode does nothing */
              if (data & 0x02)
              {
                /* Word-RAM is assigned to SUB-CPU */
                scd.dmna = 1;

                /* clear RET bit */
                scd.regs[0x02>>1].w = (scd.regs[0x02>>1].w & ~0xffc3) | (data & 0xffc2);
                return;
              }
            }
             
            /* update WP0-7 & BK0-1 bits */
            scd.regs[0x02>>1].w = (scd.regs[0x02>>1].w & ~0xffc0) | (data & 0xffc0);
            return;
          }

          case 0x06:  /* H-INT vector (word access only ?) */
          {
            *(uint16 *)(m68k.memory_map[0].base + 0x72) = data;
            return;
          }

          case 0x0e:  /* MAIN-CPU communication flags */
          {
            m68k_poll_sync(0x0e);

            /* LSB is read-only (Mortal Kombat) */
            scd.regs[0x0e>>1].byte.h = data;
            return;
          }

          default:
          {
            /* MAIN-CPU communication words */
            if ((address & 0x30) == 0x10)
            {
              m68k_poll_sync(address & 0x1e);
              scd.regs[(address >> 1) & 0xff].w = data;
              return;
            }

            /* invalid address */
            m68k_unused_16_w (address, data);
            return;
          }
        }
      }

      m68k_unused_16_w (address, data);
      return;
    }

    case 0x30:  /* TIME */
    {
      cart.hw.time_w(address, data);
      return;
    }

    case 0x40:  /* TMSS */
    {
      if (config.bios & 1)
      {
        gen_tmss_w(address & 3, data);
        return;
      }
      m68k_unused_16_w(address, data);
      return;
    }

    case 0x50:  /* SVP */
    {
      if (!(address & 0xFD))
      {
        svp->ssp1601.gr[SSP_XST].byte.h = data;
        svp->ssp1601.gr[SSP_PM0].byte.h |= 2;
        svp->ssp1601.emu_status &= ~SSP_WAIT_PM0;
        return;
      }
      m68k_unused_16_w(address, data);
      return;
    }

    case 0x10:  /* MEMORY MODE */
    case 0x13:  /* unknown */
    case 0x41:  /* BOOT ROM */
    case 0x44:  /* RADICA */
    {
      m68k_unused_16_w (address, data);
      return;
    }
            
    default:  /* Invalid address */
    {
      m68k_lockup_w_16 (address, data);
      return;
    }
  }
}