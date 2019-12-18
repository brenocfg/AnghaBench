#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_12__ {int special; int mask; scalar_t__ rom; } ;
struct TYPE_11__ {scalar_t__ lock_on; } ;
struct TYPE_10__ {TYPE_1__* memory_map; } ;
struct TYPE_9__ {scalar_t__ sram; scalar_t__ on; } ;
struct TYPE_8__ {void* write; int /*<<< orphan*/ * read; } ;
struct TYPE_7__ {void* write16; void* write8; int /*<<< orphan*/ * read16; int /*<<< orphan*/ * read8; scalar_t__ base; } ;

/* Variables and functions */
 int HW_LOCK_ON ; 
 scalar_t__ TYPE_SK ; 
 TYPE_6__ cart ; 
 TYPE_5__ config ; 
 TYPE_4__ m68k ; 
 void* m68k_unused_16_w ; 
 void* m68k_unused_8_w ; 
 TYPE_3__ sram ; 
 void* sram_read_byte ; 
 int /*<<< orphan*/ * sram_read_word ; 
 void* sram_write_byte ; 
 void* sram_write_word ; 
 TYPE_2__* zbank_memory_map ; 
 void* zbank_unused_w ; 

__attribute__((used)) static void mapper_sega_w(uint32 data)
{
  int i;

  if (data & 1)
  {
    if (sram.on)
    {
      /* Backup RAM mapped to $200000-$20ffff (normally mirrored up to $3fffff but this breaks Sonic Megamix and no game need it) */
      m68k.memory_map[0x20].base    = sram.sram;
      m68k.memory_map[0x20].read8   = sram_read_byte;
      m68k.memory_map[0x20].read16  = sram_read_word;
      zbank_memory_map[0x20].read   = sram_read_byte;

      /* Backup RAM write protection */
      if (data & 2)
      {
        m68k.memory_map[0x20].write8  = m68k_unused_8_w;
        m68k.memory_map[0x20].write16 = m68k_unused_16_w;
        zbank_memory_map[0x20].write  = zbank_unused_w;
      }
      else
      {
        m68k.memory_map[0x20].write8  = sram_write_byte;
        m68k.memory_map[0x20].write16 = sram_write_word;
        zbank_memory_map[0x20].write  = sram_write_byte;
      }
    }

    /* S&K lock-on chip */
    if ((cart.special & HW_LOCK_ON) && (config.lock_on == TYPE_SK))
    {
      /* S2K upmem chip mapped to $300000-$3fffff (256K mirrored) */
      for (i=0x30; i<0x40; i++)
      {
        m68k.memory_map[i].base = (cart.rom + 0x900000) + ((i & 3) << 16);
      }
    }
  }
  else
  {
    /* cartridge ROM mapped to $200000-$3fffff */
    for (i=0x20; i<0x40; i++)
    {
      m68k.memory_map[i].base     = cart.rom + ((i<<16) & cart.mask);
      m68k.memory_map[i].read8    = NULL;
      m68k.memory_map[i].read16   = NULL;
      zbank_memory_map[i].read    = NULL;
      m68k.memory_map[i].write8   = m68k_unused_8_w;
      m68k.memory_map[i].write16  = m68k_unused_16_w;
      zbank_memory_map[i].write   = zbank_unused_w;
    }
  }
}