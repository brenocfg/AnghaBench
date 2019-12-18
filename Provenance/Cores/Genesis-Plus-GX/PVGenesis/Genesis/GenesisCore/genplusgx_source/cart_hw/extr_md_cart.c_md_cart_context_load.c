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
typedef  int /*<<< orphan*/  ssp1601_t ;
struct TYPE_9__ {int /*<<< orphan*/ * regs; } ;
struct TYPE_14__ {scalar_t__ rom; TYPE_2__ hw; } ;
struct TYPE_13__ {TYPE_1__* memory_map; } ;
struct TYPE_12__ {scalar_t__ sram; } ;
struct TYPE_11__ {int /*<<< orphan*/  ssp1601; int /*<<< orphan*/ * dram; int /*<<< orphan*/ * iram_rom; } ;
struct TYPE_10__ {void* write; int /*<<< orphan*/ * read; } ;
struct TYPE_8__ {scalar_t__ base; int /*<<< orphan*/  write16; void* write8; int /*<<< orphan*/ * read16; int /*<<< orphan*/ * read8; } ;

/* Variables and functions */
 TYPE_7__ cart ; 
 int /*<<< orphan*/  load_param (int /*<<< orphan*/ *,int) ; 
 TYPE_6__ m68k ; 
 int /*<<< orphan*/  m68k_unused_16_w ; 
 void* m68k_unused_8_w ; 
 TYPE_5__ sram ; 
 void* sram_read_byte ; 
 int /*<<< orphan*/ * sram_read_word ; 
 void* sram_write_byte ; 
 int /*<<< orphan*/  sram_write_word ; 
 TYPE_4__* svp ; 
 TYPE_3__* zbank_memory_map ; 
 void* zbank_unused_w ; 

int md_cart_context_load(uint8 *state)
{
  int i;
  int bufferptr = 0;
  uint8 offset;

  /* cartridge mapping */
  for (i=0; i<0x40; i++)
  {
    /* get offset */
    offset = state[bufferptr++];

    if (offset == 0xff)
    {
      /* SRAM */
      m68k.memory_map[i].base     = sram.sram;
      m68k.memory_map[i].read8    = sram_read_byte;
      m68k.memory_map[i].read16   = sram_read_word;
      m68k.memory_map[i].write8   = sram_write_byte;
      m68k.memory_map[i].write16  = sram_write_word;
      zbank_memory_map[i].read    = sram_read_byte;
      zbank_memory_map[i].write   = sram_write_byte;

    }
    else
    {
      /* check if SRAM was mapped there before loading state */
      if (m68k.memory_map[i].base == sram.sram)
      {
        m68k.memory_map[i].read8    = NULL;
        m68k.memory_map[i].read16   = NULL;
        m68k.memory_map[i].write8   = m68k_unused_8_w;
        m68k.memory_map[i].write16  = m68k_unused_16_w;
        zbank_memory_map[i].read    = NULL;
        zbank_memory_map[i].write   = zbank_unused_w;
      }

      /* ROM */
      m68k.memory_map[i].base = cart.rom + (offset << 16);
    }
  }

  /* hardware registers */
  load_param(cart.hw.regs, sizeof(cart.hw.regs));

  /* SVP */
  if (svp)
  {
    load_param(svp->iram_rom, 0x800);
    load_param(svp->dram,sizeof(svp->dram));
    load_param(&svp->ssp1601,sizeof(ssp1601_t));
  }

  return bufferptr;
}