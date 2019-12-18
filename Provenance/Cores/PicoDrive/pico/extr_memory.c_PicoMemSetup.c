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
struct TYPE_8__ {int romsize; scalar_t__ ram; scalar_t__ rom; } ;
struct TYPE_7__ {int /*<<< orphan*/ * fetch32; int /*<<< orphan*/ * fetch16; int /*<<< orphan*/ * fetch8; int /*<<< orphan*/ * checkpc; void* write32; void* write16; void* write8; void* read32; void* read16; void* read8; } ;
struct TYPE_6__ {unsigned long* Fetch; int /*<<< orphan*/  write_long; int /*<<< orphan*/  write_word; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  read_long; int /*<<< orphan*/  read_word; int /*<<< orphan*/  read_byte; } ;
struct TYPE_5__ {int flags; int end; int start; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int FAMEC_FETCHBITS ; 
 int M68K_FETCHBANK1 ; 
 int M68K_MEM_SHIFT ; 
 TYPE_4__ Pico ; 
 TYPE_3__ PicoCpuCM68k ; 
 TYPE_2__ PicoCpuFM68k ; 
 scalar_t__ PicoRead16_io ; 
 scalar_t__ PicoRead16_sram ; 
 scalar_t__ PicoRead16_vdp ; 
 scalar_t__ PicoRead16_z80 ; 
 scalar_t__ PicoRead8_io ; 
 scalar_t__ PicoRead8_sram ; 
 scalar_t__ PicoRead8_vdp ; 
 scalar_t__ PicoRead8_z80 ; 
 scalar_t__ PicoWrite16_io ; 
 scalar_t__ PicoWrite16_sram ; 
 scalar_t__ PicoWrite16_vdp ; 
 scalar_t__ PicoWrite16_z80 ; 
 scalar_t__ PicoWrite8_io ; 
 scalar_t__ PicoWrite8_sram ; 
 scalar_t__ PicoWrite8_vdp ; 
 scalar_t__ PicoWrite8_z80 ; 
 int SRF_ENABLED ; 
 TYPE_1__ SRam ; 
 int /*<<< orphan*/  cpu68k_map_set (scalar_t__,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  m68k_mem_setup () ; 
 int /*<<< orphan*/  m68k_read16 ; 
 scalar_t__ m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read32 ; 
 int /*<<< orphan*/  m68k_read8 ; 
 scalar_t__ m68k_read8_map ; 
 scalar_t__ m68k_unmapped_read16 ; 
 scalar_t__ m68k_unmapped_read8 ; 
 scalar_t__ m68k_unmapped_write16 ; 
 scalar_t__ m68k_unmapped_write8 ; 
 int /*<<< orphan*/  m68k_write16 ; 
 scalar_t__ m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write32 ; 
 int /*<<< orphan*/  m68k_write8 ; 
 scalar_t__ m68k_write8_map ; 
 int /*<<< orphan*/  z80_mem_setup () ; 

void PicoMemSetup(void)
{
  int mask, rs, a;

  // setup the memory map
  cpu68k_map_set(m68k_read8_map,   0x000000, 0xffffff, m68k_unmapped_read8, 1);
  cpu68k_map_set(m68k_read16_map,  0x000000, 0xffffff, m68k_unmapped_read16, 1);
  cpu68k_map_set(m68k_write8_map,  0x000000, 0xffffff, m68k_unmapped_write8, 1);
  cpu68k_map_set(m68k_write16_map, 0x000000, 0xffffff, m68k_unmapped_write16, 1);

  // ROM
  // align to bank size. We know ROM loader allocated enough for this
  mask = (1 << M68K_MEM_SHIFT) - 1;
  rs = (Pico.romsize + mask) & ~mask;
  cpu68k_map_set(m68k_read8_map,  0x000000, rs - 1, Pico.rom, 0);
  cpu68k_map_set(m68k_read16_map, 0x000000, rs - 1, Pico.rom, 0);

  // Common case of on-cart (save) RAM, usually at 0x200000-...
  if ((SRam.flags & SRF_ENABLED) && SRam.data != NULL) {
    rs = SRam.end - SRam.start;
    rs = (rs + mask) & ~mask;
    if (SRam.start + rs >= 0x1000000)
      rs = 0x1000000 - SRam.start;
    cpu68k_map_set(m68k_read8_map,   SRam.start, SRam.start + rs - 1, PicoRead8_sram, 1);
    cpu68k_map_set(m68k_read16_map,  SRam.start, SRam.start + rs - 1, PicoRead16_sram, 1);
    cpu68k_map_set(m68k_write8_map,  SRam.start, SRam.start + rs - 1, PicoWrite8_sram, 1);
    cpu68k_map_set(m68k_write16_map, SRam.start, SRam.start + rs - 1, PicoWrite16_sram, 1);
  }

  // Z80 region
  cpu68k_map_set(m68k_read8_map,   0xa00000, 0xa0ffff, PicoRead8_z80, 1);
  cpu68k_map_set(m68k_read16_map,  0xa00000, 0xa0ffff, PicoRead16_z80, 1);
  cpu68k_map_set(m68k_write8_map,  0xa00000, 0xa0ffff, PicoWrite8_z80, 1);
  cpu68k_map_set(m68k_write16_map, 0xa00000, 0xa0ffff, PicoWrite16_z80, 1);

  // IO/control region
  cpu68k_map_set(m68k_read8_map,   0xa10000, 0xa1ffff, PicoRead8_io, 1);
  cpu68k_map_set(m68k_read16_map,  0xa10000, 0xa1ffff, PicoRead16_io, 1);
  cpu68k_map_set(m68k_write8_map,  0xa10000, 0xa1ffff, PicoWrite8_io, 1);
  cpu68k_map_set(m68k_write16_map, 0xa10000, 0xa1ffff, PicoWrite16_io, 1);

  // VDP region
  for (a = 0xc00000; a < 0xe00000; a += 0x010000) {
    if ((a & 0xe700e0) != 0xc00000)
      continue;
    cpu68k_map_set(m68k_read8_map,   a, a + 0xffff, PicoRead8_vdp, 1);
    cpu68k_map_set(m68k_read16_map,  a, a + 0xffff, PicoRead16_vdp, 1);
    cpu68k_map_set(m68k_write8_map,  a, a + 0xffff, PicoWrite8_vdp, 1);
    cpu68k_map_set(m68k_write16_map, a, a + 0xffff, PicoWrite16_vdp, 1);
  }

  // RAM and it's mirrors
  for (a = 0xe00000; a < 0x1000000; a += 0x010000) {
    cpu68k_map_set(m68k_read8_map,   a, a + 0xffff, Pico.ram, 0);
    cpu68k_map_set(m68k_read16_map,  a, a + 0xffff, Pico.ram, 0);
    cpu68k_map_set(m68k_write8_map,  a, a + 0xffff, Pico.ram, 0);
    cpu68k_map_set(m68k_write16_map, a, a + 0xffff, Pico.ram, 0);
  }

  // Setup memory callbacks:
#ifdef EMU_C68K
  PicoCpuCM68k.read8  = (void *)m68k_read8_map;
  PicoCpuCM68k.read16 = (void *)m68k_read16_map;
  PicoCpuCM68k.read32 = (void *)m68k_read16_map;
  PicoCpuCM68k.write8  = (void *)m68k_write8_map;
  PicoCpuCM68k.write16 = (void *)m68k_write16_map;
  PicoCpuCM68k.write32 = (void *)m68k_write16_map;
  PicoCpuCM68k.checkpc = NULL; /* unused */
  PicoCpuCM68k.fetch8  = NULL;
  PicoCpuCM68k.fetch16 = NULL;
  PicoCpuCM68k.fetch32 = NULL;
#endif
#ifdef EMU_F68K
  PicoCpuFM68k.read_byte  = m68k_read8;
  PicoCpuFM68k.read_word  = m68k_read16;
  PicoCpuFM68k.read_long  = m68k_read32;
  PicoCpuFM68k.write_byte = m68k_write8;
  PicoCpuFM68k.write_word = m68k_write16;
  PicoCpuFM68k.write_long = m68k_write32;

  // setup FAME fetchmap
  {
    int i;
    // by default, point everything to first 64k of ROM
    for (i = 0; i < M68K_FETCHBANK1; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico.rom - (i<<(24-FAMEC_FETCHBITS));
    // now real ROM
    for (i = 0; i < M68K_FETCHBANK1 && (i<<(24-FAMEC_FETCHBITS)) < Pico.romsize; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico.rom;
    // .. and RAM
    for (i = M68K_FETCHBANK1*14/16; i < M68K_FETCHBANK1; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico.ram - (i<<(24-FAMEC_FETCHBITS));
  }
#endif
#ifdef EMU_M68K
  m68k_mem_setup();
#endif

  z80_mem_setup();
}