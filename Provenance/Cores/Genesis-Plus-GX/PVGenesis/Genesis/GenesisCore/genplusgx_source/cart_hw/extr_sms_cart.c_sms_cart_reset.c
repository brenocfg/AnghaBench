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
struct TYPE_8__ {int* fcr; int pages; int mapper; } ;
struct TYPE_7__ {scalar_t__ rom; } ;
struct TYPE_6__ {int mapper; int* fcr; int pages; } ;
struct TYPE_5__ {int* fcr; int mapper; int pages; scalar_t__ rom; } ;

/* Variables and functions */
#define  MAPPER_KOREA_8K 132 
#define  MAPPER_MSX 131 
#define  MAPPER_MSX_NEMESIS 130 
#define  MAPPER_SEGA 129 
#define  MAPPER_SEGA_X 128 
 int SYSTEM_SMS ; 
 TYPE_4__ bios_rom ; 
 TYPE_3__ cart ; 
 TYPE_2__ cart_rom ; 
 int* io_reg ; 
 int /*<<< orphan*/  mapper_reset () ; 
 TYPE_1__ slot ; 
 int system_hw ; 
 int* work_ram ; 
 scalar_t__* z80_readmap ; 

void sms_cart_reset(void)
{
  /* reset BIOS ROM paging (SEGA mapper by default) */
  bios_rom.fcr[0] = 0;
  bios_rom.fcr[1] = 0;
  bios_rom.fcr[2] = 1;
  bios_rom.fcr[3] = 2;

  /* reset cartridge ROM paging */
  switch (cart_rom.mapper)
  {
    case MAPPER_SEGA:
    case MAPPER_SEGA_X:
      cart_rom.fcr[0] = 0;
      cart_rom.fcr[1] = 0;
      cart_rom.fcr[2] = 1;
      cart_rom.fcr[3] = 2;
      break;

    case MAPPER_KOREA_8K:
    case MAPPER_MSX:
    case MAPPER_MSX_NEMESIS:
      cart_rom.fcr[0] = 0;
      cart_rom.fcr[1] = 0;
      cart_rom.fcr[2] = 0;
      cart_rom.fcr[3] = 0;
      break;

    default:
      cart_rom.fcr[0] = 0;
      cart_rom.fcr[1] = 0;
      cart_rom.fcr[2] = 1;
      cart_rom.fcr[3] = 0;
      break;
  }

  /* check if BIOS is larger than 1k */
  if (bios_rom.pages > 1)
  {
    /* enable BIOS ROM */
    slot.rom = cart.rom + 0x400000;
    slot.fcr = bios_rom.fcr;
    slot.mapper = bios_rom.mapper;
    slot.pages = bios_rom.pages;
  }
  else
  {
    /* enable cartridge ROM */
    slot.rom = cart.rom;
    slot.fcr = cart_rom.fcr;
    slot.mapper = cart_rom.mapper;
    slot.pages = cart_rom.pages;

    /* force Memory Control register value in RAM (usually set by Master System BIOS) */
    if (system_hw & SYSTEM_SMS)
    {
      work_ram[0] = 0xA8;
    }
  }

  /* reset Memory Control register (RAM & I/O are enabled, either BIOS or Cartridge ROM are enabled) */
  io_reg[0x0E] = bios_rom.pages ? 0xE0 : 0xA8;

  /* reset Z80 memory map */
  mapper_reset();

  /* 1k BIOS special case (Majesco GG) */
  if (bios_rom.pages == 1)
  {
    /* BIOS ROM is mapped to $0000-$03FF */
    z80_readmap[0] = cart.rom + 0x400000;
  }
}