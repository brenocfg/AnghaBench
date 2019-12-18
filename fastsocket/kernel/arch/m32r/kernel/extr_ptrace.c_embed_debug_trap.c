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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  next_insn ;
typedef  int /*<<< orphan*/  code ;

/* Variables and functions */
 int access_process_vm (struct task_struct*,unsigned long,unsigned long*,int,int) ; 
 scalar_t__ register_debug_trap (struct task_struct*,unsigned long,unsigned long,unsigned long*) ; 

__attribute__((used)) static int
embed_debug_trap(struct task_struct *child, unsigned long next_pc)
{
	unsigned long next_insn, code;
	unsigned long addr = next_pc & ~3;

	if (access_process_vm(child, addr, &next_insn, sizeof(next_insn), 0)
	    != sizeof(next_insn)) {
		return -1; /* error */
	}

	/* Set a trap code. */
	if (register_debug_trap(child, next_pc, next_insn, &code)) {
		return -1; /* error */
	}
	if (access_process_vm(child, addr, &code, sizeof(code), 1)
	    != sizeof(code)) {
		return -1; /* error */
	}
	return 0; /* success */
}