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
struct TYPE_10__ {int romsize; scalar_t__ ram; scalar_t__ rom; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fetch32; int /*<<< orphan*/ * fetch16; int /*<<< orphan*/ * fetch8; int /*<<< orphan*/ * checkpc; void* write32; void* write16; void* write8; void* read32; void* read16; void* read8; } ;
struct TYPE_8__ {unsigned long* Fetch; } ;
struct TYPE_7__ {unsigned long* Fetch; int /*<<< orphan*/  write_long; int /*<<< orphan*/  write_word; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  read_long; int /*<<< orphan*/  read_word; int /*<<< orphan*/  read_byte; } ;
struct TYPE_6__ {scalar_t__ word_ram2M; scalar_t__ prg_ram; } ;

/* Variables and functions */
 int FAMEC_FETCHBITS ; 
 int M68K_FETCHBANK1 ; 
 int POPT_EN_MCD_RAMCART ; 
 TYPE_5__ Pico ; 
 TYPE_4__ PicoCpuCS68k ; 
 TYPE_3__ PicoCpuFM68k ; 
 TYPE_2__ PicoCpuFS68k ; 
 int /*<<< orphan*/  PicoMemSetup () ; 
 int PicoOpt ; 
 scalar_t__ PicoRead16_mcd_io ; 
 scalar_t__ PicoRead8_mcd_io ; 
 scalar_t__ PicoReadM68k16_ramc ; 
 scalar_t__ PicoReadM68k8_ramc ; 
 scalar_t__ PicoReadS68k16_bram ; 
 scalar_t__ PicoReadS68k16_pr ; 
 scalar_t__ PicoReadS68k8_bram ; 
 scalar_t__ PicoReadS68k8_pr ; 
 scalar_t__ PicoWrite16_mcd_io ; 
 scalar_t__ PicoWrite8_mcd_io ; 
 scalar_t__ PicoWriteM68k16_ramc ; 
 scalar_t__ PicoWriteM68k8_ramc ; 
 scalar_t__ PicoWriteS68k16_bram ; 
 scalar_t__ PicoWriteS68k16_pr ; 
 scalar_t__ PicoWriteS68k16_prgwp ; 
 scalar_t__ PicoWriteS68k8_bram ; 
 scalar_t__ PicoWriteS68k8_pr ; 
 scalar_t__ PicoWriteS68k8_prgwp ; 
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  cpu68k_map_set (scalar_t__,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  m68k_mem_setup_cd () ; 
 scalar_t__ m68k_read16_map ; 
 scalar_t__ m68k_read8_map ; 
 scalar_t__ m68k_write16_map ; 
 scalar_t__ m68k_write8_map ; 
 int /*<<< orphan*/  remap_word_ram (int) ; 
 int /*<<< orphan*/  s68k_read16 ; 
 scalar_t__ s68k_read16_map ; 
 int /*<<< orphan*/  s68k_read32 ; 
 int /*<<< orphan*/  s68k_read8 ; 
 scalar_t__ s68k_read8_map ; 
 scalar_t__ s68k_unmapped_read16 ; 
 scalar_t__ s68k_unmapped_read8 ; 
 scalar_t__ s68k_unmapped_write16 ; 
 scalar_t__ s68k_unmapped_write8 ; 
 int /*<<< orphan*/  s68k_write16 ; 
 scalar_t__ s68k_write16_map ; 
 int /*<<< orphan*/  s68k_write32 ; 
 int /*<<< orphan*/  s68k_write8 ; 
 scalar_t__ s68k_write8_map ; 

void PicoMemSetupCD(void)
{
  // setup default main68k map
  PicoMemSetup();

  // main68k map (BIOS mapped by PicoMemSetup()):
  // RAM cart
  if (PicoOpt & POPT_EN_MCD_RAMCART) {
    cpu68k_map_set(m68k_read8_map,   0x400000, 0x7fffff, PicoReadM68k8_ramc, 1);
    cpu68k_map_set(m68k_read16_map,  0x400000, 0x7fffff, PicoReadM68k16_ramc, 1);
    cpu68k_map_set(m68k_write8_map,  0x400000, 0x7fffff, PicoWriteM68k8_ramc, 1);
    cpu68k_map_set(m68k_write16_map, 0x400000, 0x7fffff, PicoWriteM68k16_ramc, 1);
  }

  // registers/IO:
  cpu68k_map_set(m68k_read8_map,   0xa10000, 0xa1ffff, PicoRead8_mcd_io, 1);
  cpu68k_map_set(m68k_read16_map,  0xa10000, 0xa1ffff, PicoRead16_mcd_io, 1);
  cpu68k_map_set(m68k_write8_map,  0xa10000, 0xa1ffff, PicoWrite8_mcd_io, 1);
  cpu68k_map_set(m68k_write16_map, 0xa10000, 0xa1ffff, PicoWrite16_mcd_io, 1);

  // sub68k map
  cpu68k_map_set(s68k_read8_map,   0x000000, 0xffffff, s68k_unmapped_read8, 1);
  cpu68k_map_set(s68k_read16_map,  0x000000, 0xffffff, s68k_unmapped_read16, 1);
  cpu68k_map_set(s68k_write8_map,  0x000000, 0xffffff, s68k_unmapped_write8, 1);
  cpu68k_map_set(s68k_write16_map, 0x000000, 0xffffff, s68k_unmapped_write16, 1);

  // PRG RAM
  cpu68k_map_set(s68k_read8_map,   0x000000, 0x07ffff, Pico_mcd->prg_ram, 0);
  cpu68k_map_set(s68k_read16_map,  0x000000, 0x07ffff, Pico_mcd->prg_ram, 0);
  cpu68k_map_set(s68k_write8_map,  0x000000, 0x07ffff, Pico_mcd->prg_ram, 0);
  cpu68k_map_set(s68k_write16_map, 0x000000, 0x07ffff, Pico_mcd->prg_ram, 0);
  cpu68k_map_set(s68k_write8_map,  0x000000, 0x01ffff, PicoWriteS68k8_prgwp, 1);
  cpu68k_map_set(s68k_write16_map, 0x000000, 0x01ffff, PicoWriteS68k16_prgwp, 1);

  // BRAM
  cpu68k_map_set(s68k_read8_map,   0xfe0000, 0xfeffff, PicoReadS68k8_bram, 1);
  cpu68k_map_set(s68k_read16_map,  0xfe0000, 0xfeffff, PicoReadS68k16_bram, 1);
  cpu68k_map_set(s68k_write8_map,  0xfe0000, 0xfeffff, PicoWriteS68k8_bram, 1);
  cpu68k_map_set(s68k_write16_map, 0xfe0000, 0xfeffff, PicoWriteS68k16_bram, 1);

  // PCM, regs
  cpu68k_map_set(s68k_read8_map,   0xff0000, 0xffffff, PicoReadS68k8_pr, 1);
  cpu68k_map_set(s68k_read16_map,  0xff0000, 0xffffff, PicoReadS68k16_pr, 1);
  cpu68k_map_set(s68k_write8_map,  0xff0000, 0xffffff, PicoWriteS68k8_pr, 1);
  cpu68k_map_set(s68k_write16_map, 0xff0000, 0xffffff, PicoWriteS68k16_pr, 1);

  // RAMs
  remap_word_ram(1);

#ifdef EMU_C68K
  // s68k
  PicoCpuCS68k.read8  = (void *)s68k_read8_map;
  PicoCpuCS68k.read16 = (void *)s68k_read16_map;
  PicoCpuCS68k.read32 = (void *)s68k_read16_map;
  PicoCpuCS68k.write8  = (void *)s68k_write8_map;
  PicoCpuCS68k.write16 = (void *)s68k_write16_map;
  PicoCpuCS68k.write32 = (void *)s68k_write16_map;
  PicoCpuCS68k.checkpc = NULL; /* unused */
  PicoCpuCS68k.fetch8  = NULL;
  PicoCpuCS68k.fetch16 = NULL;
  PicoCpuCS68k.fetch32 = NULL;
#endif
#ifdef EMU_F68K
  // s68k
  PicoCpuFS68k.read_byte  = s68k_read8;
  PicoCpuFS68k.read_word  = s68k_read16;
  PicoCpuFS68k.read_long  = s68k_read32;
  PicoCpuFS68k.write_byte = s68k_write8;
  PicoCpuFS68k.write_word = s68k_write16;
  PicoCpuFS68k.write_long = s68k_write32;

  // setup FAME fetchmap
  {
    int i;
    // M68k
    // by default, point everything to fitst 64k of ROM (BIOS)
    for (i = 0; i < M68K_FETCHBANK1; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico.rom - (i<<(24-FAMEC_FETCHBITS));
    // now real ROM (BIOS)
    for (i = 0; i < M68K_FETCHBANK1 && (i<<(24-FAMEC_FETCHBITS)) < Pico.romsize; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico.rom;
    // .. and RAM
    for (i = M68K_FETCHBANK1*14/16; i < M68K_FETCHBANK1; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico.ram - (i<<(24-FAMEC_FETCHBITS));
    // S68k
    // PRG RAM is default
    for (i = 0; i < M68K_FETCHBANK1; i++)
      PicoCpuFS68k.Fetch[i] = (unsigned long)Pico_mcd->prg_ram - (i<<(24-FAMEC_FETCHBITS));
    // real PRG RAM
    for (i = 0; i < M68K_FETCHBANK1 && (i<<(24-FAMEC_FETCHBITS)) < 0x80000; i++)
      PicoCpuFS68k.Fetch[i] = (unsigned long)Pico_mcd->prg_ram;
    // WORD RAM 2M area
    for (i = M68K_FETCHBANK1*0x08/0x100; i < M68K_FETCHBANK1 && (i<<(24-FAMEC_FETCHBITS)) < 0xc0000; i++)
      PicoCpuFS68k.Fetch[i] = (unsigned long)Pico_mcd->word_ram2M - 0x80000;
    // remap_word_ram() will setup word ram for both
  }
#endif
#ifdef EMU_M68K
  m68k_mem_setup_cd();
#endif
}