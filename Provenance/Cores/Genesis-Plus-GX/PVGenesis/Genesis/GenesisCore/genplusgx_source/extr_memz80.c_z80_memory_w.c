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
struct TYPE_8__ {int /*<<< orphan*/  cycles; } ;
struct TYPE_7__ {TYPE_1__* memory_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* write ) (unsigned int,unsigned char) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BYTE (int /*<<< orphan*/ ,unsigned int,unsigned char) ; 
 TYPE_4__ Z80 ; 
 int /*<<< orphan*/  fm_write (int /*<<< orphan*/ ,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  gen_zbank_w (unsigned char) ; 
 TYPE_3__ m68k ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned char) ; 
 int /*<<< orphan*/  stub2 (unsigned int,unsigned char) ; 
 int /*<<< orphan*/  z80_unused_w (unsigned int,unsigned char) ; 
 unsigned int zbank ; 
 TYPE_2__* zbank_memory_map ; 
 unsigned char* zram ; 

void z80_memory_w(unsigned int address, unsigned char data)
{
  switch((address >> 13) & 7)
  {
    case 0: /* $0000-$3FFF: Z80 RAM (8K mirrored) */
    case 1: 
    {
      zram[address & 0x1FFF] = data;
      return;
    }

    case 2: /* $4000-$5FFF: YM2612 */
    {
      fm_write(Z80.cycles, address & 3, data);
      return;
    }

    case 3: /* Bank register and VDP */
    {
      switch(address >> 8)
      {
        case 0x60: /* $6000-$60FF: Bank register */
        {
          gen_zbank_w(data & 1);
          return;
        }

        case 0x7F: /* $7F00-$7FFF: VDP */
        {
          (*zbank_memory_map[0xc0].write)(address, data);
          return;
        }

        default:
        {
          z80_unused_w(address, data);
          return;
        }
      }
    }

    default: /* $8000-$FFFF: 68k bank (32K) */
    {
      address = zbank | (address & 0x7FFF);
      if (zbank_memory_map[address >> 16].write)
      {
        (*zbank_memory_map[address >> 16].write)(address, data);
        return;
      }
      WRITE_BYTE(m68k.memory_map[address >> 16].base, address & 0xFFFF, data);
      return;
    }
  }
}