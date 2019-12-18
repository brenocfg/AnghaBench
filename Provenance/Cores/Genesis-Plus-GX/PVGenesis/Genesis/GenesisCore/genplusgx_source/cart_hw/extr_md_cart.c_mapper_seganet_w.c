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
struct TYPE_6__ {TYPE_1__* memory_map; } ;
struct TYPE_5__ {int /*<<< orphan*/ * write; } ;
struct TYPE_4__ {int /*<<< orphan*/ * write16; int /*<<< orphan*/ * write8; } ;

/* Variables and functions */
 TYPE_3__ m68k ; 
 int /*<<< orphan*/ * m68k_unused_16_w ; 
 int /*<<< orphan*/ * m68k_unused_8_w ; 
 TYPE_2__* zbank_memory_map ; 
 int /*<<< orphan*/ * zbank_unused_w ; 

__attribute__((used)) static void mapper_seganet_w(uint32 address, uint32 data)
{
  if ((address & 0xff) == 0xf1)
  {
    int i;
    if (data & 1)
    {
      /* ROM Write protected */
      for (i=0; i<0x40; i++)
      {
        m68k.memory_map[i].write8   = m68k_unused_8_w;
        m68k.memory_map[i].write16  = m68k_unused_16_w;
        zbank_memory_map[i].write   = zbank_unused_w;
      }
    }
    else
    {
      /* ROM Write enabled */
      for (i=0; i<0x40; i++)
      {
        m68k.memory_map[i].write8   = NULL;
        m68k.memory_map[i].write16  = NULL;
        zbank_memory_map[i].write   = NULL;
      }
    }
  }
}