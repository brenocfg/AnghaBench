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
 int /*<<< orphan*/  PicoMemSetup () ; 
 int /*<<< orphan*/  PicoRead16_pico ; 
 int /*<<< orphan*/  PicoRead8_pico ; 
 int /*<<< orphan*/  PicoWrite16_pico ; 
 int /*<<< orphan*/  PicoWrite8_pico ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_map_unmap (int,int) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write8_map ; 

void PicoMemSetupPico(void)
{
  PicoMemSetup();

  // no MD IO or Z80 on Pico
  m68k_map_unmap(0x400000, 0xbfffff);

  // map Pico I/O
  cpu68k_map_set(m68k_read8_map,   0x800000, 0x80ffff, PicoRead8_pico, 1);
  cpu68k_map_set(m68k_read16_map,  0x800000, 0x80ffff, PicoRead16_pico, 1);
  cpu68k_map_set(m68k_write8_map,  0x800000, 0x80ffff, PicoWrite8_pico, 1);
  cpu68k_map_set(m68k_write16_map, 0x800000, 0x80ffff, PicoWrite16_pico, 1);
}