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
typedef  int uint8 ;
struct TYPE_8__ {int pages; int /*<<< orphan*/  mapper; scalar_t__ fcr; } ;
struct TYPE_7__ {int romsize; scalar_t__ rom; } ;
struct TYPE_6__ {int pages; int /*<<< orphan*/  mapper; scalar_t__ fcr; } ;
struct TYPE_5__ {int pages; int /*<<< orphan*/  mapper; scalar_t__ fcr; scalar_t__ rom; } ;

/* Variables and functions */
 TYPE_4__ bios_rom ; 
 TYPE_3__ cart ; 
 TYPE_2__ cart_rom ; 
 int /*<<< orphan*/  mapper_reset () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 TYPE_1__ slot ; 
 scalar_t__* z80_readmap ; 

void sms_cart_switch(uint8 mode)
{
  /* by default, disable cartridge & BIOS ROM */
  slot.pages = 0;

  /* cartridge ROM enabled ? */
  if (mode & 0x40)
  {
    /* check if cartridge is loaded */
    if (cart_rom.pages)
    {
      /* map cartridge ROM */
      slot.rom = cart.rom;
      slot.fcr = cart_rom.fcr;
      slot.mapper = cart_rom.mapper;
      slot.pages = cart_rom.pages;
    }
  }
  else
  {
    /* BIOS ROM enabled ? */
    if (mode & 0x08)
    {
      /* check if BIOS ROM is larger than 1K */
      if (bios_rom.pages > 1)
      {
        /* map BIOS ROM */
        slot.rom = cart.rom + 0x400000;
        slot.fcr = bios_rom.fcr;
        slot.mapper = bios_rom.mapper;
        slot.pages = bios_rom.pages;
      }
      else
      {
        /* by default, map cartridge ROM */
        slot.rom = cart.rom;
        slot.fcr = cart_rom.fcr;
        slot.mapper = cart_rom.mapper;
        slot.pages = cart_rom.pages;
      }
    }

    /* assume only BIOS would disable cartridge slot */
    if (!bios_rom.pages)
    {
      /* max. BIOS ROM size supported is 1MB */
      if (cart.romsize <= 0x100000)
      {
        /* copy to BIOS ROM */
        memcpy(cart.rom + 0x400000, cart.rom, cart.romsize);
        memcpy(bios_rom.fcr, cart_rom.fcr, 4);
        bios_rom.mapper = cart_rom.mapper;
        bios_rom.pages = cart_rom.pages;

        /* unload cartridge  */
        cart_rom.pages = 0;
      }
    }
  }

  /* reset Z80 memory map */
  mapper_reset();

  /* 1k BIOS special case (Majesco GG) */
  if ((bios_rom.pages == 1) && ((mode & 0x48) == 0x08))
  {
    /* BIOS ROM is mapped to $0000-$03FF */
    z80_readmap[0] = cart.rom + 0x400000;
  }
}