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
typedef  int u32 ;
struct TYPE_2__ {void** prg_ram_b; } ;

/* Variables and functions */
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  cpu68k_map_all_ram (int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68k_map_unmap (int,int) ; 

__attribute__((used)) static void remap_prg_window(u32 r1, u32 r3)
{
  // PRG RAM
  if (r1 & 2) {
    void *bank = Pico_mcd->prg_ram_b[(r3 >> 6) & 3];
    cpu68k_map_all_ram(0x020000, 0x03ffff, bank, 0);
  }
  else {
    m68k_map_unmap(0x020000, 0x03ffff);
  }
}