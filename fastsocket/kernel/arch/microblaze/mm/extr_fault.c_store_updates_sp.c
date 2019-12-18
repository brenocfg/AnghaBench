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
struct pt_regs {scalar_t__ pc; } ;

/* Variables and functions */
 scalar_t__ get_user (unsigned int,unsigned int*) ; 

__attribute__((used)) static int store_updates_sp(struct pt_regs *regs)
{
	unsigned int inst;

	if (get_user(inst, (unsigned int *)regs->pc))
		return 0;
	/* check for 1 in the rD field */
	if (((inst >> 21) & 0x1f) != 1)
		return 0;
	/* check for store opcodes */
	if ((inst & 0xd0000000) == 0xd0000000)
		return 1;
	return 0;
}