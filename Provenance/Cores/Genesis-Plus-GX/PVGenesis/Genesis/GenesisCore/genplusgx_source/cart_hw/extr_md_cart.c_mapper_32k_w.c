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
typedef  int uint32 ;
struct TYPE_6__ {int /*<<< orphan*/ * rom; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 TYPE_3__ cart ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mapper_32k_w(uint32 data)
{
  int i;
  
  /* 64 x 32k banks */
  if (data)
  {
    for (i=0; i<0x10; i++)
    {
      /* Remap to unused ROM area  */
      m68k.memory_map[i].base = &cart.rom[0x400000 + (i << 16)];

      /* address = address OR (value << 15) */
      memcpy(m68k.memory_map[i].base, cart.rom + ((i << 16) | (data & 0x3f) << 15), 0x8000);
      memcpy(m68k.memory_map[i].base + 0x8000, cart.rom + ((i << 16) | ((data | 1) & 0x3f) << 15), 0x8000);
    }
  }
  else
  {
    /* reset default $000000-$0FFFFF mapping */
    for (i=0; i<16; i++)
    {
      m68k.memory_map[i].base = &cart.rom[i << 16];
    }
  }
}