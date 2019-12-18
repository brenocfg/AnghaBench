#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ SekCyclesDone () ; 
 int cycles_68k_to_z80 (scalar_t__) ; 
 scalar_t__ last_z80_sync ; 
 int z80_cycle_aim ; 

__attribute__((used)) static int z80_cycles_from_68k(void)
{
  return z80_cycle_aim
    + cycles_68k_to_z80(SekCyclesDone() - last_z80_sync);
}