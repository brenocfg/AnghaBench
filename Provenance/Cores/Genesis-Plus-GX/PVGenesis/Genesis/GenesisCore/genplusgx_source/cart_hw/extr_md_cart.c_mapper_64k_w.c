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

__attribute__((used)) static void mapper_64k_w(uint32 data)
{
  int i;

  /* 16 x 64k banks */
  if (data)
  {
    /* bank is mapped at $000000-$0FFFFF */
    for (i=0; i<16; i++)
    {
      m68k.memory_map[i].base = &cart.rom[(data & 0xf) << 16];
    }
  }
  else
  {
    /* reset default $000000-$0FFFFF mapping */
    for (i=0; i<16; i++)
    {
      m68k.memory_map[i].base = &cart.rom[(i & 0xf) << 16];
    }
  }
}