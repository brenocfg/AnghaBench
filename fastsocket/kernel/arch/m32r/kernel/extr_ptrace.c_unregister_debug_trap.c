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
struct debug_trap {int nr_trap; unsigned long* addr; unsigned long* insn; } ;
struct TYPE_2__ {struct debug_trap debug_trap; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */

__attribute__((used)) static int
unregister_debug_trap(struct task_struct *child, unsigned long addr,
		      unsigned long *code)
{
	struct debug_trap *p = &child->thread.debug_trap;
        int i;

	/* Search debug trap entry. */
	for (i = 0; i < p->nr_trap; i++) {
		if (p->addr[i] == addr)
			break;
	}
	if (i >= p->nr_trap) {
		/* The trap may be requested from debugger.
		 * ptrace should do nothing in this case.
		 */
		return 0;
	}

	/* Recover original instruction code. */
	*code = p->insn[i];

	/* Shift debug trap entries. */
	while (i < p->nr_trap - 1) {
		p->insn[i] = p->insn[i + 1];
		p->addr[i] = p->addr[i + 1];
		i++;
	}
	p->nr_trap--;
	return 1;
}