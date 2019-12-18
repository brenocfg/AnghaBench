#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_14__ {TYPE_2__* memory_map; } ;
struct TYPE_13__ {TYPE_3__* memory_map; } ;
struct TYPE_8__ {int boot; } ;
struct TYPE_12__ {int /*<<< orphan*/ * bram; int /*<<< orphan*/ * word_ram_2M; int /*<<< orphan*/ * word_ram; int /*<<< orphan*/ * prg_ram; int /*<<< orphan*/ * bootrom; TYPE_1__ cartridge; } ;
struct TYPE_11__ {int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct TYPE_10__ {int /*<<< orphan*/ * write16; int /*<<< orphan*/ * write8; int /*<<< orphan*/ * read16; int /*<<< orphan*/ * read8; int /*<<< orphan*/ * base; } ;
struct TYPE_9__ {int /*<<< orphan*/ * write16; int /*<<< orphan*/ * write8; int /*<<< orphan*/ * read16; int /*<<< orphan*/ * read8; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int /*<<< orphan*/ * bram_read_byte ; 
 int /*<<< orphan*/ * bram_read_word ; 
 int /*<<< orphan*/ * bram_write_byte ; 
 int /*<<< orphan*/ * bram_write_word ; 
 int /*<<< orphan*/  cd_cart_init () ; 
 int /*<<< orphan*/  cdc_init () ; 
 int /*<<< orphan*/  gfx_init () ; 
 TYPE_7__ m68k ; 
 int /*<<< orphan*/ * m68k_unused_16_w ; 
 int /*<<< orphan*/ * m68k_unused_8_w ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * prg_ram_write_byte ; 
 int /*<<< orphan*/ * prg_ram_write_word ; 
 TYPE_6__ s68k ; 
 int /*<<< orphan*/ * s68k_read_bus_16 ; 
 int /*<<< orphan*/ * s68k_read_bus_8 ; 
 int /*<<< orphan*/ * s68k_unused_16_w ; 
 int /*<<< orphan*/ * s68k_unused_8_w ; 
 TYPE_5__ scd ; 
 int /*<<< orphan*/ * scd_read_byte ; 
 int /*<<< orphan*/ * scd_read_word ; 
 int /*<<< orphan*/ * scd_write_byte ; 
 int /*<<< orphan*/ * scd_write_word ; 
 TYPE_4__* zbank_memory_map ; 
 int /*<<< orphan*/ * zbank_unused_w ; 

void scd_init(void)
{
  int i;
  
  /****************************************************************/
  /*  MAIN-CPU low memory map ($000000-$7FFFFF)                   */
  /****************************************************************/

  /* 0x00: boot from CD (Mode 2), 0x40: boot from cartridge (Mode 1) */
  uint8 base = scd.cartridge.boot;

  /* $400000-$7FFFFF (resp. $000000-$3FFFFF): cartridge area (4MB) */
  cd_cart_init();

  /* $000000-$1FFFFF (resp. $400000-$5FFFFF): CD memory area */
  for (i=base; i<base+0x20; i++)
  {
    if (i & 2)
    {
      /* $020000-$03FFFF (resp. $420000-$43FFFF): PRG-RAM (first 128KB bank, mirrored each 256KB) */
      m68k.memory_map[i].base    = scd.prg_ram + ((i & 1) << 16);
      m68k.memory_map[i].read8   = NULL;
      m68k.memory_map[i].read16  = NULL;
      m68k.memory_map[i].write8  = NULL;
      m68k.memory_map[i].write16 = NULL;
      zbank_memory_map[i].read   = NULL;
      zbank_memory_map[i].write  = NULL;

    }
    else
    {
      /* $000000-$01FFFF (resp. $400000-$41FFFF): internal ROM (128KB, mirrored each 256KB) */
      /* NB: Flux expects it to be mapped at $440000-$45FFFF */
      m68k.memory_map[i].base    = scd.bootrom + ((i & 1) << 16);
      m68k.memory_map[i].read8   = NULL;
      m68k.memory_map[i].read16  = NULL;
      m68k.memory_map[i].write8  = m68k_unused_8_w;
      m68k.memory_map[i].write16 = m68k_unused_16_w;
      zbank_memory_map[i].read   = NULL;
      zbank_memory_map[i].write  = zbank_unused_w;
    }
  }

  /* $200000-$3FFFFF (resp. $600000-$7FFFFF): Word-RAM in 2M mode (256KB mirrored) */
  for (i=base+0x20; i<base+0x40; i++)
  {
    m68k.memory_map[i].base    = scd.word_ram_2M + ((i & 3) << 16);
    m68k.memory_map[i].read8   = NULL;
    m68k.memory_map[i].read16  = NULL;
    m68k.memory_map[i].write8  = NULL;
    m68k.memory_map[i].write16 = NULL;
    zbank_memory_map[i].read   = NULL;
    zbank_memory_map[i].write  = NULL;
  }
  
  /****************************************************************/
  /*  SUB-CPU memory map ($000000-$FFFFFF)                        */
  /****************************************************************/

  /* $000000-$07FFFF: PRG-RAM (512KB) */
  for (i=0x00; i<0x08; i++)
  {
    s68k.memory_map[i].base    = scd.prg_ram + (i << 16);
    s68k.memory_map[i].read8   = NULL;
    s68k.memory_map[i].read16  = NULL;

    /* first 128KB is write-protected */
    s68k.memory_map[i].write8  = (i < 0x02) ? prg_ram_write_byte : NULL;
    s68k.memory_map[i].write16 = (i < 0x02) ? prg_ram_write_word : NULL;
  }

  /* $080000-$0BFFFF:  Word-RAM in 2M mode (256KB)*/
  for (i=0x08; i<0x0c; i++)
  {
    s68k.memory_map[i].base    = scd.word_ram_2M + ((i & 3) << 16);
    s68k.memory_map[i].read8   = NULL;
    s68k.memory_map[i].read16  = NULL;
    s68k.memory_map[i].write8  = NULL;
    s68k.memory_map[i].write16 = NULL;
  }
  
  /* $0C0000-$FD0000: Unused area (Word-RAM mirrored ?) */
  for (i=0x0c; i<0xfd; i++)
  {
    s68k.memory_map[i].base     = scd.word_ram_2M + ((i & 3) << 16);
    s68k.memory_map[i].read8    = s68k_read_bus_8;
    s68k.memory_map[i].read16   = s68k_read_bus_16;
    s68k.memory_map[i].write8   = s68k_unused_8_w;
    s68k.memory_map[i].write16  = s68k_unused_16_w;
  }

  /* $FD0000-$FF0000 (odd address only): 8KB backup RAM, mirrored(Wonder Mega / X'Eye BIOS access it at $FD0000-$FD1FFF) */
  for (i=0xfd; i<0xff; i++)
  {
    s68k.memory_map[i].base     = NULL;
    s68k.memory_map[i].read8    = bram_read_byte;
    s68k.memory_map[i].read16   = bram_read_word;
    s68k.memory_map[i].write8   = bram_write_byte;
    s68k.memory_map[i].write16  = bram_write_word;
  }

  /* $FF0000-$FFFFFF: PCM hardware & SUB-CPU registers  */
  s68k.memory_map[0xff].base     = NULL;
  s68k.memory_map[0xff].read8    = scd_read_byte;
  s68k.memory_map[0xff].read16   = scd_read_word;
  s68k.memory_map[0xff].write8   = scd_write_byte;
  s68k.memory_map[0xff].write16  = scd_write_word;

  /* Initialize CD hardware */
  cdc_init();
  gfx_init();

  /* Clear RAM */
  memset(scd.prg_ram, 0x00, sizeof(scd.prg_ram));
  memset(scd.word_ram, 0x00, sizeof(scd.word_ram));
  memset(scd.word_ram_2M, 0x00, sizeof(scd.word_ram_2M));
  memset(scd.bram, 0x00, sizeof(scd.bram));
}