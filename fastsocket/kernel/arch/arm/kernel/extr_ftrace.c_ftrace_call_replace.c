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
 long BL_OFFSET_MASK ; 
 long BL_OPCODE ; 
 scalar_t__ PC_OFFSET ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 long bl_insn ; 
 scalar_t__ unlikely (int) ; 

unsigned char *ftrace_call_replace(unsigned long pc, unsigned long addr)
{
	long offset;

	offset = (long)addr - (long)(pc + PC_OFFSET);
	if (unlikely(offset < -33554432 || offset > 33554428)) {
		/* Can't generate branches that far (from ARM ARM). Ftrace
		 * doesn't generate branches outside of kernel text.
		 */
		WARN_ON_ONCE(1);
		return NULL;
	}
	offset = (offset >> 2) & BL_OFFSET_MASK;
	bl_insn = BL_OPCODE | offset;
	return (unsigned char *)&bl_insn;
}