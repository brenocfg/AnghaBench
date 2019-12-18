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
struct TYPE_2__ {int romsize; } ;

/* Variables and functions */
 int M68K_BANK_MASK ; 
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  PicoRead16_sprot ; 
 int /*<<< orphan*/  PicoRead8_sprot ; 
 int /*<<< orphan*/  PicoWrite16_sprot ; 
 int /*<<< orphan*/  PicoWrite8_sprot ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write8_map ; 

__attribute__((used)) static void carthw_sprot_mem_setup(void)
{
  int start;

  // map ROM - 0x7fffff, /TIME areas (which are tipically used)
  start = (Pico.romsize + M68K_BANK_MASK) & ~M68K_BANK_MASK;
  cpu68k_map_set(m68k_read8_map,   start, 0x7fffff, PicoRead8_sprot, 1);
  cpu68k_map_set(m68k_read16_map,  start, 0x7fffff, PicoRead16_sprot, 1);
  cpu68k_map_set(m68k_write8_map,  start, 0x7fffff, PicoWrite8_sprot, 1);
  cpu68k_map_set(m68k_write16_map, start, 0x7fffff, PicoWrite16_sprot, 1);

  cpu68k_map_set(m68k_read8_map,   0xa10000, 0xa1ffff, PicoRead8_sprot, 1);
  cpu68k_map_set(m68k_read16_map,  0xa10000, 0xa1ffff, PicoRead16_sprot, 1);
  cpu68k_map_set(m68k_write8_map,  0xa10000, 0xa1ffff, PicoWrite8_sprot, 1);
  cpu68k_map_set(m68k_write16_map, 0xa10000, 0xa1ffff, PicoWrite16_sprot, 1);
}