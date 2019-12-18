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
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  rom; } ;
struct TYPE_7__ {TYPE_1__* memory_map; } ;
struct TYPE_6__ {int* sram; } ;
struct TYPE_5__ {int base; } ;

/* Variables and functions */
 TYPE_4__ cart ; 
 TYPE_3__ m68k ; 
 int /*<<< orphan*/  m68k_unused_8_w (int,int) ; 
 TYPE_2__ sram ; 

__attribute__((used)) static void mapper_smw_64_w(uint32 address, uint32 data)
{
  /* internal registers (saved to backup RAM) */
  switch ((address >> 16) & 0x07)
  {
    case 0x00:  /* $60xxxx */
    {
      if (address & 2)
      {
        /* $600003 data write mode ? */
        switch (sram.sram[0x00] & 0x07)
        {
          case 0x00:
          {
            /* update value returned at $660001-$660003 */
            sram.sram[0x06] = ((sram.sram[0x06] ^ sram.sram[0x01]) ^ data) & 0xFE;
            break;
          }

          case 0x01:
          {
            /* update value returned at $660005-$660007 */
            sram.sram[0x07] = data & 0xFE;
            break;
          }

          case 0x07:
          {
            /* update selected ROM bank (upper 512K) mapped at $610000-$61ffff */
            m68k.memory_map[0x61].base = m68k.memory_map[0x69].base = cart.rom + 0x080000 + ((data & 0x1c) << 14);
            break;
          }

          default:
          {
            /* unknown mode */
            break;
          }
        }

        /* $600003 data register */
        sram.sram[0x01] = data;
      }
      else
      {
        /* $600001 ctrl register */
        sram.sram[0x00] = data;
      }
      return;
    }

    case 0x01:  /* $61xxxx */
    {
      if (address & 2)
      {
        /* $610003 ctrl register */
        sram.sram[0x02] = data;
      }
      return;
    }

    case 0x04:  /* $64xxxx */
    {
      if (address & 2)
      {
        /* $640003 data register */
        sram.sram[0x04] = data;
      }
      else
      {
        /* $640001 data register */
        sram.sram[0x03] = data;
      }
      return;
    }

    case 0x06:  /* $66xxxx */
    {
      /* unknown */
      return;
    }

    case 0x07:  /* $67xxxx */
    {
      if (!(address & 2))
      {
        /* $670001 ctrl register */
        sram.sram[0x05] = data;

        /* upper 512K ROM bank-switching enabled ? */
        if (sram.sram[0x02] & 0x80)
        {
          /* update selected ROM bank (upper 512K) mapped at $600000-$60ffff */
          m68k.memory_map[0x60].base = m68k.memory_map[0x68].base = cart.rom + 0x080000 + ((data & 0x1c) << 14);
        }
      }
      return;
    }

    default:  /* not used */
    {
      m68k_unused_8_w(address, data);
      return;
    }
  }
}