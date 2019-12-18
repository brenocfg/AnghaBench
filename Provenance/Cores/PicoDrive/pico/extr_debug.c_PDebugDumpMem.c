#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  vsram; int /*<<< orphan*/  vram; int /*<<< orphan*/  ram; int /*<<< orphan*/  vramb; int /*<<< orphan*/  cram; int /*<<< orphan*/  zram; } ;
struct TYPE_9__ {int /*<<< orphan*/  pal; int /*<<< orphan*/ * dram; int /*<<< orphan*/  sdram; } ;
struct TYPE_8__ {int* s68k_regs; int /*<<< orphan*/  bram; int /*<<< orphan*/  pcm_ram; int /*<<< orphan*/  word_ram2M; int /*<<< orphan*/ * word_ram1M; int /*<<< orphan*/  prg_ram; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_array; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_array; } ;

/* Variables and functions */
 int PAHW_32X ; 
 int PAHW_MCD ; 
 int PAHW_SMS ; 
 TYPE_5__ Pico ; 
 TYPE_4__* Pico32xMem ; 
 int PicoAHW ; 
 TYPE_3__* Pico_mcd ; 
 int /*<<< orphan*/  dump_ram (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_ram_noswab (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ msh2 ; 
 TYPE_1__ ssh2 ; 
 int /*<<< orphan*/  wram_1M_to_2M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wram_2M_to_1M (int /*<<< orphan*/ ) ; 

void PDebugDumpMem(void)
{
  dump_ram_noswab(Pico.zram, "dumps/zram.bin");
  dump_ram(Pico.cram, "dumps/cram.bin");

  if (PicoAHW & PAHW_SMS)
  {
    dump_ram_noswab(Pico.vramb, "dumps/vram.bin");
  }
  else
  {
    dump_ram(Pico.ram,  "dumps/ram.bin");
    dump_ram(Pico.vram, "dumps/vram.bin");
    dump_ram(Pico.vsram,"dumps/vsram.bin");
  }

  if (PicoAHW & PAHW_MCD)
  {
    dump_ram(Pico_mcd->prg_ram, "dumps/prg_ram.bin");
    if (Pico_mcd->s68k_regs[3]&4) // 1M mode?
      wram_1M_to_2M(Pico_mcd->word_ram2M);
    dump_ram(Pico_mcd->word_ram2M, "dumps/word_ram_2M.bin");
    wram_2M_to_1M(Pico_mcd->word_ram2M);
    dump_ram(Pico_mcd->word_ram1M[0], "dumps/word_ram_1M_0.bin");
    dump_ram(Pico_mcd->word_ram1M[1], "dumps/word_ram_1M_1.bin");
    if (!(Pico_mcd->s68k_regs[3]&4)) // 2M mode?
      wram_2M_to_1M(Pico_mcd->word_ram2M);
    dump_ram_noswab(Pico_mcd->pcm_ram,"dumps/pcm_ram.bin");
    dump_ram_noswab(Pico_mcd->bram,   "dumps/bram.bin");
  }

#ifndef NO_32X
  if (PicoAHW & PAHW_32X)
  {
    dump_ram(Pico32xMem->sdram, "dumps/sdram.bin");
    dump_ram(Pico32xMem->dram[0], "dumps/dram0.bin");
    dump_ram(Pico32xMem->dram[1], "dumps/dram1.bin");
    dump_ram(Pico32xMem->pal, "dumps/pal32x.bin");
    dump_ram(msh2.data_array, "dumps/data_array0.bin");
    dump_ram(ssh2.data_array, "dumps/data_array1.bin");
  }
#endif
}