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
struct TYPE_6__ {scalar_t__ rom; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {scalar_t__ base; } ;

/* Variables and functions */
 TYPE_3__ cart ; 
 TYPE_2__ m68k ; 

__attribute__((used)) static void mapper_sf002_w(uint32 address, uint32 data)
{
  int i;
  if (data & 0x80)
  {
    /* $000000-$1BFFFF mapped to $200000-$3BFFFF */
    for (i=0x20; i<0x3C; i++)
    {
      m68k.memory_map[i].base = cart.rom + ((i & 0x1F) << 16);
    }
  }
  else
  {
    /* $200000-$3BFFFF mapped to $200000-$3BFFFF */
    for (i=0x20; i<0x3C; i++)
    {
      m68k.memory_map[i].base = cart.rom + (i << 16);
    }
  }
}