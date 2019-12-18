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
typedef  int uint16 ;
struct TYPE_10__ {int l; } ;
struct TYPE_13__ {int w; TYPE_3__ byte; } ;
struct TYPE_14__ {TYPE_6__ poll; TYPE_2__* memory_map; } ;
struct TYPE_12__ {TYPE_6__ poll; } ;
struct TYPE_8__ {int boot; } ;
struct TYPE_11__ {scalar_t__ pending; scalar_t__ cycles; scalar_t__ stopwatch; scalar_t__ timer; TYPE_6__* regs; scalar_t__ prg_ram; TYPE_1__ cartridge; scalar_t__ dmna; } ;
struct TYPE_9__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdc_reset () ; 
 int /*<<< orphan*/  cdd_reset () ; 
 int /*<<< orphan*/  gfx_reset () ; 
 TYPE_7__ m68k ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_reset () ; 
 TYPE_5__ s68k ; 
 TYPE_4__ scd ; 
 int /*<<< orphan*/  word_ram_switch (int /*<<< orphan*/ ) ; 

void scd_reset(int hard)
{
  /* TODO: figure what exactly is resetted when RESET bit is cleared by SUB-CPU */
  if (hard)
  {
    int i;
    
    /* Clear all ASIC registers by default */
    memset(scd.regs, 0, sizeof(scd.regs));

    /* Clear pending DMNA write status */
    scd.dmna = 0;

    /* H-INT default vector */
    *(uint16 *)(m68k.memory_map[0].base + 0x70) = 0x00FF;
    *(uint16 *)(m68k.memory_map[0].base + 0x72) = 0xFFFF;

    /* Power ON initial values (MAIN-CPU side) */
    scd.regs[0x00>>1].w = 0x0002;
    scd.regs[0x02>>1].w = 0x0001;

    /* 2M mode */
    word_ram_switch(0);

    /* reset PRG-RAM banking on MAIN-CPU side */
    for (i=scd.cartridge.boot+0x02; i<scd.cartridge.boot+0x20; i+=4)
    {
      /* MAIN-CPU: $020000-$03FFFF (resp. $420000-$43FFFF) mapped to first 128KB PRG-RAM bank (mirrored each 256KB) */
      m68k.memory_map[i].base = scd.prg_ram;
      m68k.memory_map[i+1].base = scd.prg_ram + 0x10000;
    }
  }
  else
  {
    /* Clear only SUB-CPU side registers */
    memset(&scd.regs[0x04>>1], 0, sizeof(scd.regs) - 4);
  }

  /* SUB-CPU side default values */
  scd.regs[0x08>>1].w = 0xffff;
  scd.regs[0x0a>>1].w = 0xffff;
  scd.regs[0x36>>1].w = 0x0100;
  scd.regs[0x40>>1].w = 0x000f;
  scd.regs[0x42>>1].w = 0xffff;
  scd.regs[0x44>>1].w = 0xffff;
  scd.regs[0x46>>1].w = 0xffff;
  scd.regs[0x48>>1].w = 0xffff;
  scd.regs[0x4a>>1].w = 0xffff;

  /* RESET register always return 1 (register $06 is unused by both sides, it is used for SUB-CPU first register) */
  scd.regs[0x06>>1].byte.l = 0x01;

  /* Reset Timer & Stopwatch counters */
  scd.timer = 0;
  scd.stopwatch = 0;

  /* Reset frame cycle counter */
  scd.cycles = 0;

  /* Clear pending interrupts */
  scd.pending = 0;

  /* Clear CPU polling detection */
  memset(&m68k.poll, 0, sizeof(m68k.poll));
  memset(&s68k.poll, 0, sizeof(s68k.poll));

  /* Reset CD hardware */
  cdd_reset();
  cdc_reset();
  gfx_reset();
  pcm_reset();
}