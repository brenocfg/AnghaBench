#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; int /*<<< orphan*/ * opcode; } ;

/* Variables and functions */
 scalar_t__ gdbstub_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* step_bp ; 

__attribute__((used)) static int __gdbstub_mark_bp(u8 *addr, int ix)
{
	if (addr < (u8 *) 0x70000000UL)
		return 0;
	/* 70000000-7fffffff: vmalloc area */
	if (addr < (u8 *) 0x80000000UL)
		goto okay;
	if (addr < (u8 *) 0x8c000000UL)
		return 0;
	/* 8c000000-93ffffff: SRAM, SDRAM */
	if (addr < (u8 *) 0x94000000UL)
		goto okay;
	return 0;

okay:
	if (gdbstub_read_byte(addr + 0, &step_bp[ix].opcode[0]) < 0 ||
	    gdbstub_read_byte(addr + 1, &step_bp[ix].opcode[1]) < 0)
		return 0;

	step_bp[ix].addr = addr;
	return 1;
}