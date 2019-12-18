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
struct TYPE_8__ {int /*<<< orphan*/  rom; } ;
struct TYPE_7__ {unsigned int* regs; int* addr; int* data; int /*<<< orphan*/  rom; } ;
struct TYPE_6__ {TYPE_1__* memory_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  write16; int /*<<< orphan*/  write8; int /*<<< orphan*/ * read16; int /*<<< orphan*/ * read8; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_4__ cart ; 
 TYPE_3__ ggenie ; 
 int /*<<< orphan*/ * ggenie_read_byte ; 
 int /*<<< orphan*/ * ggenie_read_word ; 
 int /*<<< orphan*/  ggenie_switch (int) ; 
 int /*<<< orphan*/  ggenie_write_byte ; 
 int /*<<< orphan*/  ggenie_write_word ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  m68k_unused_16_w ; 
 int /*<<< orphan*/  m68k_unused_8_w ; 

__attribute__((used)) static void ggenie_write_regs(unsigned int offset, unsigned int data)
{
  /* update internal register */
  ggenie.regs[offset] = data;

  /* Mode Register */
  if (offset == 0)
  {
    /* MODE bit */
    if (data & 0x400)
    {
      /* $0000-$7ffff reads mapped to Cartridge ROM */
      m68k.memory_map[0].base = cart.rom;
      m68k.memory_map[0].read8 = NULL; 
      m68k.memory_map[0].read16 = NULL; 
    }
    else
    {
      /* $0000-$7ffff reads mapped to Game Genie ROM */
      m68k.memory_map[0].base = ggenie.rom;
      m68k.memory_map[0].read8 = NULL; 
      m68k.memory_map[0].read16 = NULL; 

      /* READ_ENABLE bit */
      if (data & 0x200)
      {
        /* $0000-$7ffff reads mapped to Game Genie Registers */
        /* code doing this should execute in RAM so we don't need to modify base address */
        m68k.memory_map[0].read8 = ggenie_read_byte; 
        m68k.memory_map[0].read16 = ggenie_read_word; 
      }
    }

    /* LOCK bit */
    if (data & 0x100)
    {
      /* decode patch address (ROM area only)*/
      /* note: Charles's doc is wrong, first register holds bits 23-16 of patch address */
      ggenie.addr[0] = ((ggenie.regs[2]   & 0x3f) << 16) | ggenie.regs[3];
      ggenie.addr[1] = ((ggenie.regs[5]   & 0x3f) << 16) | ggenie.regs[6];
      ggenie.addr[2] = ((ggenie.regs[8]   & 0x3f) << 16) | ggenie.regs[9];
      ggenie.addr[3] = ((ggenie.regs[11]  & 0x3f) << 16) | ggenie.regs[12];
      ggenie.addr[4] = ((ggenie.regs[14]  & 0x3f) << 16) | ggenie.regs[15];
      ggenie.addr[5] = ((ggenie.regs[17]  & 0x3f) << 16) | ggenie.regs[18];

      /* decode patch data */
      ggenie.data[0] = ggenie.regs[4];
      ggenie.data[1] = ggenie.regs[7];
      ggenie.data[2] = ggenie.regs[10];
      ggenie.data[3] = ggenie.regs[13];
      ggenie.data[4] = ggenie.regs[16];
      ggenie.data[5] = ggenie.regs[19];

      /* disable internal registers */
      m68k.memory_map[0].write8   = m68k_unused_8_w;
      m68k.memory_map[0].write16  = m68k_unused_16_w;

      /* patch ROM when GG program exits (LOCK bit set) */
      /* this is done here to handle patched program reads faster & more easily */
      /* on real HW, address decoding would be done on each reads */
      ggenie_switch(1);
    }
    else
    {
      m68k.memory_map[0].write8   = ggenie_write_byte;
      m68k.memory_map[0].write16  = ggenie_write_word;
    }
  }

  /* RESET register */
  else if (offset == 1)
  {
    ggenie.regs[1] |= 1;
  }
}