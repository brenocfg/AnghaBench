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
struct TYPE_6__ {int* regs; } ;
struct TYPE_8__ {TYPE_2__ hw; int /*<<< orphan*/ * rom; } ;
struct TYPE_7__ {TYPE_1__* memory_map; } ;
struct TYPE_5__ {int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 TYPE_4__ cart ; 
 TYPE_3__ m68k ; 

__attribute__((used)) static void mapper_realtec_w(uint32 address, uint32 data)
{
  switch (address)
  {
    case 0x402000:  
    {
      /* number of mapped 64k blocks (the written value is a number of 128k blocks) */
      cart.hw.regs[2] = data << 1;
      return;
    }

    case 0x404000:
    {
      /* 00000xxx */
      cart.hw.regs[0] = data & 7;
      return;
    }

    case 0x400000:  
    {
      /* 00000yy1 */
      cart.hw.regs[1] = data & 6;

      /* ensure mapped size is not null */
      if (cart.hw.regs[2])
      {
        /* mapped start address is 00yy xxx0 0000 0000 0000 0000 */
        uint32 base = (cart.hw.regs[0] << 1) | (cart.hw.regs[1] << 3);

        /* selected blocks are mirrored into the whole cartridge area */
        int i;
        for (i=0x00; i<0x40; i++)
        {
          m68k.memory_map[i].base = &cart.rom[(base + (i % cart.hw.regs[2])) << 16];
        }
      }
      return;
    }
  }
}