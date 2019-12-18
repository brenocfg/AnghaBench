#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  address ;
struct TYPE_4__ {unsigned int pc; TYPE_1__* memory_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_REG_PC ; 
 unsigned int READ_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,unsigned int,char*) ; 
 TYPE_2__ m68k ; 
 char* m68k_get_reg (int /*<<< orphan*/ ) ; 

unsigned int m68k_read_bus_8(unsigned int address)
{
#ifdef LOGERROR
  error("Unused read8 %08X (%08X)\n", address, m68k_get_reg(M68K_REG_PC));
#endif
  address = m68k.pc | (address & 1);
  return READ_BYTE(m68k.memory_map[((address)>>16)&0xff].base, (address) & 0xffff);
}