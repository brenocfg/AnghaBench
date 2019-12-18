#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  get_instruction (unsigned short*,unsigned short*) ; 

__attribute__((used)) static bool is_bfin_call(unsigned short *addr)
{
	unsigned short opcode = 0, *ins_addr;
	ins_addr = (unsigned short *)addr;

	if (!get_instruction(&opcode, ins_addr))
		return false;

	if ((opcode >= 0x0060 && opcode <= 0x0067) ||
	    (opcode >= 0x0070 && opcode <= 0x0077))
		return true;

	ins_addr--;
	if (!get_instruction(&opcode, ins_addr))
		return false;

	if (opcode >= 0xE300 && opcode <= 0xE3FF)
		return true;

	return false;

}