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
struct TYPE_5__ {int sram_reg; scalar_t__ ncart_in; } ;
struct TYPE_8__ {unsigned int romsize; scalar_t__ rom; TYPE_1__ m; } ;
struct TYPE_7__ {unsigned long* Fetch; } ;
struct TYPE_6__ {unsigned int start; } ;

/* Variables and functions */
 int EL_32X ; 
 int EL_ANOMALY ; 
 unsigned int M68K_BANK_MASK ; 
 TYPE_4__ Pico ; 
 TYPE_3__ PicoCpuFM68k ; 
 int SRR_MAPPED ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  bank_map_handler () ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elprintf (int,char*,int,...) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 

__attribute__((used)) static void bank_switch(int b)
{
  unsigned int rs, bank;

  if (Pico.m.ncart_in)
    return;

  bank = b << 20;
  if ((Pico.m.sram_reg & SRR_MAPPED) && bank == SRam.start) {
    bank_map_handler();
    return;
  }

  if (bank >= Pico.romsize) {
    elprintf(EL_32X|EL_ANOMALY, "missing bank @ %06x", bank);
    bank_map_handler();
    return;
  }

  // 32X ROM (unbanked, XXX: consider mirroring?)
  rs = (Pico.romsize + M68K_BANK_MASK) & ~M68K_BANK_MASK;
  rs -= bank;
  if (rs > 0x100000)
    rs = 0x100000;
  cpu68k_map_set(m68k_read8_map,   0x900000, 0x900000 + rs - 1, Pico.rom + bank, 0);
  cpu68k_map_set(m68k_read16_map,  0x900000, 0x900000 + rs - 1, Pico.rom + bank, 0);

  elprintf(EL_32X, "bank %06x-%06x -> %06x", 0x900000, 0x900000 + rs - 1, bank);

#ifdef EMU_F68K
  // setup FAME fetchmap
  for (rs = 0x90; rs < 0xa0; rs++)
    PicoCpuFM68k.Fetch[rs] = (unsigned long)Pico.rom + bank - 0x900000;
#endif
}