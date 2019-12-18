#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int scanline; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int z80_cyclesDone () ; 
 int z80_scanline ; 
 int z80_scanline_cycles ; 

__attribute__((used)) static int get_scanline(int is_from_z80)
{
  if (is_from_z80) {
    int cycles = z80_cyclesDone();
    while (cycles - z80_scanline_cycles >= 228)
      z80_scanline++, z80_scanline_cycles += 228;
    return z80_scanline;
  }

  return Pico.m.scanline;
}