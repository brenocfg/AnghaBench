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

__attribute__((used)) static uint32 mapper_radica_r(uint32 address)
{
  int i = 0;
  address = (address >> 1);
  
  /* 64 x 64k banks */
  for (i = 0; i < 64; i++)
  {
    m68k.memory_map[i].base = &cart.rom[((address++)& 0x3f)<< 16];
  }

  return 0xffff;
}