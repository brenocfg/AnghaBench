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
struct TYPE_6__ {int /*<<< orphan*/ * rom; } ;
struct TYPE_5__ {scalar_t__ mapper; } ;
struct TYPE_4__ {int pages; int mapper; int /*<<< orphan*/ * fcr; int /*<<< orphan*/ * rom; } ;

/* Variables and functions */
#define  MAPPER_93C46 139 
#define  MAPPER_CODIES 138 
#define  MAPPER_KOREA 137 
#define  MAPPER_KOREA_16K 136 
#define  MAPPER_KOREA_8K 135 
#define  MAPPER_MSX 134 
#define  MAPPER_MSX_NEMESIS 133 
#define  MAPPER_MULTI 132 
#define  MAPPER_NONE 131 
#define  MAPPER_RAM_8K_EXT1 130 
#define  MAPPER_RAM_8K_EXT2 129 
 int MAPPER_SEGA ; 
#define  MAPPER_TEREBI 128 
 scalar_t__ SYSTEM_SG ; 
 TYPE_3__ cart ; 
 TYPE_2__ cart_rom ; 
 int /*<<< orphan*/  mapper_16k_w (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapper_8k_w (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_mapper_93c46 ; 
 int /*<<< orphan*/  read_mapper_default ; 
 int /*<<< orphan*/  read_mapper_korea_8k ; 
 int /*<<< orphan*/  read_mapper_terebi ; 
 TYPE_1__ slot ; 
 scalar_t__ system_hw ; 
 int /*<<< orphan*/ * work_ram ; 
 int /*<<< orphan*/  write_mapper_93c46 ; 
 int /*<<< orphan*/  write_mapper_codies ; 
 int /*<<< orphan*/  write_mapper_korea ; 
 int /*<<< orphan*/  write_mapper_korea_16k ; 
 int /*<<< orphan*/  write_mapper_korea_8k ; 
 int /*<<< orphan*/  write_mapper_msx ; 
 int /*<<< orphan*/  write_mapper_multi ; 
 int /*<<< orphan*/  write_mapper_none ; 
 int /*<<< orphan*/  write_mapper_sega ; 
 int /*<<< orphan*/  write_mapper_terebi ; 
 int /*<<< orphan*/ ** z80_readmap ; 
 int /*<<< orphan*/  z80_readmem ; 
 int /*<<< orphan*/ ** z80_writemap ; 
 int /*<<< orphan*/  z80_writemem ; 

__attribute__((used)) static void mapper_reset(void)
{
  int i;

  /* reset internal RAM mapping */
  if (system_hw == SYSTEM_SG)
  {
    /* 8k RAM extension adapter (type B) */
    if (cart_rom.mapper == MAPPER_RAM_8K_EXT2)
    {
      /* $C000-$FFFF mapped to 8k external RAM (mirrored) */
      for (i = 0x30; i < 0x40; i++)
      {
        z80_readmap[i] = z80_writemap[i] = &work_ram[(i & 0x07) << 10];
      }
    }
    else
    {
      /* $C000-$FFFF mapped to 2k mirrored RAM */
      for (i = 0x30; i < 0x40; i++)
      {
        z80_readmap[i] = z80_writemap[i] = &work_ram[(i & 0x01) << 10];
      }
    }
  }
  else
  {
    /* $C000-$FFFF mapped to 8k internal RAM (mirrored) */
    for (i = 0x30; i < 0x40; i++)
    {
      z80_readmap[i] = z80_writemap[i] = &work_ram[(i & 0x07) << 10];
    }
  }

  /* check if ROM is disabled */
  if (!slot.pages)
  {
    /* $0000-$BFFF mapped to unused cartridge areas */
    for(i = 0x00; i < 0x30; i++)
    {
      z80_writemap[i] = cart.rom + 0x510000;
      z80_readmap[i]  = cart.rom + 0x510400;
    }

    /* set default Z80 memory handlers */
    z80_readmem = read_mapper_default;
    z80_writemem = write_mapper_none;
    return;
  }

  /* reset default $0000-$BFFF mapping */
  if (slot.mapper < MAPPER_SEGA)
  {
    /* $0000-$BFFF mapped to ROM (48k) */
    for (i = 0x00; i < 0x30; i++)
    {
      z80_readmap[i] = &slot.rom[i << 10];
      z80_writemap[i] = cart.rom + 0x510000; /* unused area */
    }

    /* cartridge extra RAM enabled by default with 32K ROM */
    if (slot.pages <= 0x20)
    {
      /* $8000-$BFFF mapped to 8k external RAM (mirrored) */
      for (i = 0x20; i < 0x30; i++)
      {
        z80_readmap[i] = z80_writemap[i] = &work_ram[0x2000 + ((i & 0x07) << 10)];
      }
    }

    /* 8k RAM extension adapter (type A) */
    if (slot.mapper == MAPPER_RAM_8K_EXT1)
    {
      /* $2000-$3FFF mapped to 8k external RAM */
      for (i = 0x08; i < 0x10; i++)
      {
        z80_readmap[i] = z80_writemap[i] = &work_ram[0x2000 + ((i & 0x07) << 10)];
      }
    }
  }
  else
  {
    /* $0000-$BFFF mapped to ROM by default */
    for (i = 0x00; i < 0x30; i++)
    {
      z80_readmap[i] = &slot.rom[i << 10];
      z80_writemap[i] = cart.rom + 0x510000; /* unused area */
    }

    /* reset default ROM paging */
    if (slot.mapper & MAPPER_KOREA_8K)
    {
      mapper_8k_w(0,slot.fcr[0]);
      mapper_8k_w(1,slot.fcr[1]);
      mapper_8k_w(2,slot.fcr[2]);
      mapper_8k_w(3,slot.fcr[3]);

      /* Nemesis special case */
      if (slot.mapper == MAPPER_MSX_NEMESIS)
      {
        /* first 8k page is mapped to last 8k ROM bank */
        for (i = 0x00; i < 0x08; i++)
        {
          z80_readmap[i] = &slot.rom[(0x0f << 13) | ((i & 0x07) << 10)];
        }
      }
    }
    else
    {
      mapper_16k_w(0,slot.fcr[0]);
      mapper_16k_w(1,slot.fcr[1]);
      mapper_16k_w(2,slot.fcr[2]);
      mapper_16k_w(3,slot.fcr[3]);
    }
  }

  /* reset Z80 memory handlers */
  switch (slot.mapper)
  {
    case MAPPER_NONE:
    case MAPPER_RAM_8K_EXT1:
    case MAPPER_RAM_8K_EXT2:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_none;
      break;

    case MAPPER_CODIES:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_codies;
      break;

    case MAPPER_KOREA:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_korea;
      break;

    case MAPPER_KOREA_8K:
      z80_readmem = read_mapper_korea_8k;
      z80_writemem = write_mapper_korea_8k;
      break;

    case MAPPER_KOREA_16K:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_korea_16k;
      break;

    case MAPPER_MSX:
    case MAPPER_MSX_NEMESIS:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_msx;
      break;

    case MAPPER_MULTI:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_multi;
      break;

    case MAPPER_93C46:
      z80_readmem = read_mapper_93c46;
      z80_writemem = write_mapper_93c46;
      break;

    case MAPPER_TEREBI:
      z80_readmem = read_mapper_terebi;
      z80_writemem = write_mapper_terebi;
      break;

    default:
      z80_readmem = read_mapper_default;
      z80_writemem = write_mapper_sega;
      break;
  }
}