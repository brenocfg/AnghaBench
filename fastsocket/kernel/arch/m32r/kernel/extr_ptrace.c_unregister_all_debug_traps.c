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
struct debug_trap {int nr_trap; int /*<<< orphan*/ * insn; int /*<<< orphan*/ * addr; } ;
struct TYPE_2__ {struct debug_trap debug_trap; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  access_process_vm (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
unregister_all_debug_traps(struct task_struct *child)
{
	struct debug_trap *p = &child->thread.debug_trap;
	int i;

	for (i = 0; i < p->nr_trap; i++)
		access_process_vm(child, p->addr[i], &p->insn[i], sizeof(p->insn[i]), 1);
	p->nr_trap = 0;
}