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
struct TYPE_6__ {unsigned int cycles; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  write16; int /*<<< orphan*/  write8; int /*<<< orphan*/  read16; int /*<<< orphan*/  read8; } ;

/* Variables and functions */
 TYPE_3__ Z80 ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  m68k_read_bus_16 ; 
 int /*<<< orphan*/  m68k_read_bus_8 ; 
 int /*<<< orphan*/  m68k_unused_16_w ; 
 int /*<<< orphan*/  m68k_unused_8_w ; 
 int /*<<< orphan*/  z80_read_byte ; 
 int /*<<< orphan*/  z80_read_word ; 
 int /*<<< orphan*/  z80_run (unsigned int) ; 
 int /*<<< orphan*/  z80_write_byte ; 
 int /*<<< orphan*/  z80_write_word ; 
 int zstate ; 

void gen_zbusreq_w(unsigned int data, unsigned int cycles)
{
  if (data)  /* !ZBUSREQ asserted */
  {
    /* check if Z80 is going to be stopped */
    if (zstate == 1)
    {
      /* resynchronize with 68k */ 
      z80_run(cycles);

      /* enable 68k access to Z80 bus */
      m68k.memory_map[0xa0].read8   = z80_read_byte;
      m68k.memory_map[0xa0].read16  = z80_read_word;
      m68k.memory_map[0xa0].write8  = z80_write_byte;
      m68k.memory_map[0xa0].write16 = z80_write_word;
    }

    /* update Z80 bus status */
    zstate |= 2;
  }
  else  /* !ZBUSREQ released */
  {
    /* check if Z80 is going to be restarted */
    if (zstate == 3)
    {
      /* resynchronize with 68k */
      Z80.cycles = cycles;

      /* disable 68k access to Z80 bus */
      m68k.memory_map[0xa0].read8   = m68k_read_bus_8;
      m68k.memory_map[0xa0].read16  = m68k_read_bus_16;
      m68k.memory_map[0xa0].write8  = m68k_unused_8_w;
      m68k.memory_map[0xa0].write16 = m68k_unused_16_w;
    }

    /* update Z80 bus status */
    zstate &= 1;
  }
}