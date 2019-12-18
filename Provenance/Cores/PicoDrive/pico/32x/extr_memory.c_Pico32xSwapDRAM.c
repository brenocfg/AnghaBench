#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * dram; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_MEMORY (int /*<<< orphan*/ ) ; 
 TYPE_3__* Pico32xMem ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write16_dram0_ow ; 
 int /*<<< orphan*/  m68k_write16_dram1_ow ; 
 int /*<<< orphan*/  m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write8_dram0_ow ; 
 int /*<<< orphan*/  m68k_write8_dram1_ow ; 
 int /*<<< orphan*/  m68k_write8_map ; 
 TYPE_2__* sh2_read16_map ; 
 TYPE_1__* sh2_read8_map ; 
 int /*<<< orphan*/  sh2_write16_dram0 ; 
 int /*<<< orphan*/  sh2_write16_dram1 ; 
 int /*<<< orphan*/ * sh2_write16_map ; 
 int /*<<< orphan*/  sh2_write8_dram0 ; 
 int /*<<< orphan*/  sh2_write8_dram1 ; 
 int /*<<< orphan*/ * sh2_write8_map ; 

void Pico32xSwapDRAM(int b)
{
  cpu68k_map_set(m68k_read8_map,   0x840000, 0x85ffff, Pico32xMem->dram[b], 0);
  cpu68k_map_set(m68k_read16_map,  0x840000, 0x85ffff, Pico32xMem->dram[b], 0);
  cpu68k_map_set(m68k_read8_map,   0x860000, 0x87ffff, Pico32xMem->dram[b], 0);
  cpu68k_map_set(m68k_read16_map,  0x860000, 0x87ffff, Pico32xMem->dram[b], 0);
  cpu68k_map_set(m68k_write8_map,  0x840000, 0x87ffff,
                 b ? m68k_write8_dram1_ow : m68k_write8_dram0_ow, 1);
  cpu68k_map_set(m68k_write16_map, 0x840000, 0x87ffff,
                 b ? m68k_write16_dram1_ow : m68k_write16_dram0_ow, 1);

  // SH2
  sh2_read8_map[0x04/2].addr  = sh2_read8_map[0x24/2].addr  =
  sh2_read16_map[0x04/2].addr = sh2_read16_map[0x24/2].addr = MAP_MEMORY(Pico32xMem->dram[b]);

  sh2_write8_map[0x04/2]  = sh2_write8_map[0x24/2]  = b ? sh2_write8_dram1 : sh2_write8_dram0;
  sh2_write16_map[0x04/2] = sh2_write16_map[0x24/2] = b ? sh2_write16_dram1 : sh2_write16_dram0;
}