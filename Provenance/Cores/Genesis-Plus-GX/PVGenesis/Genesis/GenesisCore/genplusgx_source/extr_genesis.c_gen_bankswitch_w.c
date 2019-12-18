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
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int SYSTEM_MD ; 
 int /*<<< orphan*/  boot_rom ; 
 TYPE_3__ cart ; 
 TYPE_2__ m68k ; 
 int system_bios ; 

void gen_bankswitch_w(unsigned int data)
{
  /* check if BOOT ROM is loaded */
  if (system_bios & SYSTEM_MD)
  {
    if (data & 1)
    {
      /* enable cartridge ROM */
      m68k.memory_map[0].base = cart.base;
    }
    else
    {
      /* enable internal BOOT ROM */
      m68k.memory_map[0].base = boot_rom;
    }
  }
}