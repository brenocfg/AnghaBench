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
struct TYPE_6__ {int /*<<< orphan*/  rom; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_3__ cart ; 
 TYPE_2__ m68k ; 

__attribute__((used)) static void ar_write_regs_2(uint32 address, uint32 data)
{
  /* enable Cartridge ROM */
  if (((address & 0xff) == 0x78) && (data == 0xffff))
  {
    m68k.memory_map[0].base = cart.rom;
  }
}