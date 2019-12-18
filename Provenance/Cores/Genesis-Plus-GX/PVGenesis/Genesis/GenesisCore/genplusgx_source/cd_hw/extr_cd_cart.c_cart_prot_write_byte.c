#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* memory_map; } ;
struct TYPE_7__ {unsigned int prot; } ;
struct TYPE_9__ {TYPE_2__ cartridge; } ;
struct TYPE_8__ {void* write; } ;
struct TYPE_6__ {int /*<<< orphan*/  write16; void* write8; } ;

/* Variables and functions */
 void* cart_ram_write_byte ; 
 int /*<<< orphan*/  cart_ram_write_word ; 
 TYPE_5__ m68k ; 
 int /*<<< orphan*/  m68k_unused_16_w ; 
 void* m68k_unused_8_w ; 
 TYPE_4__ scd ; 
 TYPE_3__* zbank_memory_map ; 
 void* zbank_unused_w ; 

__attribute__((used)) static void cart_prot_write_byte(unsigned int address, unsigned int data)
{
  /* LSB only */
  if (address & 1)
  {
    int i;

    if (data & 1)
    {
      /* cartridge is write enabled */
      for (i=0x60; i<0x70; i++)
      {
        m68k.memory_map[i].write8  = cart_ram_write_byte;
        m68k.memory_map[i].write16 = cart_ram_write_word;
        zbank_memory_map[i].write  = cart_ram_write_byte;
      }
    }
    else
    {
      /* cartridge is write protected */
      for (i=0x60; i<0x70; i++)
      {
        m68k.memory_map[i].write8  = m68k_unused_8_w;
        m68k.memory_map[i].write16 = m68k_unused_16_w;
        zbank_memory_map[i].write  = zbank_unused_w;
      }
    }

    scd.cartridge.prot = data;
  }
}