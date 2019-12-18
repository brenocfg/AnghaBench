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
struct TYPE_2__ {int /*<<< orphan*/  dram; } ;

/* Variables and functions */
 int /*<<< orphan*/  PicoRead16_svpca1 ; 
 int /*<<< orphan*/  PicoRead16_svpca2 ; 
 int /*<<< orphan*/  PicoRead16_svpr ; 
 int /*<<< orphan*/  PicoRead8_svpr ; 
 int /*<<< orphan*/  PicoWrite16_dram ; 
 int /*<<< orphan*/  PicoWrite16_svpr ; 
 int /*<<< orphan*/  PicoWrite8_io ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write8_map ; 
 TYPE_1__* svp ; 

void PicoSVPMemSetup(void)
{
  // 68k memmap:
  // DRAM
  cpu68k_map_set(m68k_read8_map,   0x300000, 0x31ffff, svp->dram, 0);
  cpu68k_map_set(m68k_read16_map,  0x300000, 0x31ffff, svp->dram, 0);
  cpu68k_map_set(m68k_write8_map,  0x300000, 0x31ffff, svp->dram, 0);
  cpu68k_map_set(m68k_write16_map, 0x300000, 0x31ffff, svp->dram, 0);
  cpu68k_map_set(m68k_write16_map, 0x300000, 0x30ffff, PicoWrite16_dram, 1);

  // DRAM (cell arrange)
  cpu68k_map_set(m68k_read16_map,  0x390000, 0x39ffff, PicoRead16_svpca1, 1);
  cpu68k_map_set(m68k_read16_map,  0x3a0000, 0x3affff, PicoRead16_svpca2, 1);

  // regs
  cpu68k_map_set(m68k_read8_map,   0xa10000, 0xa1ffff, PicoRead8_svpr, 1);
  cpu68k_map_set(m68k_read16_map,  0xa10000, 0xa1ffff, PicoRead16_svpr, 1);
  cpu68k_map_set(m68k_write8_map,  0xa10000, 0xa1ffff, PicoWrite8_io, 1); // PicoWrite8_svpr
  cpu68k_map_set(m68k_write16_map, 0xa10000, 0xa1ffff, PicoWrite16_svpr, 1);
}