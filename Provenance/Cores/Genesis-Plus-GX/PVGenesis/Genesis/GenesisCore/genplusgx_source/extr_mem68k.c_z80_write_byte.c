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
struct TYPE_2__ {int cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm_write (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gen_zbank_w (unsigned int) ; 
 TYPE_1__ m68k ; 
 int /*<<< orphan*/  m68k_lockup_w_8 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  m68k_unused_8_w (unsigned int,unsigned int) ; 
 unsigned int* zram ; 

void z80_write_byte(unsigned int address, unsigned int data)
{
  switch ((address >> 13) & 3)
  {
    case 2: /* YM2612 */
    {
      fm_write(m68k.cycles, address & 3, data);
      return;
    }

    case 3:
    {
      switch ((address >> 8) & 0x7F)
      {
        case 0x60:  /* Bank register */
        {
          gen_zbank_w(data & 1);
          return;
        }

        case 0x7F:  /* VDP */
        {
          m68k_lockup_w_8(address, data);
          return;
        }
      
        default:
        {
          m68k_unused_8_w(address, data);
          return;
        }
      }
    }
      
    default: /* ZRAM */
    {
      zram[address & 0x1FFF] = data;
      m68k.cycles += 8; /* ZRAM access latency (fixes Pacman 2: New Adventures) */
      return;
    }
  }
}