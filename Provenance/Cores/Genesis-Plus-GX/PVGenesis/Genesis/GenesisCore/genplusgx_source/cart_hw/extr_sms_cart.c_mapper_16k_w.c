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
typedef  int uint8 ;
struct TYPE_6__ {int /*<<< orphan*/  rom; } ;
struct TYPE_5__ {unsigned int pages; int* fcr; scalar_t__ mapper; int /*<<< orphan*/ * rom; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sram; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEATS_UPDATE () ; 
 scalar_t__ MAPPER_CODIES ; 
 scalar_t__ MAPPER_MULTI ; 
 scalar_t__ MAPPER_SEGA ; 
 TYPE_3__ cart ; 
 TYPE_2__ slot ; 
 TYPE_1__ sram ; 
 int /*<<< orphan*/ * work_ram ; 
 int /*<<< orphan*/ ** z80_readmap ; 
 int /*<<< orphan*/ ** z80_writemap ; 

__attribute__((used)) static void mapper_16k_w(int offset, unsigned int data)
{
  int i;

  /* cartridge ROM page (16k) */
  uint8 page = data % slot.pages;

  /* page index increment (SEGA mapper only) */
  if ((slot.fcr[0] & 0x03) && (slot.mapper == MAPPER_SEGA))
  {
    page = (page + ((4 - (slot.fcr[0] & 0x03)) << 3)) % slot.pages;
  }

  /* save frame control register data */
  slot.fcr[offset] = data;

  switch (offset)
  {
    case 0: /* control register (SEGA mapper only) */
    {
      if (data & 0x08)
      {
        /* external RAM (upper or lower 16K) mapped at $8000-$BFFF */
        for (i = 0x20; i < 0x30; i++)
        {
          z80_readmap[i] = z80_writemap[i] = &sram.sram[((data & 0x04) << 12) + ((i & 0x0F) << 10)];
        }
      }
      else
      {
        /* cartridge ROM page (16k) */
        page = slot.fcr[3] % slot.pages;
        
        /* page index increment (SEGA mapper) */
        if ((data & 0x03) && (slot.mapper == MAPPER_SEGA))
        {
          page = (page + ((4 - (data & 0x03)) << 3)) % slot.pages;
        }

        /* cartridge ROM mapped at $8000-$BFFF */
        for (i = 0x20; i < 0x30; i++)
        {
          z80_readmap[i] = &slot.rom[(page << 14) | ((i & 0x0F) << 10)];
          z80_writemap[i] = cart.rom + 0x510000; /* unused area */
        }
      }

      if (data & 0x10)
      {
        /* external RAM (lower 16K) mapped at $C000-$FFFF */
        for (i = 0x30; i < 0x40; i++)
        {
          z80_readmap[i] = z80_writemap[i] = &sram.sram[(i & 0x0F) << 10];
        }
      }
      else
      {
        /* internal RAM (8K mirrorred) mapped at $C000-$FFFF */
        for (i = 0x30; i < 0x40; i++)
        {
          z80_readmap[i] = z80_writemap[i] = &work_ram[(i & 0x07) << 10];
        }
      }
      break;
    }

    case 1: /* cartridge ROM bank (16k) at $0000-$3FFF */
    {
      /* first 1k is not fixed (CODEMASTER or MULTI mappers only) */
      if ((slot.mapper == MAPPER_CODIES) || (slot.mapper == MAPPER_MULTI))
      {
        z80_readmap[0] = &slot.rom[(page << 14)];
      }

      for (i = 0x01; i < 0x10; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 14) | ((i & 0x0F) << 10)];
      }
      break;
    }

    case 2: /* cartridge ROM bank (16k) at $4000-$7FFF */
    {
      for (i = 0x10; i < 0x20; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 14) | ((i & 0x0F) << 10)];
      }

      /* cartridge RAM switch (CODEMASTER mapper only, see Ernie Elf's Golf) */
      if (slot.mapper == MAPPER_CODIES)
      {
        if (data & 0x80)
        {
          /* external RAM (8k) mapped at $A000-$BFFF */
          for (i = 0x28; i < 0x30; i++)
          {
            z80_readmap[i] = z80_writemap[i] = &sram.sram[(i & 0x0F) << 10];
          }
        }
        else
        {
          /* cartridge ROM page (16k) */
          page = slot.fcr[3] % slot.pages;

          /* cartridge ROM mapped at $A000-$BFFF */
          for (i = 0x28; i < 0x30; i++)
          {
            z80_readmap[i] = &slot.rom[(page << 14) | ((i & 0x0F) << 10)];
            z80_writemap[i] = cart.rom + 0x510000; /* unused area */
          }
        }
      }
      break;
    }

    case 3: /* cartridge ROM bank (16k) at $8000-$BFFF */
    {
      /* check that external RAM (16k) is not mapped at $8000-$BFFF (SEGA mapper only) */
      if ((slot.fcr[0] & 0x08)) break;

      /* first 8k */
      for (i = 0x20; i < 0x28; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 14) | ((i & 0x0F) << 10)];
      }

      /* check that cartridge RAM (8k) is not mapped at $A000-$BFFF (CODEMASTER mapper only) */
      if ((slot.mapper == MAPPER_CODIES) && (slot.fcr[2] & 0x80)) break;

      /* last 8k */
      for (i = 0x28; i < 0x30; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 14) | ((i & 0x0F) << 10)];
      }
      break;
    }
  }

#ifdef CHEATS_UPDATE
  /* update ROM patches when banking has changed */
  CHEATS_UPDATE();
#endif
}