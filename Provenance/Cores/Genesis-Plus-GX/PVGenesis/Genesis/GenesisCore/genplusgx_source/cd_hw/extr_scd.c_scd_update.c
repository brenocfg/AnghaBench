#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ dma_w; } ;
struct TYPE_13__ {int cycles; } ;
struct TYPE_12__ {unsigned int cycles; } ;
struct TYPE_11__ {scalar_t__ cycles; } ;
struct TYPE_10__ {scalar_t__ cycles; int pending; scalar_t__ timer; TYPE_2__* regs; } ;
struct TYPE_8__ {int l; int h; } ;
struct TYPE_9__ {TYPE_1__ byte; } ;

/* Variables and functions */
 int SCYCLES_PER_LINE ; 
 int TIMERS_SCYCLES_RATIO ; 
 TYPE_7__ cdc ; 
 int /*<<< orphan*/  cdc_dma_update () ; 
 TYPE_6__ cdd ; 
 int /*<<< orphan*/  cdd_update () ; 
 int /*<<< orphan*/  gfx_update (scalar_t__) ; 
 TYPE_5__ m68k ; 
 int /*<<< orphan*/  m68k_run (unsigned int) ; 
 TYPE_4__ s68k ; 
 int /*<<< orphan*/  s68k_run (scalar_t__) ; 
 int /*<<< orphan*/  s68k_update_irq (int) ; 
 TYPE_3__ scd ; 

void scd_update(unsigned int cycles)
{
  /* update CDC DMA transfer */
  if (cdc.dma_w)
  {
    cdc_dma_update();
  }

  /* run both CPU in sync until end of line */
  do
  {
    m68k_run(cycles);
    s68k_run(scd.cycles + SCYCLES_PER_LINE);
  }
  while ((m68k.cycles < cycles) || (s68k.cycles < (scd.cycles + SCYCLES_PER_LINE)));

  /* increment CD hardware cycle counter */
  scd.cycles += SCYCLES_PER_LINE;

  /* CDD processing at 75Hz (one clock = 12500000/75 = 500000/3 CPU clocks) */
  cdd.cycles += (SCYCLES_PER_LINE * 3);
  if (cdd.cycles >= (500000 * 4))
  {
    /* reload CDD cycle counter */
    cdd.cycles -= (500000 * 4);

    /* update CDD sector */
    cdd_update();

    /* check if a new CDD command has been processed */
    if (!(scd.regs[0x4a>>1].byte.l & 0xf0))
    {
      /* reset CDD command wait flag */
      scd.regs[0x4a>>1].byte.l = 0xf0;

      /* pending level 4 interrupt */
      scd.pending |= (1 << 4);

      /* level 4 interrupt enabled */
      if (scd.regs[0x32>>1].byte.l & 0x10)
      {
        /* update IRQ level */
        s68k_update_irq((scd.pending & scd.regs[0x32>>1].byte.l) >> 1);
      }
    }
  }

  /* Timer */
  if (scd.timer)
  {
    /* decrement timer */
    scd.timer -= SCYCLES_PER_LINE;
    if (scd.timer <= 0)
    {
      /* reload timer (one timer clock = 384 CPU cycles) */
      scd.timer += (scd.regs[0x30>>1].byte.l * TIMERS_SCYCLES_RATIO);

      /* level 3 interrupt enabled ? */
      if (scd.regs[0x32>>1].byte.l & 0x08)
      {
        /* trigger level 3 interrupt */
        scd.pending |= (1 << 3);

        /* update IRQ level */
        s68k_update_irq((scd.pending & scd.regs[0x32>>1].byte.l) >> 1);
      }
    }
  }

  /* GFX processing */
  if (scd.regs[0x58>>1].byte.h & 0x80)
  {
    /* update graphics operation if running */
    gfx_update(scd.cycles);
  }
}